/*
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "p4IRConstructor.h"

#include "P4Lexer.h"
#include "frontends/common/constantParsing.h"
#include "frontends/common/parser_options.h"
#include "ir/ir.h"
#include "lib/error.h"
#include "lib/log.h"

using namespace P4::literals;

namespace P4ANTLR {

P4IRConstructor::P4IRConstructor(const SourceInfoFactory &sourceInfoFactory,
                                 P4::Util::InputSources *sources)
    : sourceInfoFactory(sourceInfoFactory),
      sources(sources),
      structure(new P4::Util::ProgramStructure()) {}

//===----------------------------------------------------------------------===//
// Source info helpers
//===----------------------------------------------------------------------===//

P4::Util::SourceInfo P4IRConstructor::srcInfo(antlr4::ParserRuleContext *ctx) const {
    if (srcInfoOverride.isValid()) return srcInfoOverride;
    return sourceInfoFactory.toSourceInfo(ctx);
}

P4::Util::SourceInfo P4IRConstructor::srcInfo(antlr4::Token *token) const {
    if (srcInfoOverride.isValid()) return srcInfoOverride;
    return sourceInfoFactory.toSourceInfo(token);
}

P4::Util::SourceInfo P4IRConstructor::srcInfo(antlr4::Token *start,
                                              antlr4::Token *stop) const {
    if (srcInfoOverride.isValid()) return srcInfoOverride;
    return sourceInfoFactory.toSourceInfo(start, stop);
}

//===----------------------------------------------------------------------===//
// Integer parsing
//===----------------------------------------------------------------------===//

P4::UnparsedConstant P4IRConstructor::tokenToUnparsedConstant(
    const std::string &text) {
    P4::UnparsedConstant uc;
    uc.text = P4::cstring(text);

    // Check for width-prefixed constant: digits followed by 'w', 'W', 's', 'S'
    size_t sepPos = std::string::npos;
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] == 'w' || text[i] == 'W' || text[i] == 's' || text[i] == 'S') {
            // Make sure everything before is a digit
            bool allDigits = true;
            for (size_t j = 0; j < i; ++j) {
                if (!isdigit(text[j])) {
                    allDigits = false;
                    break;
                }
            }
            if (allDigits && i > 0) {
                sepPos = i;
                break;
            }
        }
    }

    if (sepPos != std::string::npos) {
        uc.hasWidth = true;
        // The value part starts after the separator.
        // 'skip' is the length of the base prefix (e.g., 2 for "0x") relative
        // to the value part, NOT an absolute position in the text. The
        // parseConstantWithWidth function parses the width and separator itself,
        // then uses 'skip' to skip the base prefix of the value part.
        std::string valuePart = text.substr(sepPos + 1);
        if (valuePart.size() >= 2 && valuePart[0] == '0') {
            char prefix = valuePart[1];
            if (prefix == 'x' || prefix == 'X') {
                uc.base = 16;
                uc.skip = 2;
            } else if (prefix == 'b' || prefix == 'B') {
                uc.base = 2;
                uc.skip = 2;
            } else if (prefix == 'o' || prefix == 'O') {
                uc.base = 8;
                uc.skip = 2;
            } else if (prefix == 'd' || prefix == 'D') {
                uc.base = 10;
                uc.skip = 2;
            } else {
                uc.base = 10;
                uc.skip = 0;
            }
        } else {
            uc.base = 10;
            uc.skip = 0;
        }
    } else {
        uc.hasWidth = false;
        if (text.size() >= 2 && text[0] == '0') {
            char prefix = text[1];
            if (prefix == 'x' || prefix == 'X') {
                uc.base = 16;
                uc.skip = 2;
            } else if (prefix == 'b' || prefix == 'B') {
                uc.base = 2;
                uc.skip = 2;
            } else if (prefix == 'o' || prefix == 'O') {
                uc.base = 8;
                uc.skip = 2;
            } else if (prefix == 'd' || prefix == 'D') {
                uc.base = 10;
                uc.skip = 2;
            } else {
                uc.base = 10;
                uc.skip = 0;
            }
        } else {
            uc.base = 10;
            uc.skip = 0;
        }
    }

    return uc;
}

P4::IR::Constant *P4IRConstructor::parseIntegerToken(antlr4::Token *token) {
    auto text = token->getText();
    auto uc = tokenToUnparsedConstant(text);
    return P4::parseConstant(srcInfo(token), uc, 0);
}

//===----------------------------------------------------------------------===//
// Entry point
//===----------------------------------------------------------------------===//

const P4::IR::P4Program *P4IRConstructor::visitProgram(
    Antlr4P4Parser::ProgramContext *ctx) {
    auto *nodes = new P4::IR::Vector<P4::IR::Node>();

    for (auto *declCtx : ctx->declaration()) {
        auto *node = visitDeclaration(declCtx);
        if (node) nodes->push_back(node);
    }

    structure->endParse();
    return new P4::IR::P4Program(srcInfo(ctx), *nodes);
}

//===----------------------------------------------------------------------===//
// Names
//===----------------------------------------------------------------------===//

P4::IR::ID *P4IRConstructor::visitName(Antlr4P4Parser::NameContext *ctx) {
    if (ctx->nonTypeName()) return visitNonTypeName(ctx->nonTypeName());
    if (ctx->LIST()) return new P4::IR::ID(srcInfo(ctx->LIST()->getSymbol()), "list"_cs);
    return new P4::IR::ID(srcInfo(ctx), P4::cstring(ctx->getText()));
}

P4::IR::ID *P4IRConstructor::visitNonTypeName(Antlr4P4Parser::NonTypeNameContext *ctx) {
    auto si = srcInfo(ctx);
    if (ctx->IDENTIFIER()) return new P4::IR::ID(si, P4::cstring(ctx->IDENTIFIER()->getText()));
    if (ctx->APPLY()) return new P4::IR::ID(si, "apply"_cs);
    if (ctx->KEY()) return new P4::IR::ID(si, "key"_cs);
    if (ctx->ACTIONS()) return new P4::IR::ID(si, "actions"_cs);
    if (ctx->STATE()) return new P4::IR::ID(si, "state"_cs);
    if (ctx->ENTRIES()) return new P4::IR::ID(si, "entries"_cs);
    if (ctx->TYPE()) return new P4::IR::ID(si, "type"_cs);
    if (ctx->PRIORITY()) return new P4::IR::ID(si, "priority"_cs);
    return new P4::IR::ID(si, P4::cstring(ctx->getText()));
}

P4::IR::ID *P4IRConstructor::visitNonTableKwName(Antlr4P4Parser::NonTableKwNameContext *ctx) {
    auto si = srcInfo(ctx);
    if (ctx->IDENTIFIER()) return new P4::IR::ID(si, P4::cstring(ctx->IDENTIFIER()->getText()));
    if (ctx->APPLY()) return new P4::IR::ID(si, "apply"_cs);
    if (ctx->STATE()) return new P4::IR::ID(si, "state"_cs);
    if (ctx->TYPE()) return new P4::IR::ID(si, "type"_cs);
    if (ctx->PRIORITY()) return new P4::IR::ID(si, "priority"_cs);
    return new P4::IR::ID(si, P4::cstring(ctx->getText()));
}

P4::IR::ID *P4IRConstructor::visitAnnotationName(Antlr4P4Parser::AnnotationNameContext *ctx) {
    return new P4::IR::ID(srcInfo(ctx), P4::cstring(ctx->getText()));
}

//===----------------------------------------------------------------------===//
// Annotations
//===----------------------------------------------------------------------===//

P4::IR::Vector<P4::IR::Annotation> *P4IRConstructor::visitOptAnnotations(
    Antlr4P4Parser::OptAnnotationsContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Annotation>();
    if (!ctx || !ctx->annotations()) return result;
    return visitAnnotations(ctx->annotations());
}

P4::IR::Vector<P4::IR::Annotation> *P4IRConstructor::visitAnnotations(
    Antlr4P4Parser::AnnotationsContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Annotation>();
    if (!ctx) return result;
    for (auto *annCtx : ctx->annotation()) {
        auto *ann = visitAnnotation(annCtx);
        if (ann && !P4::P4CContext::get().options().isAnnotationDisabled(ann)) {
            result->push_back(ann);
        }
    }
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Annotation *P4IRConstructor::visitAnnotation(
    Antlr4P4Parser::AnnotationContext *ctx) {
    auto *name = visitAnnotationName(ctx->annotationName());
    auto si = srcInfo(ctx);

    // @name(body)
    if (ctx->LPAR()) {
        auto *body = visitAnnotationBody(ctx->annotationBody());
        return new P4::IR::Annotation(si, *name, *body);
    }

    // @name[expressionList] or @name[kvList]
    if (ctx->LBRAK()) {
        if (ctx->expressionList()) {
            auto *exprList = visitExpressionList(ctx->expressionList());
            return new P4::IR::Annotation(si, *name, *exprList, true);
        }
        if (ctx->kvList()) {
            auto *kvs = visitKvList(ctx->kvList());
            return new P4::IR::Annotation(si, *name, *kvs, true);
        }
    }

    // @name (no arguments)
    return new P4::IR::Annotation(si, *name, P4::IR::Vector<P4::IR::AnnotationToken>());
}

/// Create an AnnotationToken from an ANTLR4 terminal. The `token_type` field
/// stores the ANTLR4 lexer token type so the annotation body can later be
/// re-lexed/re-parsed via the ANTLR4 parser fragment rules.
P4::IR::AnnotationToken *P4IRConstructor::makeAnnotationToken(antlr4::Token *token) {
    auto text = P4::cstring(token->getText());
    auto *annToken =
        new P4::IR::AnnotationToken(srcInfo(token), static_cast<int>(token->getType()), text);
    if (token->getType() == ::P4Lexer::INTEGER) {
        auto uc = tokenToUnparsedConstant(token->getText());
        annToken->constInfo = new P4::UnparsedConstant{
            P4::cstring(uc.text), uc.skip, uc.base, uc.hasWidth};
    }
    return annToken;
}

P4::IR::Vector<P4::IR::AnnotationToken> *P4IRConstructor::visitAnnotationBody(
    Antlr4P4Parser::AnnotationBodyContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::AnnotationToken>();
    if (!ctx) return result;

    // Walk through the children of annotationBody.
    // The grammar is: annotationBody -> empty
    //                                 | annotationBody '(' annotationBody ')'
    //                                 | annotationBody annotationToken
    // So children are: nested annotationBody contexts, annotationToken contexts,
    // and terminal nodes (parentheses from the '(' annotationBody ')' production).
    for (size_t i = 0; i < ctx->children.size(); ++i) {
        auto *child = ctx->children[i];
        // Recurse into nested annotationBody contexts.
        if (auto *abCtx = dynamic_cast<Antlr4P4Parser::AnnotationBodyContext *>(child)) {
            auto *inner = visitAnnotationBody(abCtx);
            result->append(*inner);
        } else if (auto *atCtx =
                       dynamic_cast<Antlr4P4Parser::AnnotationTokenContext *>(child)) {
            // annotationToken wraps a single terminal (keyword, operator, literal, etc.)
            auto *terminal = atCtx->children[0];
            if (auto *tn = dynamic_cast<antlr4::tree::TerminalNode *>(terminal)) {
                result->push_back(makeAnnotationToken(tn->getSymbol()));
            }
        } else if (auto *terminal = dynamic_cast<antlr4::tree::TerminalNode *>(child)) {
            // Direct terminals (parentheses from the balanced-paren production).
            result->push_back(makeAnnotationToken(terminal->getSymbol()));
        }
    }
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

//===----------------------------------------------------------------------===//
// Parameters
//===----------------------------------------------------------------------===//

P4::IR::IndexedVector<P4::IR::Parameter> *P4IRConstructor::visitParameterList(
    Antlr4P4Parser::ParameterListContext *ctx) {
    auto *result = new P4::IR::IndexedVector<P4::IR::Parameter>();
    if (!ctx || !ctx->nonEmptyParameterList()) return result;
    for (auto *paramCtx : ctx->nonEmptyParameterList()->parameter()) {
        result->push_back(visitParameter(paramCtx));
    }
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Parameter *P4IRConstructor::visitParameter(
    Antlr4P4Parser::ParameterContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    auto dir = visitDirection(ctx->direction());
    auto *type = visitTypeRef(ctx->typeRef());
    auto ntp = visitDeclarator(ctx->declarator(), type);
    P4::IR::Expression *defaultValue = nullptr;
    if (ctx->expression()) {
        defaultValue = visitExpression(ctx->expression());
    }
    return new P4::IR::Parameter(srcInfo(ctx->declarator()), *ntp.name,
                                 *annotations, dir, ntp.type, defaultValue);
}

P4::IR::Direction P4IRConstructor::visitDirection(
    Antlr4P4Parser::DirectionContext *ctx) {
    if (!ctx || ctx->children.empty()) return P4::IR::Direction::None;
    if (ctx->IN()) return P4::IR::Direction::In;
    if (ctx->OUT()) return P4::IR::Direction::Out;
    if (ctx->INOUT()) return P4::IR::Direction::InOut;
    return P4::IR::Direction::None;
}

//===----------------------------------------------------------------------===//
// Types
//===----------------------------------------------------------------------===//

const P4::IR::Type *P4IRConstructor::visitTypeRef(
    Antlr4P4Parser::TypeRefContext *ctx) {
    if (auto *c = dynamic_cast<Antlr4P4Parser::BaseTypeRefContext *>(ctx)) {
        return visitBaseType(c->baseType());
    }
    if (auto *c = dynamic_cast<Antlr4P4Parser::TypeNameRefContext *>(ctx)) {
        return visitTypeName(c->typeName());
    }
    if (auto *c = dynamic_cast<Antlr4P4Parser::SpecializedTypeRefContext *>(ctx)) {
        return visitSpecializedType(c->specializedType());
    }
    if (auto *c = dynamic_cast<Antlr4P4Parser::HeaderStackTypeRefContext *>(ctx)) {
        // Inlined headerStackType: typeRef '[' expression ']'
        auto *type = visitTypeRef(c->typeRef());
        auto *size = visitExpression(c->expression());
        return new P4::IR::Type_Array(srcInfo(ctx), type, size);
    }
    if (auto *c = dynamic_cast<Antlr4P4Parser::P4listTypeRefContext *>(ctx)) {
        return visitP4listType(c->p4listType());
    }
    if (auto *c = dynamic_cast<Antlr4P4Parser::TupleTypeRefContext *>(ctx)) {
        return visitTupleType(c->tupleType());
    }
    BUG("Unexpected typeRef alternative");
}

const P4::IR::Type *P4IRConstructor::visitBaseType(
    Antlr4P4Parser::BaseTypeContext *ctx) {
    auto si = srcInfo(ctx);
    if (ctx->BOOL()) return P4::IR::Type_Boolean::get(si);
    if (ctx->MATCH_KIND()) return P4::IR::Type_MatchKind::get(si);
    if (ctx->ERROR()) {
        return new P4::IR::Type_Name(si, new P4::IR::Path(P4::IR::ID(si, "error"_cs)));
    }
    if (ctx->STRING_KW()) return P4::IR::Type::String::get(si);
    if (ctx->INT() && !ctx->LT()) return P4::IR::Type_InfInt::get(si);
    if (ctx->BIT() && !ctx->LT()) return P4::IR::Type::Bits::get(si, 1);

    // bit<N>, int<N>, varbit<N>
    if (ctx->INTEGER()) {
        auto *intToken = ctx->INTEGER()->getSymbol();
        int width = P4::parseConstantChecked(srcInfo(intToken),
                                             tokenToUnparsedConstant(intToken->getText()));
        if (ctx->BIT()) return P4::IR::Type::Bits::get(si, width, false);
        if (ctx->INT()) return P4::IR::Type::Bits::get(si, width, true);
        if (ctx->VARBIT()) return P4::IR::Type::Varbits::get(si, width);
    }

    // bit<(expr)>, int<(expr)>, varbit<(expr)>
    if (ctx->expression()) {
        auto *expr = visitExpression(ctx->expression());
        if (ctx->BIT()) return P4::IR::Type_Bits::get(si, expr, false);
        if (ctx->INT()) return P4::IR::Type_Bits::get(si, expr, true);
        if (ctx->VARBIT()) return P4::IR::Type_Varbits::get(si, expr);
    }

    BUG("Unexpected baseType alternative");
}

P4::IR::Type_Name *P4IRConstructor::visitTypeName(
    const std::string &text, P4::Util::SourceInfo si) {
    bool absolute = !text.empty() && text[0] == '.';
    auto name = absolute ? text.substr(1) : text;
    auto *id = new P4::IR::ID(si, P4::cstring(name));
    auto *path = new P4::IR::Path(*id, absolute);
    return new P4::IR::Type_Name(si, path);
}

P4::IR::Type_Name *P4IRConstructor::visitTypeName(
    Antlr4P4Parser::TypeNameContext *ctx) {
    auto *prefixed = ctx->prefixedType();
    auto si = srcInfo(ctx);
    if (prefixed->DOT()) {
        // Absolute path: .TypeName
        auto *id = new P4::IR::ID(srcInfo(prefixed->IDENTIFIER()->getSymbol()),
                                  P4::cstring(prefixed->IDENTIFIER()->getText()));
        auto *path = new P4::IR::Path(*id, true);
        return new P4::IR::Type_Name(si, path);
    }
    auto *id = new P4::IR::ID(srcInfo(prefixed->IDENTIFIER()->getSymbol()),
                              P4::cstring(prefixed->IDENTIFIER()->getText()));
    auto *path = new P4::IR::Path(*id);
    return new P4::IR::Type_Name(si, path);
}

const P4::IR::Type *P4IRConstructor::visitSpecializedType(
    Antlr4P4Parser::SpecializedTypeContext *ctx) {
    auto *typeName = visitTypeName(ctx->typeName());
    auto *typeArgs = visitTypeArgumentList(ctx->typeArgumentList());
    return new P4::IR::Type_Specialized(srcInfo(ctx), typeName, typeArgs);
}

const P4::IR::Type *P4IRConstructor::visitP4listType(
    Antlr4P4Parser::P4listTypeContext *ctx) {
    auto *typeArg = visitTypeArg(ctx->typeArg());
    return new P4::IR::Type_P4List(srcInfo(ctx), typeArg);
}

const P4::IR::Type *P4IRConstructor::visitTupleType(
    Antlr4P4Parser::TupleTypeContext *ctx) {
    auto *typeArgs = visitTypeArgumentList(ctx->typeArgumentList());
    return new P4::IR::Type_Tuple(srcInfo(ctx), *typeArgs);
}

const P4::IR::Type *P4IRConstructor::visitTypeOrVoid(
    Antlr4P4Parser::TypeOrVoidContext *ctx) {
    if (ctx->typeRef()) return visitTypeRef(ctx->typeRef());
    if (ctx->VOID()) return P4::IR::Type_Void::get(srcInfo(ctx));
    if (ctx->IDENTIFIER()) {
        auto si = srcInfo(ctx->IDENTIFIER()->getSymbol());
        return new P4::IR::Type_Name(si,
            new P4::IR::Path(P4::IR::ID(si, P4::cstring(ctx->IDENTIFIER()->getText()))));
    }
    BUG("Unexpected typeOrVoid alternative");
}

const P4::IR::Type *P4IRConstructor::visitNamedType(
    Antlr4P4Parser::NamedTypeContext *ctx) {
    if (ctx->typeName()) return visitTypeName(ctx->typeName());
    if (ctx->specializedType()) return visitSpecializedType(ctx->specializedType());
    BUG("Unexpected namedType alternative");
}

P4::IR::TypeParameters *P4IRConstructor::visitOptTypeParameters(
    Antlr4P4Parser::OptTypeParametersContext *ctx) {
    if (!ctx || !ctx->typeParameters()) return new P4::IR::TypeParameters();
    return visitTypeParameters(ctx->typeParameters());
}

P4::IR::TypeParameters *P4IRConstructor::visitTypeParameters(
    Antlr4P4Parser::TypeParametersContext *ctx) {
    auto *tpList = new P4::IR::IndexedVector<P4::IR::Type_Var>();
    for (auto *nameCtx : ctx->typeParameterList()->name()) {
        auto *id = visitName(nameCtx);
        tpList->push_back(new P4::IR::Type_Var(srcInfo(nameCtx), *id));
    }
    return new P4::IR::TypeParameters(srcInfo(ctx), *tpList);
}

const P4::IR::Type *P4IRConstructor::visitTypeArg(
    Antlr4P4Parser::TypeArgContext *ctx) {
    if (ctx->typeRef()) return visitTypeRef(ctx->typeRef());
    if (ctx->VOID()) return P4::IR::Type_Void::get(srcInfo(ctx));
    if (ctx->DONTCARE()) return P4::IR::Type_Dontcare::get(srcInfo(ctx));
    if (ctx->nonTypeName()) {
        auto *id = visitNonTypeName(ctx->nonTypeName());
        return new P4::IR::Type_Name(srcInfo(ctx), new P4::IR::Path(*id));
    }
    BUG("Unexpected typeArg alternative");
}

P4::IR::Vector<P4::IR::Type> *P4IRConstructor::visitTypeArgumentList(
    Antlr4P4Parser::TypeArgumentListContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Type>();
    if (!ctx) return result;
    for (auto *argCtx : ctx->typeArg()) {
        result->push_back(visitTypeArg(argCtx));
    }
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Vector<P4::IR::Type> *P4IRConstructor::visitRealTypeArgumentList(
    Antlr4P4Parser::RealTypeArgumentListContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Type>();
    if (!ctx) return result;
    if (ctx->realTypeArg()) {
        auto *ratCtx = ctx->realTypeArg();
        if (ratCtx->typeRef()) result->push_back(visitTypeRef(ratCtx->typeRef()));
        else if (ratCtx->VOID()) result->push_back(P4::IR::Type_Void::get(srcInfo(ratCtx)));
        else if (ratCtx->DONTCARE()) result->push_back(P4::IR::Type_Dontcare::get(srcInfo(ratCtx)));
    }
    for (auto *argCtx : ctx->typeArg()) {
        result->push_back(visitTypeArg(argCtx));
    }
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

//===----------------------------------------------------------------------===//
// Declarations
//===----------------------------------------------------------------------===//

P4::IR::Node *P4IRConstructor::visitDeclaration(
    Antlr4P4Parser::DeclarationContext *ctx) {
    if (ctx->constantDeclaration()) return visitConstantDeclaration(ctx->constantDeclaration());
    if (ctx->externDeclaration()) return visitExternDeclaration(ctx->externDeclaration());
    if (ctx->actionDeclaration()) return visitActionDeclaration(ctx->actionDeclaration());
    if (ctx->parserDeclaration()) return visitParserDeclaration(ctx->parserDeclaration());
    if (ctx->typeDeclaration()) return visitTypeDeclaration(ctx->typeDeclaration());
    if (ctx->controlDeclaration()) return visitControlDeclaration(ctx->controlDeclaration());
    if (ctx->instantiation()) return visitInstantiation(ctx->instantiation());
    if (ctx->errorDeclaration()) {
        auto *err = visitErrorDeclaration(ctx->errorDeclaration());
        // Merge error declarations like the Bison parser does
        if (allErrors == nullptr) {
            allErrors = err;
            return err;
        }
        allErrors->members.append(err->members);
        return nullptr;
    }
    if (ctx->matchKindDeclaration()) return visitMatchKindDeclaration(ctx->matchKindDeclaration());
    if (ctx->functionDeclaration()) return visitFunctionDeclaration(ctx->functionDeclaration());
    BUG("Unexpected declaration alternative");
}

P4::IR::Declaration *P4IRConstructor::visitConstantDeclaration(
    Antlr4P4Parser::ConstantDeclarationContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    auto *type = visitTypeRef(ctx->typeRef());
    auto ntp = visitDeclarator(ctx->declarator(), type);
    auto *init = visitInitializer(ctx->initializer());
    structure->declareObject(*ntp.name, ntp.type->toString());
    return new P4::IR::Declaration_Constant(srcInfo(ctx->declarator()), *ntp.name,
                                            *annotations, ntp.type, init);
}

P4::IR::Declaration *P4IRConstructor::visitVariableDeclaration(
    Antlr4P4Parser::VariableDeclarationContext *ctx) {
    auto *type = visitTypeRef(ctx->typeRef());
    auto ntp = visitDeclarator(ctx->declarator(), type);
    auto *init = visitOptInitializer(ctx->optInitializer());

    if (ctx->annotations()) {
        auto *annotations = visitAnnotations(ctx->annotations());
        structure->declareObject(*ntp.name, ntp.type->toString());
        return new P4::IR::Declaration_Variable(srcInfo(ctx), *ntp.name,
                                                *annotations, ntp.type, init);
    }

    structure->declareObject(*ntp.name, ntp.type->toString());
    return new P4::IR::Declaration_Variable(srcInfo(ctx), *ntp.name, ntp.type, init);
}

P4::IR::Declaration *P4IRConstructor::visitVariableDeclarationWithoutSemicolon(
    Antlr4P4Parser::VariableDeclarationWithoutSemicolonContext *ctx) {
    auto *type = visitTypeRef(ctx->typeRef());
    auto ntp = visitDeclarator(ctx->declarator(), type);
    auto *init = visitOptInitializer(ctx->optInitializer());

    if (ctx->annotations()) {
        auto *annotations = visitAnnotations(ctx->annotations());
        structure->declareObject(*ntp.name, ntp.type->toString());
        return new P4::IR::Declaration_Variable(srcInfo(ctx), *ntp.name,
                                                *annotations, ntp.type, init);
    }

    structure->declareObject(*ntp.name, ntp.type->toString());
    return new P4::IR::Declaration_Variable(srcInfo(ctx), *ntp.name, ntp.type, init);
}

P4IRConstructor::NameTypePair P4IRConstructor::visitDeclarator(
    Antlr4P4Parser::DeclaratorContext *ctx, const P4::IR::Type *baseType) {
    if (ctx->name()) {
        auto *name = visitName(ctx->name());
        return {name, baseType};
    }
    // Array declarator: declarator[expression]
    auto inner = visitDeclarator(ctx->declarator(), baseType);
    auto *size = visitExpression(ctx->expression());
    auto *arrayType = new P4::IR::Type_Array(srcInfo(ctx), inner.type, size);
    return {inner.name, arrayType};
}

P4::IR::Expression *P4IRConstructor::visitOptInitializer(
    Antlr4P4Parser::OptInitializerContext *ctx) {
    if (!ctx || !ctx->initializer()) return nullptr;
    return visitInitializer(ctx->initializer());
}

P4::IR::Expression *P4IRConstructor::visitInitializer(
    Antlr4P4Parser::InitializerContext *ctx) {
    return visitExpression(ctx->expression());
}

P4::IR::Declaration *P4IRConstructor::visitInstantiation(
    Antlr4P4Parser::InstantiationContext *ctx) {
    auto *type = visitTypeRef(ctx->typeRef());
    auto *args = visitArgumentList(ctx->argumentList());
    auto ntp = visitDeclarator(ctx->declarator(), type);
    auto *objInit = visitOptObjInitializer(ctx->optObjInitializer());

    if (ctx->annotations()) {
        auto *annotations = visitAnnotations(ctx->annotations());
        structure->declareObject(*ntp.name, type->toString());
        return new P4::IR::Declaration_Instance(srcInfo(ctx->declarator()), *ntp.name,
                                                *annotations, ntp.type, args, objInit);
    }

    structure->declareObject(*ntp.name, type->toString());
    return new P4::IR::Declaration_Instance(srcInfo(ctx->declarator()), *ntp.name,
                                            ntp.type, args, objInit);
}

P4::IR::IndexedVector<P4::IR::Parameter> *P4IRConstructor::visitOptConstructorParameters(
    Antlr4P4Parser::OptConstructorParametersContext *ctx) {
    if (!ctx || !ctx->parameterList()) return new P4::IR::IndexedVector<P4::IR::Parameter>();
    return visitParameterList(ctx->parameterList());
}

P4::IR::BlockStatement *P4IRConstructor::visitOptObjInitializer(
    Antlr4P4Parser::OptObjInitializerContext *ctx) {
    if (!ctx || !ctx->LCURL()) return nullptr;
    structure->pushNamespace(srcInfo(ctx), false);
    auto *stmts = new P4::IR::IndexedVector<P4::IR::StatOrDecl>();
    for (auto *objDeclCtx : ctx->objDeclarations()->objDeclaration()) {
        if (objDeclCtx->functionDeclaration()) {
            stmts->push_back(visitFunctionDeclaration(objDeclCtx->functionDeclaration()));
        } else if (objDeclCtx->instantiation()) {
            stmts->push_back(visitInstantiation(objDeclCtx->instantiation()));
        }
    }
    structure->pop();
    return new P4::IR::BlockStatement(srcInfo(ctx), *stmts);
}

//===----------------------------------------------------------------------===//
// Type declarations
//===----------------------------------------------------------------------===//

P4::IR::Type_Declaration *P4IRConstructor::visitTypeDeclaration(
    Antlr4P4Parser::TypeDeclarationContext *ctx) {
    if (ctx->derivedTypeDeclaration())
        return visitDerivedTypeDeclaration(ctx->derivedTypeDeclaration());
    if (ctx->typedefDeclaration())
        return visitTypedefDeclaration(ctx->typedefDeclaration());
    if (ctx->parserTypeDeclaration()) {
        auto *pt = visitParserTypeDeclaration(ctx->parserTypeDeclaration());
        structure->pop();
        return pt;
    }
    if (ctx->controlTypeDeclaration()) {
        auto *ct = visitControlTypeDeclaration(ctx->controlTypeDeclaration());
        structure->pop();
        return ct;
    }
    if (ctx->packageTypeDeclaration())
        return visitPackageTypeDeclaration(ctx->packageTypeDeclaration());
    BUG("Unexpected typeDeclaration alternative");
}

P4::IR::Type_Declaration *P4IRConstructor::visitDerivedTypeDeclaration(
    Antlr4P4Parser::DerivedTypeDeclarationContext *ctx) {
    if (ctx->headerTypeDeclaration()) return visitHeaderTypeDeclaration(ctx->headerTypeDeclaration());
    if (ctx->headerUnionDeclaration()) return visitHeaderUnionDeclaration(ctx->headerUnionDeclaration());
    if (ctx->structTypeDeclaration()) return visitStructTypeDeclaration(ctx->structTypeDeclaration());
    if (ctx->enumDeclaration()) return visitEnumDeclaration(ctx->enumDeclaration());
    BUG("Unexpected derivedTypeDeclaration alternative");
}

P4::IR::Type_Declaration *P4IRConstructor::visitHeaderTypeDeclaration(
    Antlr4P4Parser::HeaderTypeDeclarationContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    auto *name = visitName(ctx->name());
    structure->pushContainerType(*name, true);
    auto *typeParams = visitOptTypeParameters(ctx->optTypeParameters());
    structure->markAsTemplate(*name);
    structure->declareTypes(&typeParams->parameters);
    auto *fields = visitStructFieldList(ctx->structFieldList());
    auto *result = new P4::IR::Type_Header(srcInfo(ctx->name()), *name,
                                           *annotations, typeParams, *fields);
    structure->pop();
    return result;
}

P4::IR::Type_Declaration *P4IRConstructor::visitStructTypeDeclaration(
    Antlr4P4Parser::StructTypeDeclarationContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    auto *name = visitName(ctx->name());
    structure->pushContainerType(*name, true);
    auto *typeParams = visitOptTypeParameters(ctx->optTypeParameters());
    structure->markAsTemplate(*name);
    structure->declareTypes(&typeParams->parameters);
    auto *fields = visitStructFieldList(ctx->structFieldList());
    auto *result = new P4::IR::Type_Struct(srcInfo(ctx->name()), *name,
                                           *annotations, typeParams, *fields);
    structure->pop();
    return result;
}

P4::IR::Type_Declaration *P4IRConstructor::visitHeaderUnionDeclaration(
    Antlr4P4Parser::HeaderUnionDeclarationContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    auto *name = visitName(ctx->name());
    structure->pushContainerType(*name, true);
    auto *typeParams = visitOptTypeParameters(ctx->optTypeParameters());
    structure->markAsTemplate(*name);
    structure->declareTypes(&typeParams->parameters);
    auto *fields = visitStructFieldList(ctx->structFieldList());
    auto *result = new P4::IR::Type_HeaderUnion(srcInfo(ctx->name()), *name,
                                                *annotations, typeParams, *fields);
    structure->pop();
    return result;
}

P4::IR::IndexedVector<P4::IR::StructField> *P4IRConstructor::visitStructFieldList(
    Antlr4P4Parser::StructFieldListContext *ctx) {
    auto *result = new P4::IR::IndexedVector<P4::IR::StructField>();
    if (!ctx) return result;
    for (auto *fieldCtx : ctx->structField()) {
        result->push_back(visitStructField(fieldCtx));
    }
    return result;
}

P4::IR::StructField *P4IRConstructor::visitStructField(
    Antlr4P4Parser::StructFieldContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    auto *type = visitTypeRef(ctx->typeRef());
    auto ntp = visitDeclarator(ctx->declarator(), type);
    return new P4::IR::StructField(srcInfo(ctx->declarator()), *ntp.name,
                                   *annotations, ntp.type);
}

P4::IR::Type_Declaration *P4IRConstructor::visitEnumDeclaration(
    Antlr4P4Parser::EnumDeclarationContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());

    if (ctx->specifiedIdentifierList()) {
        // Serializable enum: enum typeRef name { ... }
        auto *type = visitTypeRef(ctx->typeRef());
        auto *name = visitName(ctx->name());
        structure->declareType(*name);
        auto *members = visitSpecifiedIdentifierList(ctx->specifiedIdentifierList());
        return new P4::IR::Type_SerEnum(srcInfo(ctx->name()), *name,
                                        *annotations, type, *members);
    }

    // Simple enum
    auto *name = visitName(ctx->name());
    structure->declareType(*name);
    auto *ids = visitIdentifierList(ctx->identifierList());
    return new P4::IR::Type_Enum(srcInfo(ctx->name()), *name, *annotations, *ids);
}

P4::IR::IndexedVector<P4::IR::SerEnumMember> *P4IRConstructor::visitSpecifiedIdentifierList(
    Antlr4P4Parser::SpecifiedIdentifierListContext *ctx) {
    auto *result = new P4::IR::IndexedVector<P4::IR::SerEnumMember>();
    for (auto *specCtx : ctx->specifiedIdentifier()) {
        result->push_back(visitSpecifiedIdentifier(specCtx));
    }
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::SerEnumMember *P4IRConstructor::visitSpecifiedIdentifier(
    Antlr4P4Parser::SpecifiedIdentifierContext *ctx) {
    auto *name = visitName(ctx->name());
    auto *init = visitInitializer(ctx->initializer());
    return new P4::IR::SerEnumMember(srcInfo(ctx), *name, init);
}

P4::IR::Type_Error *P4IRConstructor::visitErrorDeclaration(
    Antlr4P4Parser::ErrorDeclarationContext *ctx) {
    auto *ids = visitIdentifierList(ctx->identifierList());
    return new P4::IR::Type_Error(srcInfo(ctx), P4::IR::ID(srcInfo(ctx), "error"_cs), *ids);
}

P4::IR::Node *P4IRConstructor::visitMatchKindDeclaration(
    Antlr4P4Parser::MatchKindDeclarationContext *ctx) {
    auto *ids = visitIdentifierList(ctx->identifierList());
    return new P4::IR::Declaration_MatchKind(srcInfo(ctx), *ids);
}

P4::IR::IndexedVector<P4::IR::Declaration_ID> *P4IRConstructor::visitIdentifierList(
    Antlr4P4Parser::IdentifierListContext *ctx) {
    auto *result = new P4::IR::IndexedVector<P4::IR::Declaration_ID>();
    for (auto *nameCtx : ctx->name()) {
        auto *id = visitName(nameCtx);
        result->push_back(new P4::IR::Declaration_ID(srcInfo(nameCtx), *id));
    }
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Type_Declaration *P4IRConstructor::visitTypedefDeclaration(
    Antlr4P4Parser::TypedefDeclarationContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());

    if (ctx->TYPE()) {
        // type newtype
        auto *type = visitTypeRef(ctx->typeRef());
        auto ntp = visitDeclarator(ctx->declarator(), type);
        structure->declareType(*ntp.name);
        return new P4::IR::Type_Newtype(srcInfo(ctx->declarator()), *ntp.name,
                                        *annotations, ntp.type);
    }

    if (ctx->derivedTypeDeclaration()) {
        auto *derived = visitDerivedTypeDeclaration(ctx->derivedTypeDeclaration());
        auto ntp = visitDeclarator(ctx->declarator(), derived);
        structure->declareType(*ntp.name);
        return new P4::IR::Type_Typedef(srcInfo(ctx->declarator()), *ntp.name,
                                        *annotations, ntp.type);
    }

    // typedef typeRef name
    auto *type = visitTypeRef(ctx->typeRef());
    auto ntp = visitDeclarator(ctx->declarator(), type);
    structure->declareType(*ntp.name);
    return new P4::IR::Type_Typedef(srcInfo(ctx->declarator()), *ntp.name,
                                    *annotations, ntp.type);
}

P4::IR::Type_Declaration *P4IRConstructor::visitPackageTypeDeclaration(
    Antlr4P4Parser::PackageTypeDeclarationContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    auto *name = visitName(ctx->name());
    structure->pushContainerType(*name, false);
    auto *typeParams = visitOptTypeParameters(ctx->optTypeParameters());
    if (!typeParams->empty()) structure->markAsTemplate(*name);
    structure->declareTypes(&typeParams->parameters);
    auto *params = visitParameterList(ctx->parameterList());
    structure->declareParameters(params);
    auto *pl = new P4::IR::ParameterList(srcInfo(ctx->parameterList()), *params);
    auto *result = new P4::IR::Type_Package(srcInfo(ctx->name()), *name,
                                            *annotations, typeParams, pl);
    structure->pop();
    return result;
}

//===----------------------------------------------------------------------===//
// Extern
//===----------------------------------------------------------------------===//

P4::IR::Node *P4IRConstructor::visitExternDeclaration(
    Antlr4P4Parser::ExternDeclarationContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());

    // extern name<T> { methods }
    if (ctx->nonTypeName()) {
        auto *name = visitNonTypeName(ctx->nonTypeName());
        structure->pushContainerType(*name, true);
        auto *typeParams = visitOptTypeParameters(ctx->optTypeParameters());
        if (!typeParams->empty()) structure->markAsTemplate(*name);
        structure->declareTypes(&typeParams->parameters);
        auto *methods = visitMethodPrototypes(ctx->methodPrototypes());
        structure->pop();
        return new P4::IR::Type_Extern(srcInfo(ctx->nonTypeName()), *name,
                                       typeParams, *methods, *annotations);
    }

    // extern functionPrototype ;
    if (ctx->functionPrototype()) {
        auto *method = visitFunctionPrototype(ctx->functionPrototype());
        structure->pop();
        method->annotations = *annotations;
        return method;
    }

    // extern name ; (forward declaration)
    if (ctx->name()) {
        auto *name = visitName(ctx->name());
        structure->pushContainerType(*name, true);
        structure->pop();
        return nullptr;
    }

    BUG("Unexpected externDeclaration alternative");
}

P4::IR::Vector<P4::IR::Method> *P4IRConstructor::visitMethodPrototypes(
    Antlr4P4Parser::MethodPrototypesContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Method>();
    if (!ctx) return result;
    for (auto *mpCtx : ctx->methodPrototype()) {
        auto *method = visitMethodPrototype(mpCtx);
        if (method) result->push_back(method);
    }
    return result;
}

P4::IR::Method *P4IRConstructor::visitFunctionPrototype(
    Antlr4P4Parser::FunctionPrototypeContext *ctx) {
    auto *type = visitTypeOrVoid(ctx->typeOrVoid());
    auto *name = visitName(ctx->name());
    auto *typeParams = visitOptTypeParameters(ctx->optTypeParameters());
    structure->declareObject(*name, type->toString());
    if (!typeParams->empty()) structure->markAsTemplate(*name);
    structure->pushNamespace(srcInfo(ctx->name()), false);
    structure->declareTypes(&typeParams->parameters);
    auto *params = visitParameterList(ctx->parameterList());
    structure->declareParameters(params);
    auto *pl = new P4::IR::ParameterList(srcInfo(ctx->parameterList()), *params);
    auto *mt = new P4::IR::Type_Method(srcInfo(ctx->name()), typeParams, type, pl, *name);
    return new P4::IR::Method(srcInfo(ctx->name()), *name, mt);
}

P4::IR::Method *P4IRConstructor::visitMethodPrototype(
    Antlr4P4Parser::MethodPrototypeContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());

    // Constructor: IDENTIFIER ( parameterList ) ;
    if (ctx->IDENTIFIER()) {
        auto si = srcInfo(ctx->IDENTIFIER()->getSymbol());
        auto name = P4::cstring(ctx->IDENTIFIER()->getText());
        auto *params = visitParameterList(ctx->parameterList());
        auto *pl = new P4::IR::ParameterList(srcInfo(ctx->parameterList()), *params);
        auto *mt = new P4::IR::Type_Method(si, pl, name);
        return new P4::IR::Method(si, P4::IR::ID(si, name), mt, *annotations);
    }

    // Regular or abstract method
    auto *method = visitFunctionPrototype(ctx->functionPrototype());
    structure->pop();
    method->annotations = *annotations;
    if (ctx->ABSTRACT()) method->setAbstract();
    return method;
}

//===----------------------------------------------------------------------===//
// Parser
//===----------------------------------------------------------------------===//

P4::IR::Type_Declaration *P4IRConstructor::visitParserDeclaration(
    Antlr4P4Parser::ParserDeclarationContext *ctx) {
    auto *parserType = visitParserTypeDeclaration(ctx->parserTypeDeclaration());
    auto *ctorParams = visitOptConstructorParameters(ctx->optConstructorParameters());
    auto *locals = visitParserLocalElements(ctx->parserLocalElements());
    auto *states = visitParserStates(ctx->parserStates());
    structure->pop();
    auto *pl = new P4::IR::ParameterList(srcInfo(ctx->optConstructorParameters()), *ctorParams);
    return new P4::IR::P4Parser(parserType->name.srcInfo, parserType->name,
                                parserType, pl, *locals, *states);
}

P4::IR::Type_Parser *P4IRConstructor::visitParserTypeDeclaration(
    Antlr4P4Parser::ParserTypeDeclarationContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    auto *name = visitName(ctx->name());
    structure->pushContainerType(*name, true);
    auto *typeParams = visitOptTypeParameters(ctx->optTypeParameters());
    if (!typeParams->empty()) structure->markAsTemplate(*name);
    structure->declareTypes(&typeParams->parameters);
    auto *params = visitParameterList(ctx->parameterList());
    structure->declareParameters(params);
    auto *pl = new P4::IR::ParameterList(srcInfo(ctx->parameterList()), *params);
    return new P4::IR::Type_Parser(srcInfo(ctx->name()), *name, *annotations, typeParams, pl);
}

P4::IR::IndexedVector<P4::IR::Declaration> *P4IRConstructor::visitParserLocalElements(
    Antlr4P4Parser::ParserLocalElementsContext *ctx) {
    auto *result = new P4::IR::IndexedVector<P4::IR::Declaration>();
    if (!ctx) return result;
    for (auto *elemCtx : ctx->parserLocalElement()) {
        result->push_back(visitParserLocalElement(elemCtx));
    }
    return result;
}

P4::IR::Declaration *P4IRConstructor::visitParserLocalElement(
    Antlr4P4Parser::ParserLocalElementContext *ctx) {
    if (ctx->constantDeclaration()) return visitConstantDeclaration(ctx->constantDeclaration());
    if (ctx->instantiation()) return visitInstantiation(ctx->instantiation());
    if (ctx->variableDeclaration()) return visitVariableDeclaration(ctx->variableDeclaration());
    if (ctx->valueSetDeclaration()) return visitValueSetDeclaration(ctx->valueSetDeclaration());
    BUG("Unexpected parserLocalElement alternative");
}

P4::IR::IndexedVector<P4::IR::ParserState> *P4IRConstructor::visitParserStates(
    Antlr4P4Parser::ParserStatesContext *ctx) {
    auto *result = new P4::IR::IndexedVector<P4::IR::ParserState>();
    for (auto *stateCtx : ctx->parserState()) {
        result->push_back(visitParserState(stateCtx));
    }
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::ParserState *P4IRConstructor::visitParserState(
    Antlr4P4Parser::ParserStateContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    auto *name = visitName(ctx->name());
    structure->pushContainerType(*name, false);
    auto *stmts = visitParserStatements(ctx->parserStatements());
    auto *transition = visitTransitionStatement(ctx->transitionStatement());
    structure->pop();
    return new P4::IR::ParserState(srcInfo(ctx->name()), *name, *annotations, *stmts, transition);
}

P4::IR::IndexedVector<P4::IR::StatOrDecl> *P4IRConstructor::visitParserStatements(
    Antlr4P4Parser::ParserStatementsContext *ctx) {
    auto *result = new P4::IR::IndexedVector<P4::IR::StatOrDecl>();
    if (!ctx) return result;
    for (auto *stmtCtx : ctx->parserStatement()) {
        result->push_back(visitParserStatement(stmtCtx));
    }
    return result;
}

P4::IR::StatOrDecl *P4IRConstructor::visitParserStatement(
    Antlr4P4Parser::ParserStatementContext *ctx) {
    if (ctx->assignmentOrMethodCallStatement())
        return visitAssignmentOrMethodCallStatement(ctx->assignmentOrMethodCallStatement());
    if (ctx->directApplication())
        return visitDirectApplication(ctx->directApplication());
    if (ctx->emptyStatement())
        return visitEmptyStatement(ctx->emptyStatement());
    if (ctx->variableDeclaration())
        return visitVariableDeclaration(ctx->variableDeclaration());
    if (ctx->constantDeclaration())
        return visitConstantDeclaration(ctx->constantDeclaration());
    if (ctx->parserBlockStatement())
        return visitParserBlockStatement(ctx->parserBlockStatement());
    if (ctx->conditionalStatement())
        return visitConditionalStatement(ctx->conditionalStatement());
    BUG("Unexpected parserStatement alternative");
}

P4::IR::BlockStatement *P4IRConstructor::visitParserBlockStatement(
    Antlr4P4Parser::ParserBlockStatementContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    structure->pushNamespace(srcInfo(ctx), false);
    auto *stmts = visitParserStatements(ctx->parserStatements());
    structure->pop();
    return new P4::IR::BlockStatement(srcInfo(ctx), *annotations, *stmts);
}

P4::IR::Expression *P4IRConstructor::visitTransitionStatement(
    Antlr4P4Parser::TransitionStatementContext *ctx) {
    if (!ctx || !ctx->stateExpression()) return nullptr;
    return visitStateExpression(ctx->stateExpression());
}

P4::IR::Expression *P4IRConstructor::visitStateExpression(
    Antlr4P4Parser::StateExpressionContext *ctx) {
    if (ctx->name()) {
        auto *id = visitName(ctx->name());
        return new P4::IR::PathExpression(*id);
    }
    return visitSelectExpression(ctx->selectExpression());
}

P4::IR::Expression *P4IRConstructor::visitSelectExpression(
    Antlr4P4Parser::SelectExpressionContext *ctx) {
    auto *exprList = visitExpressionList(ctx->expressionList());
    auto *cases = visitSelectCaseList(ctx->selectCaseList());
    auto *listExpr = new P4::IR::ListExpression(srcInfo(ctx->expressionList()), *exprList);
    return new P4::IR::SelectExpression(srcInfo(ctx), listExpr, std::move(*cases));
}

P4::IR::Vector<P4::IR::SelectCase> *P4IRConstructor::visitSelectCaseList(
    Antlr4P4Parser::SelectCaseListContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::SelectCase>();
    if (!ctx) return result;
    for (auto *caseCtx : ctx->selectCase()) {
        result->push_back(visitSelectCase(caseCtx));
    }
    return result;
}

P4::IR::SelectCase *P4IRConstructor::visitSelectCase(
    Antlr4P4Parser::SelectCaseContext *ctx) {
    auto *keyset = visitKeysetExpression(ctx->keysetExpression());
    auto *name = visitName(ctx->name());
    auto *expr = new P4::IR::PathExpression(*name);
    return new P4::IR::SelectCase(srcInfo(ctx), keyset, expr);
}

P4::IR::Expression *P4IRConstructor::visitKeysetExpression(
    Antlr4P4Parser::KeysetExpressionContext *ctx) {
    if (ctx->tupleKeysetExpression()) {
        auto *elems = visitTupleKeysetExpression(ctx->tupleKeysetExpression());
        return new P4::IR::ListExpression(srcInfo(ctx), *elems);
    }
    return visitSimpleKeysetExpression(ctx->simpleKeysetExpression());
}

P4::IR::Vector<P4::IR::Expression> *P4IRConstructor::visitTupleKeysetExpression(
    Antlr4P4Parser::TupleKeysetExpressionContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Expression>();

    if (ctx->simpleExpressionList()) {
        // (simpleKeysetExpression, simpleExpressionList)
        result->push_back(visitSimpleKeysetExpression(ctx->simpleKeysetExpression()));
        for (auto *skeCtx : ctx->simpleExpressionList()->simpleKeysetExpression()) {
            result->push_back(visitSimpleKeysetExpression(skeCtx));
        }
    } else if (ctx->reducedSimpleKeysetExpression()) {
        result->push_back(visitReducedSimpleKeysetExpression(
            ctx->reducedSimpleKeysetExpression()));
    }

    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Expression *P4IRConstructor::visitSimpleKeysetExpression(
    Antlr4P4Parser::SimpleKeysetExpressionContext *ctx) {
    auto si = srcInfo(ctx);
    if (ctx->DEFAULT()) return new P4::IR::DefaultExpression(si);
    if (ctx->DONTCARE()) return new P4::IR::DefaultExpression(si);

    auto exprs = ctx->expression();
    if (ctx->MASK()) {
        return new P4::IR::Mask(si, visitExpression(exprs[0]), visitExpression(exprs[1]));
    }
    if (ctx->RANGE()) {
        return new P4::IR::Range(si, visitExpression(exprs[0]), visitExpression(exprs[1]));
    }
    return visitExpression(exprs[0]);
}

P4::IR::Expression *P4IRConstructor::visitReducedSimpleKeysetExpression(
    Antlr4P4Parser::ReducedSimpleKeysetExpressionContext *ctx) {
    auto si = srcInfo(ctx);
    if (ctx->DEFAULT()) return new P4::IR::DefaultExpression(si);
    if (ctx->DONTCARE()) return new P4::IR::DefaultExpression(si);

    auto exprs = ctx->expression();
    if (ctx->MASK()) {
        return new P4::IR::Mask(si, visitExpression(exprs[0]), visitExpression(exprs[1]));
    }
    if (ctx->RANGE()) {
        return new P4::IR::Range(si, visitExpression(exprs[0]), visitExpression(exprs[1]));
    }
    BUG("Unexpected reducedSimpleKeysetExpression alternative");
}

P4::IR::Declaration *P4IRConstructor::visitValueSetDeclaration(
    Antlr4P4Parser::ValueSetDeclarationContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    const P4::IR::Type *type = nullptr;
    if (ctx->baseType()) type = visitBaseType(ctx->baseType());
    else if (ctx->tupleType()) type = visitTupleType(ctx->tupleType());
    else if (ctx->typeName()) type = visitTypeName(ctx->typeName());

    auto *size = visitExpression(ctx->expression());
    auto *name = visitName(ctx->name());
    return new P4::IR::P4ValueSet(srcInfo(ctx->name()), *name, *annotations, type, size);
}

//===----------------------------------------------------------------------===//
// Control
//===----------------------------------------------------------------------===//

P4::IR::Type_Declaration *P4IRConstructor::visitControlDeclaration(
    Antlr4P4Parser::ControlDeclarationContext *ctx) {
    auto *controlType = visitControlTypeDeclaration(ctx->controlTypeDeclaration());
    auto *ctorParams = visitOptConstructorParameters(ctx->optConstructorParameters());
    auto *locals = visitControlLocalDeclarations(ctx->controlLocalDeclarations());
    auto *body = visitControlBody(ctx->controlBody());
    structure->pop();
    auto *pl = new P4::IR::ParameterList(srcInfo(ctx->optConstructorParameters()), *ctorParams);
    return new P4::IR::P4Control(controlType->name.srcInfo, controlType->name,
                                 controlType, pl, *locals, body);
}

P4::IR::Type_Control *P4IRConstructor::visitControlTypeDeclaration(
    Antlr4P4Parser::ControlTypeDeclarationContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    auto *name = visitName(ctx->name());
    structure->pushContainerType(*name, true);
    auto *typeParams = visitOptTypeParameters(ctx->optTypeParameters());
    if (!typeParams->empty()) structure->markAsTemplate(*name);
    structure->declareTypes(&typeParams->parameters);
    auto *params = visitParameterList(ctx->parameterList());
    structure->declareParameters(params);
    auto *pl = new P4::IR::ParameterList(srcInfo(ctx->parameterList()), *params);
    return new P4::IR::Type_Control(srcInfo(ctx->name()), *name, *annotations, typeParams, pl);
}

P4::IR::IndexedVector<P4::IR::Declaration> *P4IRConstructor::visitControlLocalDeclarations(
    Antlr4P4Parser::ControlLocalDeclarationsContext *ctx) {
    auto *result = new P4::IR::IndexedVector<P4::IR::Declaration>();
    if (!ctx) return result;
    for (auto *declCtx : ctx->controlLocalDeclaration()) {
        result->push_back(visitControlLocalDeclaration(declCtx));
    }
    return result;
}

P4::IR::Declaration *P4IRConstructor::visitControlLocalDeclaration(
    Antlr4P4Parser::ControlLocalDeclarationContext *ctx) {
    if (ctx->constantDeclaration()) return visitConstantDeclaration(ctx->constantDeclaration());
    if (ctx->actionDeclaration()) return visitActionDeclaration(ctx->actionDeclaration());
    if (ctx->tableDeclaration()) return visitTableDeclaration(ctx->tableDeclaration());
    if (ctx->instantiation()) return visitInstantiation(ctx->instantiation());
    if (ctx->variableDeclaration()) return visitVariableDeclaration(ctx->variableDeclaration());
    BUG("Unexpected controlLocalDeclaration alternative");
}

P4::IR::BlockStatement *P4IRConstructor::visitControlBody(
    Antlr4P4Parser::ControlBodyContext *ctx) {
    return visitBlockStatement(ctx->blockStatement());
}

//===----------------------------------------------------------------------===//
// Action
//===----------------------------------------------------------------------===//

P4::IR::Declaration *P4IRConstructor::visitActionDeclaration(
    Antlr4P4Parser::ActionDeclarationContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    auto *name = visitName(ctx->name());
    auto *params = visitParameterList(ctx->parameterList());
    auto *body = visitBlockStatement(ctx->blockStatement());
    auto *pl = new P4::IR::ParameterList(srcInfo(ctx->parameterList()), *params);
    return new P4::IR::P4Action(srcInfo(ctx->name()), *name, *annotations, pl, body);
}

//===----------------------------------------------------------------------===//
// Table
//===----------------------------------------------------------------------===//

P4::IR::Declaration *P4IRConstructor::visitTableDeclaration(
    Antlr4P4Parser::TableDeclarationContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    auto *name = visitName(ctx->name());
    auto *props = visitTablePropertyList(ctx->tablePropertyList());
    return new P4::IR::P4Table(srcInfo(ctx->name()), *name, *annotations,
                               new P4::IR::TableProperties(srcInfo(ctx->tablePropertyList()), *props));
}

P4::IR::IndexedVector<P4::IR::Property> *P4IRConstructor::visitTablePropertyList(
    Antlr4P4Parser::TablePropertyListContext *ctx) {
    auto *result = new P4::IR::IndexedVector<P4::IR::Property>();
    for (auto *propCtx : ctx->tableProperty()) {
        result->push_back(visitTableProperty(propCtx));
    }
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Property *P4IRConstructor::visitTableProperty(
    Antlr4P4Parser::TablePropertyContext *ctx) {
    auto si = srcInfo(ctx);

    // key = { ... }
    if (ctx->KEY()) {
        auto *keys = visitKeyElementList(ctx->keyElementList());
        auto *v = new P4::IR::Key(srcInfo(ctx->keyElementList()), *keys);
        auto id = P4::IR::ID(srcInfo(ctx->KEY()->getSymbol()), "key"_cs);
        return new P4::IR::Property(si, id, v, false);
    }

    // actions = { ... }
    if (ctx->ACTIONS()) {
        auto *actions = visitActionList(ctx->actionList());
        auto *v = new P4::IR::ActionList(srcInfo(ctx->actionList()), *actions);
        auto id = P4::IR::ID(srcInfo(ctx->ACTIONS()->getSymbol()), "actions"_cs);
        return new P4::IR::Property(si, id, v, false);
    }

    // [const] entries = { ... }
    if (ctx->ENTRIES()) {
        auto *annotations = visitOptAnnotations(ctx->optAnnotations());
        bool isConst = visitOptCONST(ctx->optCONST());
        auto *entries = visitEntriesList(ctx->entriesList());
        auto *v = new P4::IR::EntriesList(srcInfo(ctx->ENTRIES()->getSymbol()), *entries);
        auto id = P4::IR::ID(srcInfo(ctx->ENTRIES()->getSymbol()), "entries"_cs);
        return new P4::IR::Property(srcInfo(ctx->ENTRIES()->getSymbol()), id,
                                    *annotations, v, isConst);
    }

    // [const] name = initializer ;
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    bool isConst = visitOptCONST(ctx->optCONST());
    auto *name = visitNonTableKwName(ctx->nonTableKwName());
    auto *init = visitInitializer(ctx->initializer());
    auto *v = new P4::IR::ExpressionValue(srcInfo(ctx->initializer()), init);
    return new P4::IR::Property(name->srcInfo, *name, *annotations, v, isConst);
}

bool P4IRConstructor::visitOptCONST(Antlr4P4Parser::OptCONSTContext *ctx) {
    return ctx && ctx->CONST();
}

P4::IR::Vector<P4::IR::KeyElement> *P4IRConstructor::visitKeyElementList(
    Antlr4P4Parser::KeyElementListContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::KeyElement>();
    if (!ctx) return result;
    for (auto *keyCtx : ctx->keyElement()) {
        result->push_back(visitKeyElement(keyCtx));
    }
    return result;
}

P4::IR::KeyElement *P4IRConstructor::visitKeyElement(
    Antlr4P4Parser::KeyElementContext *ctx) {
    auto *expr = visitExpression(ctx->expression());
    auto *name = visitName(ctx->name());
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    auto *matchKind = new P4::IR::PathExpression(*name);
    return new P4::IR::KeyElement(srcInfo(ctx), expr, matchKind, *annotations);
}

P4::IR::IndexedVector<P4::IR::ActionListElement> *P4IRConstructor::visitActionList(
    Antlr4P4Parser::ActionListContext *ctx) {
    auto *result = new P4::IR::IndexedVector<P4::IR::ActionListElement>();
    if (!ctx) return result;

    // The grammar has: (optAnnotations actionRef SEMICOLON)*
    auto annotations = ctx->optAnnotations();
    auto actionRefs = ctx->actionRef();

    for (size_t i = 0; i < actionRefs.size(); ++i) {
        auto *annots = visitOptAnnotations(annotations[i]);
        auto *ref = visitActionRef(actionRefs[i]);
        result->push_back(new P4::IR::ActionListElement(
            srcInfo(actionRefs[i]), *annots, ref));
    }
    return result;
}

P4::IR::Expression *P4IRConstructor::visitActionRef(
    Antlr4P4Parser::ActionRefContext *ctx) {
    auto *path = visitPrefixedNonTypeName(ctx->prefixedNonTypeName());
    if (ctx->argumentList()) {
        auto *args = visitArgumentList(ctx->argumentList());
        return new P4::IR::MethodCallExpression(srcInfo(ctx),
            new P4::IR::PathExpression(path), args);
    }
    return new P4::IR::PathExpression(path);
}

P4::IR::Path *P4IRConstructor::visitPrefixedNonTypeName(
    Antlr4P4Parser::PrefixedNonTypeNameContext *ctx) {
    auto *name = visitNonTypeName(ctx->nonTypeName());
    if (ctx->DOT()) {
        return new P4::IR::Path(*name, true);
    }
    return new P4::IR::Path(*name);
}

P4::IR::Vector<P4::IR::Entry> *P4IRConstructor::visitEntriesList(
    Antlr4P4Parser::EntriesListContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Entry>();
    if (!ctx) return result;
    for (auto *entryCtx : ctx->entry()) {
        result->push_back(visitEntry(entryCtx));
    }
    return result;
}

P4::IR::Entry *P4IRConstructor::visitEntry(Antlr4P4Parser::EntryContext *ctx) {
    bool isConst = visitOptCONST(ctx->optCONST());
    auto *keyset = visitKeysetExpression(ctx->keysetExpression());
    auto *action = visitActionRef(ctx->actionRef());
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    P4::IR::Expression *priority = nullptr;
    if (ctx->entryPriority()) {
        priority = visitEntryPriority(ctx->entryPriority());
    }

    if (auto *l = keyset->to<P4::IR::ListExpression>()) {
        return new P4::IR::Entry(srcInfo(ctx), *annotations, isConst, priority, l, action, false);
    }
    P4::IR::Vector<P4::IR::Expression> le(keyset);
    return new P4::IR::Entry(srcInfo(ctx), *annotations, isConst, priority,
                             new P4::IR::ListExpression(srcInfo(ctx->keysetExpression()), le),
                             action, true);
}

P4::IR::Expression *P4IRConstructor::visitEntryPriority(
    Antlr4P4Parser::EntryPriorityContext *ctx) {
    if (ctx->INTEGER()) {
        return parseIntegerToken(ctx->INTEGER()->getSymbol());
    }
    return visitExpression(ctx->expression());
}

//===----------------------------------------------------------------------===//
// Function
//===----------------------------------------------------------------------===//

P4::IR::Declaration *P4IRConstructor::visitFunctionDeclaration(
    Antlr4P4Parser::FunctionDeclarationContext *ctx) {
    auto *proto = visitFunctionPrototype(ctx->functionPrototype());
    auto *body = visitBlockStatement(ctx->blockStatement());
    structure->pop();

    if (ctx->annotations()) {
        auto *annotations = visitAnnotations(ctx->annotations());
        return new P4::IR::Function(proto->srcInfo, proto->name, *annotations,
                                    proto->type, body);
    }
    return new P4::IR::Function(proto->srcInfo, proto->name, proto->type, body);
}

//===----------------------------------------------------------------------===//
// Arguments
//===----------------------------------------------------------------------===//

P4::IR::Vector<P4::IR::Argument> *P4IRConstructor::visitArgumentList(
    Antlr4P4Parser::ArgumentListContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Argument>();
    if (!ctx || !ctx->nonEmptyArgList()) return result;
    for (auto *argCtx : ctx->nonEmptyArgList()->argument()) {
        result->push_back(visitArgument(argCtx));
    }
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Argument *P4IRConstructor::visitArgument(Antlr4P4Parser::ArgumentContext *ctx) {
    auto si = srcInfo(ctx);

    // name = expression or name = _
    if (ctx->name()) {
        auto *name = visitName(ctx->name());
        if (ctx->DONTCARE()) {
            return new P4::IR::Argument(si, *name,
                new P4::IR::DefaultExpression(srcInfo(ctx->DONTCARE()->getSymbol())));
        }
        auto *expr = visitExpression(ctx->expression());
        return new P4::IR::Argument(si, *name, expr);
    }

    // _ (don't care)
    if (ctx->DONTCARE()) {
        return new P4::IR::Argument(si,
            new P4::IR::DefaultExpression(srcInfo(ctx->DONTCARE()->getSymbol())));
    }

    // expression
    auto *expr = visitExpression(ctx->expression());
    return new P4::IR::Argument(si, expr);
}

P4::IR::Vector<P4::IR::Expression> *P4IRConstructor::visitExpressionList(
    Antlr4P4Parser::ExpressionListContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Expression>();
    if (!ctx) return result;
    for (auto *exprCtx : ctx->expression()) {
        result->push_back(visitExpression(exprCtx));
    }
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

//===----------------------------------------------------------------------===//
// KV pairs
//===----------------------------------------------------------------------===//

P4::IR::IndexedVector<P4::IR::NamedExpression> *P4IRConstructor::visitKvList(
    Antlr4P4Parser::KvListContext *ctx) {
    auto *result = new P4::IR::IndexedVector<P4::IR::NamedExpression>();
    for (auto *kvCtx : ctx->kvPair()) {
        result->push_back(visitKvPair(kvCtx));
    }
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::NamedExpression *P4IRConstructor::visitKvPair(
    Antlr4P4Parser::KvPairContext *ctx) {
    auto *name = visitName(ctx->name());
    auto *expr = visitExpression(ctx->expression());
    return new P4::IR::NamedExpression(srcInfo(ctx), *name, expr);
}

//===----------------------------------------------------------------------===//
// Statements
//===----------------------------------------------------------------------===//

P4::IR::Statement *P4IRConstructor::visitStatement(
    Antlr4P4Parser::StatementContext *ctx) {
    if (ctx->assignmentOrMethodCallStatement())
        return visitAssignmentOrMethodCallStatement(ctx->assignmentOrMethodCallStatement());
    if (ctx->directApplication())
        return visitDirectApplication(ctx->directApplication());
    if (ctx->conditionalStatement())
        return visitConditionalStatement(ctx->conditionalStatement());
    if (ctx->emptyStatement())
        return visitEmptyStatement(ctx->emptyStatement());
    if (ctx->blockStatement())
        return visitBlockStatement(ctx->blockStatement());
    if (ctx->returnStatement())
        return visitReturnStatement(ctx->returnStatement());
    if (ctx->breakStatement())
        return visitBreakStatement(ctx->breakStatement());
    if (ctx->continueStatement())
        return visitContinueStatement(ctx->continueStatement());
    if (ctx->exitStatement())
        return visitExitStatement(ctx->exitStatement());
    if (ctx->switchStatement())
        return visitSwitchStatement(ctx->switchStatement());
    if (ctx->forStatement())
        return visitForStatement(ctx->forStatement());
    BUG("Unexpected statement alternative");
}

P4::IR::Statement *P4IRConstructor::visitAssignmentOrMethodCallStatement(
    Antlr4P4Parser::AssignmentOrMethodCallStatementContext *ctx) {
    auto si = srcInfo(ctx);

    // Use the labelled alternative context type to determine which alternative
    if (auto *mc = dynamic_cast<Antlr4P4Parser::MethodCallStmtContext *>(ctx)) {
        auto *lval = visitLvalue(mc->lvalue());
        auto *args = visitArgumentList(mc->argumentList());
        // Check for direct application: lvalue.apply(args) where lvalue base is a type.
        // In the Bison parser, this matches directApplication (typeName DOT APPLY ...)
        // but ANTLR4 can't distinguish types from identifiers, so it matches
        // methodCallStmt instead. Fix by checking the symbol table.
        if (auto *member = lval->to<P4::IR::Member>()) {
            if (member->member == "apply") {
                if (auto *pathExpr = member->expr->to<P4::IR::PathExpression>()) {
                    auto pathName = pathExpr->path->name.name;
                    auto kind = structure->lookupIdentifier(pathName);
                    if (kind == P4::Util::ProgramStructure::SymbolKind::Type ||
                        kind == P4::Util::ProgramStructure::SymbolKind::TemplateType) {
                        // This is a direct application: TypeName.apply(args)
                        auto *typeName = visitTypeName(std::string(pathName),
                                                       pathExpr->srcInfo);
                        auto *method = new P4::IR::Member(
                            member->srcInfo,
                            new P4::IR::TypeNameExpression(typeName),
                            member->member);
                        auto *mce = new P4::IR::MethodCallExpression(si, method, args);
                        return new P4::IR::MethodCallStatement(si, mce);
                    }
                }
            }
        }
        auto *mce = new P4::IR::MethodCallExpression(si, lval,
            new P4::IR::Vector<P4::IR::Type>(), args);
        return new P4::IR::MethodCallStatement(si, mce);
    }
    if (auto *tmc = dynamic_cast<Antlr4P4Parser::TypeArgsMethodCallStmtContext *>(ctx)) {
        auto *lval = visitLvalue(tmc->lvalue());
        auto *typeArgs = visitTypeArgumentList(tmc->typeArgumentList());
        auto *args = visitArgumentList(tmc->argumentList());
        auto *mce = new P4::IR::MethodCallExpression(si, lval, typeArgs, args);
        return new P4::IR::MethodCallStatement(si, mce);
    }
    if (auto *asgn = dynamic_cast<Antlr4P4Parser::AssignmentStmtContext *>(ctx)) {
        auto *lval = visitLvalue(asgn->lvalue());
        auto *expr = visitExpression(asgn->expression());
        return new P4::IR::AssignmentStatement(si, lval, expr);
    }
    if (auto *ma = dynamic_cast<Antlr4P4Parser::MulAssignStmtContext *>(ctx)) {
        return new P4::IR::MulAssign(si, visitLvalue(ma->lvalue()), visitExpression(ma->expression()));
    }
    if (auto *da = dynamic_cast<Antlr4P4Parser::DivAssignStmtContext *>(ctx)) {
        return new P4::IR::DivAssign(si, visitLvalue(da->lvalue()), visitExpression(da->expression()));
    }
    if (auto *ma = dynamic_cast<Antlr4P4Parser::ModAssignStmtContext *>(ctx)) {
        return new P4::IR::ModAssign(si, visitLvalue(ma->lvalue()), visitExpression(ma->expression()));
    }
    if (auto *aa = dynamic_cast<Antlr4P4Parser::AddAssignStmtContext *>(ctx)) {
        return new P4::IR::AddAssign(si, visitLvalue(aa->lvalue()), visitExpression(aa->expression()));
    }
    if (auto *sa = dynamic_cast<Antlr4P4Parser::SubAssignStmtContext *>(ctx)) {
        return new P4::IR::SubAssign(si, visitLvalue(sa->lvalue()), visitExpression(sa->expression()));
    }
    if (auto *asa = dynamic_cast<Antlr4P4Parser::AddSatAssignStmtContext *>(ctx)) {
        return new P4::IR::AddSatAssign(si, visitLvalue(asa->lvalue()), visitExpression(asa->expression()));
    }
    if (auto *ssa = dynamic_cast<Antlr4P4Parser::SubSatAssignStmtContext *>(ctx)) {
        return new P4::IR::SubSatAssign(si, visitLvalue(ssa->lvalue()), visitExpression(ssa->expression()));
    }
    if (auto *sha = dynamic_cast<Antlr4P4Parser::ShlAssignStmtContext *>(ctx)) {
        return new P4::IR::ShlAssign(si, visitLvalue(sha->lvalue()), visitExpression(sha->expression()));
    }
    if (auto *sra = dynamic_cast<Antlr4P4Parser::ShrAssignStmtContext *>(ctx)) {
        return new P4::IR::ShrAssign(si, visitLvalue(sra->lvalue()), visitExpression(sra->expression()));
    }
    if (auto *ba = dynamic_cast<Antlr4P4Parser::BandAssignStmtContext *>(ctx)) {
        return new P4::IR::BAndAssign(si, visitLvalue(ba->lvalue()), visitExpression(ba->expression()));
    }
    if (auto *bo = dynamic_cast<Antlr4P4Parser::BorAssignStmtContext *>(ctx)) {
        return new P4::IR::BOrAssign(si, visitLvalue(bo->lvalue()), visitExpression(bo->expression()));
    }
    if (auto *bx = dynamic_cast<Antlr4P4Parser::BxorAssignStmtContext *>(ctx)) {
        return new P4::IR::BXorAssign(si, visitLvalue(bx->lvalue()), visitExpression(bx->expression()));
    }

    BUG("Unexpected assignmentOrMethodCallStatement alternative");
}

P4::IR::Statement *P4IRConstructor::visitEmptyStatement(
    Antlr4P4Parser::EmptyStatementContext *ctx) {
    return new P4::IR::EmptyStatement(srcInfo(ctx));
}

P4::IR::Statement *P4IRConstructor::visitExitStatement(
    Antlr4P4Parser::ExitStatementContext *ctx) {
    return new P4::IR::ExitStatement(srcInfo(ctx));
}

P4::IR::Statement *P4IRConstructor::visitReturnStatement(
    Antlr4P4Parser::ReturnStatementContext *ctx) {
    P4::IR::Expression *expr = nullptr;
    if (ctx->expression()) expr = visitExpression(ctx->expression());
    return new P4::IR::ReturnStatement(srcInfo(ctx), expr);
}

P4::IR::Statement *P4IRConstructor::visitConditionalStatement(
    Antlr4P4Parser::ConditionalStatementContext *ctx) {
    auto *cond = visitExpression(ctx->expression());
    auto *trueStmt = visitStatement(ctx->statement(0));
    P4::IR::Statement *falseStmt = nullptr;
    if (ctx->statement().size() > 1) {
        falseStmt = visitStatement(ctx->statement(1));
    }
    return new P4::IR::IfStatement(srcInfo(ctx), cond, trueStmt, falseStmt);
}

P4::IR::Statement *P4IRConstructor::visitBreakStatement(
    Antlr4P4Parser::BreakStatementContext *ctx) {
    return new P4::IR::BreakStatement(srcInfo(ctx));
}

P4::IR::Statement *P4IRConstructor::visitContinueStatement(
    Antlr4P4Parser::ContinueStatementContext *ctx) {
    return new P4::IR::ContinueStatement(srcInfo(ctx));
}

P4::IR::Statement *P4IRConstructor::visitDirectApplication(
    Antlr4P4Parser::DirectApplicationContext *ctx) {
    const P4::IR::Type *type = nullptr;
    if (ctx->typeName()) type = visitTypeName(ctx->typeName());
    else if (ctx->specializedType()) type = visitSpecializedType(ctx->specializedType());

    auto *method = new P4::IR::Member(
        srcInfo(ctx), new P4::IR::TypeNameExpression(type),
        P4::IR::ID(srcInfo(ctx->APPLY()->getSymbol()), "apply"_cs));
    auto *args = visitArgumentList(ctx->argumentList());
    auto *mce = new P4::IR::MethodCallExpression(srcInfo(ctx), method, args);
    return new P4::IR::MethodCallStatement(srcInfo(ctx), mce);
}

P4::IR::BlockStatement *P4IRConstructor::visitBlockStatement(
    Antlr4P4Parser::BlockStatementContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());
    structure->pushNamespace(srcInfo(ctx), false);
    auto *stmts = visitStatOrDeclList(ctx->statOrDeclList());
    structure->pop();
    return new P4::IR::BlockStatement(srcInfo(ctx), *annotations, *stmts);
}

P4::IR::IndexedVector<P4::IR::StatOrDecl> *P4IRConstructor::visitStatOrDeclList(
    Antlr4P4Parser::StatOrDeclListContext *ctx) {
    auto *result = new P4::IR::IndexedVector<P4::IR::StatOrDecl>();
    if (!ctx) return result;
    for (auto *sodCtx : ctx->statementOrDeclaration()) {
        result->push_back(visitStatementOrDeclaration(sodCtx));
    }
    return result;
}

P4::IR::StatOrDecl *P4IRConstructor::visitStatementOrDeclaration(
    Antlr4P4Parser::StatementOrDeclarationContext *ctx) {
    if (ctx->variableDeclaration()) return visitVariableDeclaration(ctx->variableDeclaration());
    if (ctx->constantDeclaration()) return visitConstantDeclaration(ctx->constantDeclaration());
    if (ctx->statement()) return visitStatement(ctx->statement());
    if (ctx->instantiation()) return visitInstantiation(ctx->instantiation());
    BUG("Unexpected statementOrDeclaration alternative");
}

P4::IR::Statement *P4IRConstructor::visitSwitchStatement(
    Antlr4P4Parser::SwitchStatementContext *ctx) {
    auto *expr = visitExpression(ctx->expression());
    auto *cases = visitSwitchCases(ctx->switchCases());
    return new P4::IR::SwitchStatement(srcInfo(ctx), expr, std::move(*cases));
}

P4::IR::Vector<P4::IR::SwitchCase> *P4IRConstructor::visitSwitchCases(
    Antlr4P4Parser::SwitchCasesContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::SwitchCase>();
    if (!ctx) return result;
    for (auto *caseCtx : ctx->switchCase()) {
        result->push_back(visitSwitchCase(caseCtx));
    }
    return result;
}

P4::IR::SwitchCase *P4IRConstructor::visitSwitchCase(
    Antlr4P4Parser::SwitchCaseContext *ctx) {
    auto *label = visitSwitchLabel(ctx->switchLabel());
    if (ctx->blockStatement()) {
        auto *body = visitBlockStatement(ctx->blockStatement());
        return new P4::IR::SwitchCase(srcInfo(ctx), label, body);
    }
    return new P4::IR::SwitchCase(srcInfo(ctx), label, nullptr);
}

P4::IR::Expression *P4IRConstructor::visitSwitchLabel(
    Antlr4P4Parser::SwitchLabelContext *ctx) {
    if (ctx->DEFAULT()) return new P4::IR::DefaultExpression(srcInfo(ctx));
    return visitNonBraceExpression(ctx->nonBraceExpression());
}

P4::IR::Statement *P4IRConstructor::visitForStatement(
    Antlr4P4Parser::ForStatementContext *ctx) {
    auto *annotations = visitOptAnnotations(ctx->optAnnotations());

    // C-style for loop
    if (ctx->forInitStatements()) {
        auto *inits = new P4::IR::IndexedVector<P4::IR::StatOrDecl>();
        if (ctx->forInitStatements()->declOrAssignmentOrMethodCallStatement().size() > 0) {
            for (auto *initCtx :
                 ctx->forInitStatements()->declOrAssignmentOrMethodCallStatement()) {
                if (initCtx->variableDeclarationWithoutSemicolon()) {
                    inits->push_back(visitVariableDeclarationWithoutSemicolon(
                        initCtx->variableDeclarationWithoutSemicolon()));
                } else if (initCtx->assignmentOrMethodCallStatementWithoutSemicolon()) {
                    // Handle the without-semicolon variant
                    auto *amcCtx = initCtx->assignmentOrMethodCallStatementWithoutSemicolon();
                    auto *lval = visitLvalue(amcCtx->lvalue());
                    if (amcCtx->argumentList()) {
                        auto *args = visitArgumentList(amcCtx->argumentList());
                        if (amcCtx->typeArgumentList()) {
                            auto *typeArgs = visitTypeArgumentList(amcCtx->typeArgumentList());
                            auto *mce = new P4::IR::MethodCallExpression(
                                srcInfo(amcCtx), lval, typeArgs, args);
                            inits->push_back(new P4::IR::MethodCallStatement(srcInfo(amcCtx), mce));
                        } else {
                            auto *mce = new P4::IR::MethodCallExpression(
                                srcInfo(amcCtx), lval,
                                new P4::IR::Vector<P4::IR::Type>(), args);
                            inits->push_back(new P4::IR::MethodCallStatement(srcInfo(amcCtx), mce));
                        }
                    } else if (amcCtx->ASSIGN()) {
                        auto *expr = visitExpression(amcCtx->expression());
                        inits->push_back(new P4::IR::AssignmentStatement(srcInfo(amcCtx), lval, expr));
                    }
                    // Compound assignments handled similarly...
                }
            }
        }

        auto *cond = visitExpression(ctx->expression());

        auto *updates = new P4::IR::IndexedVector<P4::IR::StatOrDecl>();
        if (ctx->forUpdateStatements()) {
            for (auto *updCtx :
                 ctx->forUpdateStatements()->assignmentOrMethodCallStatementWithoutSemicolon()) {
                auto *lval = visitLvalue(updCtx->lvalue());
                if (updCtx->argumentList()) {
                    auto *args = visitArgumentList(updCtx->argumentList());
                    auto *mce = new P4::IR::MethodCallExpression(
                        srcInfo(updCtx), lval,
                        new P4::IR::Vector<P4::IR::Type>(), args);
                    updates->push_back(new P4::IR::MethodCallStatement(srcInfo(updCtx), mce));
                } else if (updCtx->ASSIGN()) {
                    auto *expr = visitExpression(updCtx->expression());
                    updates->push_back(new P4::IR::AssignmentStatement(srcInfo(updCtx), lval, expr));
                }
            }
        }

        auto *body = visitStatement(ctx->statement());
        return new P4::IR::ForStatement(srcInfo(ctx), *annotations, *inits, cond, *updates, body);
    }

    // For-in loop: for (typeRef name in expr) stmt
    // or: for (annotations typeRef name in expr) stmt
    if (ctx->IN()) {
        P4::IR::Vector<P4::IR::Annotation> declAnnotations;
        if (ctx->annotations()) {
            declAnnotations = *visitAnnotations(ctx->annotations());
        }
        auto *type = visitTypeRef(ctx->typeRef());
        auto *name = visitName(ctx->name());

        // Get collection from forCollectionExpr
        P4::IR::Expression *collection = nullptr;
        auto *fce = ctx->forCollectionExpr();
        BUG_CHECK(fce != nullptr, "For-in statement missing collection expression");
        if (fce->RANGE()) {
            collection = new P4::IR::Range(
                srcInfo(fce),
                visitExpression(fce->expression(0)),
                visitExpression(fce->expression(1)));
        } else if (fce->typeRef()) {
            auto *t = visitTypeRef(fce->typeRef());
            collection = new P4::IR::ConstructorCallExpression(
                srcInfo(fce), t, {});
        } else {
            collection = visitExpression(fce->expression(0));
        }

        auto *decl = new P4::IR::Declaration_Variable(
            srcInfo(ctx->typeRef()) + srcInfo(ctx->name()), *name, declAnnotations, type);
        auto *body = visitStatement(ctx->statement());
        return new P4::IR::ForInStatement(srcInfo(ctx), *annotations, decl, collection, body);
    }

    BUG("Unexpected forStatement alternative");
}

//===----------------------------------------------------------------------===//
// Lvalue
//===----------------------------------------------------------------------===//

P4::IR::Expression *P4IRConstructor::visitLvalue(Antlr4P4Parser::LvalueContext *ctx) {
    // Path lvalue: prefixedNonTypeName
    if (auto *plv = dynamic_cast<Antlr4P4Parser::PathLvalueContext *>(ctx)) {
        auto *path = visitPrefixedNonTypeName(plv->prefixedNonTypeName());
        return new P4::IR::PathExpression(path);
    }
    // this
    if (dynamic_cast<Antlr4P4Parser::ThisLvalueContext *>(ctx)) {
        return new P4::IR::This(srcInfo(ctx));
    }
    // lvalue.name
    if (auto *mlv = dynamic_cast<Antlr4P4Parser::MemberLvalueContext *>(ctx)) {
        auto *base = visitLvalue(mlv->lvalue());
        auto *name = visitName(mlv->name());
        return new P4::IR::Member(srcInfo(ctx), base, *name);
    }
    // lvalue[expr]
    if (auto *ilv = dynamic_cast<Antlr4P4Parser::IndexLvalueContext *>(ctx)) {
        auto *base = visitLvalue(ilv->lvalue());
        auto *index = visitExpression(ilv->expression());
        return new P4::IR::ArrayIndex(srcInfo(ctx), base, index);
    }
    // lvalue[expr:expr]
    if (auto *slv = dynamic_cast<Antlr4P4Parser::SliceLvalueContext *>(ctx)) {
        auto *base = visitLvalue(slv->lvalue());
        auto *hi = visitExpression(slv->expression(0));
        auto *lo = visitExpression(slv->expression(1));
        return new P4::IR::Slice(srcInfo(ctx), base, hi, lo);
    }
    // lvalue[expr+:expr]
    if (auto *pslv = dynamic_cast<Antlr4P4Parser::PlusSliceLvalueContext *>(ctx)) {
        auto *base = visitLvalue(pslv->lvalue());
        auto *e = visitExpression(pslv->expression(0));
        auto *w = visitExpression(pslv->expression(1));
        return new P4::IR::PlusSlice(srcInfo(ctx), base, e, w);
    }
    // (lvalue)
    if (auto *plv = dynamic_cast<Antlr4P4Parser::ParenLvalueContext *>(ctx)) {
        return visitLvalue(plv->lvalue());
    }
    BUG("Unexpected lvalue alternative");
}

//===----------------------------------------------------------------------===//
// Expressions
//===----------------------------------------------------------------------===//

P4::IR::Expression *P4IRConstructor::visitExpression(
    Antlr4P4Parser::ExpressionContext *ctx) {
    auto si = srcInfo(ctx);

    // Labelled alternatives
    if (auto *e = dynamic_cast<Antlr4P4Parser::IntegerExprContext *>(ctx)) {
        return parseIntegerToken(e->INTEGER()->getSymbol());
    }
    if (dynamic_cast<Antlr4P4Parser::DotsExprContext *>(ctx)) {
        return new P4::IR::Dots(si);
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::StringLiteralExprContext *>(ctx)) {
        auto text = e->STRING_LITERAL()->getText();
        // Remove quotes
        auto content = text.substr(1, text.size() - 2);
        return new P4::IR::StringLiteral(si, P4::cstring(content));
    }
    if (dynamic_cast<Antlr4P4Parser::TrueExprContext *>(ctx)) {
        return new P4::IR::BoolLiteral(si, true);
    }
    if (dynamic_cast<Antlr4P4Parser::FalseExprContext *>(ctx)) {
        return new P4::IR::BoolLiteral(si, false);
    }
    if (dynamic_cast<Antlr4P4Parser::ThisExprContext *>(ctx)) {
        return new P4::IR::This(si);
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::PathExprContext *>(ctx)) {
        auto *path = visitPrefixedNonTypeName(e->prefixedNonTypeName());
        return new P4::IR::PathExpression(path);
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::ParenExprContext *>(ctx)) {
        return visitExpression(e->expression());
    }
    if (dynamic_cast<Antlr4P4Parser::InvalidExprContext *>(ctx)) {
        return new P4::IR::Invalid(si, P4::IR::Type::Unknown::get());
    }

    // List expression: { exprList }
    if (auto *e = dynamic_cast<Antlr4P4Parser::ListExprContext *>(ctx)) {
        auto *exprs = visitExpressionList(e->expressionList());
        return new P4::IR::ListExpression(si, *exprs);
    }
    // Struct expression: { kvList }
    if (auto *e = dynamic_cast<Antlr4P4Parser::StructExprContext *>(ctx)) {
        auto *kvs = visitKvList(e->kvList());
        return new P4::IR::StructExpression(
            si, P4::IR::Type::Unknown::get(), (P4::IR::Type_Name *)nullptr, *kvs);
    }
    // Struct with dots: { kvList, ... }
    if (auto *e = dynamic_cast<Antlr4P4Parser::StructDotsExprContext *>(ctx)) {
        auto *kvs = visitKvList(e->kvList());
        kvs->push_back(new P4::IR::NamedDots(srcInfo(e->DOTS()->getSymbol())));
        return new P4::IR::StructExpression(
            si, P4::IR::Type::Unknown::get(), (P4::IR::Type_Name *)nullptr, *kvs);
    }

    // Unary operators
    if (auto *e = dynamic_cast<Antlr4P4Parser::LnotExprContext *>(ctx)) {
        return new P4::IR::LNot(si, visitExpression(e->expression()));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::CmplExprContext *>(ctx)) {
        return new P4::IR::Cmpl(si, visitExpression(e->expression()));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::NegExprContext *>(ctx)) {
        return new P4::IR::Neg(si, visitExpression(e->expression()));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::UplusExprContext *>(ctx)) {
        return new P4::IR::UPlus(si, visitExpression(e->expression()));
    }

    // Cast: (typeRef) expression
    if (auto *e = dynamic_cast<Antlr4P4Parser::CastExprContext *>(ctx)) {
        auto *type = visitTypeRef(e->typeRef());
        auto *expr = visitExpression(e->expression());
        return new P4::IR::Cast(si, type, expr);
    }

    // Binary operators
    if (auto *e = dynamic_cast<Antlr4P4Parser::MulExprContext *>(ctx)) {
        return new P4::IR::Mul(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::DivExprContext *>(ctx)) {
        return new P4::IR::Div(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::ModExprContext *>(ctx)) {
        return new P4::IR::Mod(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::AddExprContext *>(ctx)) {
        return new P4::IR::Add(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::SubExprContext *>(ctx)) {
        return new P4::IR::Sub(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::AddSatExprContext *>(ctx)) {
        return new P4::IR::AddSat(si, visitExpression(e->expression(0)),
                                  visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::SubSatExprContext *>(ctx)) {
        return new P4::IR::SubSat(si, visitExpression(e->expression(0)),
                                  visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::ShlExprContext *>(ctx)) {
        return new P4::IR::Shl(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::ShrExprContext *>(ctx)) {
        return new P4::IR::Shr(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::ConcatExprContext *>(ctx)) {
        return new P4::IR::Concat(si, visitExpression(e->expression(0)),
                                  visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::LeqExprContext *>(ctx)) {
        return new P4::IR::Leq(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::GeqExprContext *>(ctx)) {
        return new P4::IR::Geq(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::LssExprContext *>(ctx)) {
        return new P4::IR::Lss(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::GrtExprContext *>(ctx)) {
        return new P4::IR::Grt(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::NeqExprContext *>(ctx)) {
        return new P4::IR::Neq(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::EqExprContext *>(ctx)) {
        return new P4::IR::Equ(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::BandExprContext *>(ctx)) {
        return new P4::IR::BAnd(si, visitExpression(e->expression(0)),
                                visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::BxorExprContext *>(ctx)) {
        return new P4::IR::BXor(si, visitExpression(e->expression(0)),
                                visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::BorExprContext *>(ctx)) {
        return new P4::IR::BOr(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::LandExprContext *>(ctx)) {
        return new P4::IR::LAnd(si, visitExpression(e->expression(0)),
                                visitExpression(e->expression(1)));
    }
    if (auto *e = dynamic_cast<Antlr4P4Parser::LorExprContext *>(ctx)) {
        return new P4::IR::LOr(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)));
    }

    // Ternary: expr ? expr : expr
    if (auto *e = dynamic_cast<Antlr4P4Parser::TernaryExprContext *>(ctx)) {
        return new P4::IR::Mux(si, visitExpression(e->expression(0)),
                               visitExpression(e->expression(1)),
                               visitExpression(e->expression(2)));
    }

    // Array index: expr[expr]
    if (auto *e = dynamic_cast<Antlr4P4Parser::ArrayIndexExprContext *>(ctx)) {
        return new P4::IR::ArrayIndex(si, visitExpression(e->expression(0)),
                                      visitExpression(e->expression(1)));
    }
    // Slice: expr[expr:expr]
    if (auto *e = dynamic_cast<Antlr4P4Parser::SliceExprContext *>(ctx)) {
        return new P4::IR::Slice(si, visitExpression(e->expression(0)),
                                 visitExpression(e->expression(1)),
                                 visitExpression(e->expression(2)));
    }
    // Plus slice: expr[expr+:expr]
    if (auto *e = dynamic_cast<Antlr4P4Parser::PlusSliceExprContext *>(ctx)) {
        return new P4::IR::PlusSlice(si, visitExpression(e->expression(0)),
                                     visitExpression(e->expression(1)),
                                     visitExpression(e->expression(2)));
    }

    // Member access: expr.name
    // Also handles type member access (typeName.name) since ANTLR4 has no
    // type/identifier distinction. We use the symbol table to decide whether
    // the base is a type or a variable.
    if (auto *e = dynamic_cast<Antlr4P4Parser::MemberExprContext *>(ctx)) {
        // Check if the base expression is a simple path that refers to a type.
        // In Bison, this would be parsed as typeName DOT name using TYPE_IDENTIFIER.
        auto *innerExpr = e->expression();
        if (auto *pathCtx = dynamic_cast<Antlr4P4Parser::PathExprContext *>(innerExpr)) {
            auto pathText = pathCtx->getText();
            auto kind = structure->lookupIdentifier(P4::cstring(pathText));
            if (kind == P4::Util::ProgramStructure::SymbolKind::Type ||
                kind == P4::Util::ProgramStructure::SymbolKind::TemplateType) {
                // This is a type member access: TypeName.member
                auto *typeName = visitTypeName(pathText, srcInfo(innerExpr));
                auto *name = visitName(e->name());
                return new P4::IR::Member(si, new P4::IR::TypeNameExpression(typeName), *name);
            }
        }
        auto *base = visitExpression(e->expression());
        auto *name = visitName(e->name());
        return new P4::IR::Member(si, base, *name);
    }

    // Error member: error.name
    if (auto *e = dynamic_cast<Antlr4P4Parser::ErrorMemberExprContext *>(ctx)) {
        auto *typeName = new P4::IR::Type_Name(si,
            new P4::IR::Path(P4::IR::ID(si, "error"_cs)));
        auto *name = visitName(e->name());
        return new P4::IR::Member(si, new P4::IR::TypeNameExpression(si, typeName), *name);
    }

    // Method call with type args: expr<typeArgs>(args)
    if (auto *e = dynamic_cast<Antlr4P4Parser::TypeCallExprContext *>(ctx)) {
        auto *base = visitExpression(e->expression());
        auto *typeArgs = visitRealTypeArgumentList(e->realTypeArgumentList());
        auto *args = visitArgumentList(e->argumentList());
        return new P4::IR::MethodCallExpression(si, base, typeArgs, args);
    }

    // Method call: expr(args)
    if (auto *e = dynamic_cast<Antlr4P4Parser::MethodCallExprContext *>(ctx)) {
        auto *base = visitExpression(e->expression());
        auto *args = visitArgumentList(e->argumentList());
        return new P4::IR::MethodCallExpression(si, base, args);
    }

    // Constructor call: namedType(args)
    // Since ANTLR4 has no type/identifier distinction, this alternative also
    // matches regular function/action calls like NoAction(). Use the symbol
    // table to distinguish: if the name is a type, create ConstructorCallExpression;
    // otherwise create MethodCallExpression (same as methodCallExpr).
    if (auto *e = dynamic_cast<Antlr4P4Parser::ConstructorCallExprContext *>(ctx)) {
        auto *namedCtx = e->namedType();
        // Check if this is actually a type name by querying the symbol table.
        std::string nameText;
        if (namedCtx->typeName()) {
            nameText = namedCtx->typeName()->getText();
        } else if (namedCtx->specializedType()) {
            nameText = namedCtx->specializedType()->typeName()->getText();
        }
        auto kind = structure->lookupIdentifier(P4::cstring(nameText));
        if (kind == P4::Util::ProgramStructure::SymbolKind::Type ||
            kind == P4::Util::ProgramStructure::SymbolKind::TemplateType) {
            // This is indeed a constructor call.
            auto *type = visitNamedType(namedCtx);
            auto *args = visitArgumentList(e->argumentList());
            return new P4::IR::ConstructorCallExpression(si, type, args);
        } else {
            // Not a type - this is a regular function/action call.
            // Create a PathExpression for the callee.
            auto *path = new P4::IR::Path(
                P4::IR::ID(srcInfo(namedCtx), P4::cstring(nameText)));
            auto *callee = new P4::IR::PathExpression(srcInfo(namedCtx), path);
            auto *args = visitArgumentList(e->argumentList());
            return new P4::IR::MethodCallExpression(si, callee, args);
        }
    }

    BUG("Unexpected expression alternative: %s", ctx->getText().c_str());
}

P4::IR::Expression *P4IRConstructor::visitNonBraceExpression(
    Antlr4P4Parser::NonBraceExpressionContext *ctx) {
    return visitExpression(ctx->expression());
}

//===----------------------------------------------------------------------===//
// Annotation-body fragment visitors. Each takes a fragment parse tree produced
// by one of the `annXxx` entry rules and returns the IR shape that
// `P4ParserDriver::parseXxx` (and in turn the `ParseAnnotations` pass) expects.
//===----------------------------------------------------------------------===//

P4::IR::Vector<P4::IR::Expression> *P4IRConstructor::visitAnnExpressionList(
    Antlr4P4Parser::AnnExpressionListContext *ctx) {
    return visitExpressionList(ctx->expressionList());
}

P4::IR::IndexedVector<P4::IR::NamedExpression> *P4IRConstructor::visitAnnKvList(
    Antlr4P4Parser::AnnKvListContext *ctx) {
    return visitKvList(ctx->kvList());
}

P4::IR::Vector<P4::IR::Expression> *P4IRConstructor::visitAnnIntegerList(
    Antlr4P4Parser::AnnIntegerListContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Expression>();
    for (auto *tn : ctx->INTEGER()) result->push_back(parseIntegerToken(tn->getSymbol()));
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Vector<P4::IR::Expression> *P4IRConstructor::visitAnnIntOrStrList(
    Antlr4P4Parser::AnnIntOrStrListContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Expression>();
    for (auto *ios : ctx->intOrStr()) result->push_back(visitIntOrStr(ios));
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Vector<P4::IR::Expression> *P4IRConstructor::visitAnnStringList(
    Antlr4P4Parser::AnnStringListContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Expression>();
    for (auto *tn : ctx->STRING_LITERAL()) {
        auto *tok = tn->getSymbol();
        result->push_back(new P4::IR::StringLiteral(srcInfo(tok), P4::cstring(tok->getText())));
    }
    if (!result->empty()) result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Expression *P4IRConstructor::visitAnnExpression(
    Antlr4P4Parser::AnnExpressionContext *ctx) {
    return visitExpression(ctx->expression());
}

P4::IR::Constant *P4IRConstructor::visitAnnInteger(Antlr4P4Parser::AnnIntegerContext *ctx) {
    return parseIntegerToken(ctx->INTEGER()->getSymbol());
}

P4::IR::Expression *P4IRConstructor::visitAnnIntOrStr(
    Antlr4P4Parser::AnnIntOrStrContext *ctx) {
    return visitIntOrStr(ctx->intOrStr());
}

P4::IR::StringLiteral *P4IRConstructor::visitAnnStringLiteral(
    Antlr4P4Parser::AnnStringLiteralContext *ctx) {
    auto *tok = ctx->STRING_LITERAL()->getSymbol();
    return new P4::IR::StringLiteral(srcInfo(tok), P4::cstring(tok->getText()));
}

P4::IR::Vector<P4::IR::Expression> *P4IRConstructor::visitAnnExpressionPair(
    Antlr4P4Parser::AnnExpressionPairContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Expression>();
    auto exprs = ctx->expression();
    result->push_back(visitExpression(exprs[0]));
    result->push_back(visitExpression(exprs[1]));
    result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Vector<P4::IR::Expression> *P4IRConstructor::visitAnnIntegerPair(
    Antlr4P4Parser::AnnIntegerPairContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Expression>();
    auto ints = ctx->INTEGER();
    result->push_back(parseIntegerToken(ints[0]->getSymbol()));
    result->push_back(parseIntegerToken(ints[1]->getSymbol()));
    result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Vector<P4::IR::Expression> *P4IRConstructor::visitAnnStringPair(
    Antlr4P4Parser::AnnStringPairContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Expression>();
    auto strs = ctx->STRING_LITERAL();
    for (auto *tn : strs) {
        auto *tok = tn->getSymbol();
        result->push_back(new P4::IR::StringLiteral(srcInfo(tok), P4::cstring(tok->getText())));
    }
    result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Vector<P4::IR::Expression> *P4IRConstructor::visitAnnExpressionTriple(
    Antlr4P4Parser::AnnExpressionTripleContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Expression>();
    auto exprs = ctx->expression();
    result->push_back(visitExpression(exprs[0]));
    result->push_back(visitExpression(exprs[1]));
    result->push_back(visitExpression(exprs[2]));
    result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Vector<P4::IR::Expression> *P4IRConstructor::visitAnnIntegerTriple(
    Antlr4P4Parser::AnnIntegerTripleContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Expression>();
    auto ints = ctx->INTEGER();
    result->push_back(parseIntegerToken(ints[0]->getSymbol()));
    result->push_back(parseIntegerToken(ints[1]->getSymbol()));
    result->push_back(parseIntegerToken(ints[2]->getSymbol()));
    result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Vector<P4::IR::Expression> *P4IRConstructor::visitAnnStringTriple(
    Antlr4P4Parser::AnnStringTripleContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Expression>();
    for (auto *tn : ctx->STRING_LITERAL()) {
        auto *tok = tn->getSymbol();
        result->push_back(new P4::IR::StringLiteral(srcInfo(tok), P4::cstring(tok->getText())));
    }
    result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Vector<P4::IR::Expression> *P4IRConstructor::visitAnnP4rtTranslation(
    Antlr4P4Parser::AnnP4rtTranslationContext *ctx) {
    auto *result = new P4::IR::Vector<P4::IR::Expression>();
    auto *strTok = ctx->STRING_LITERAL()->getSymbol();
    result->push_back(
        new P4::IR::StringLiteral(srcInfo(strTok), P4::cstring(strTok->getText())));
    result->push_back(visitP4rtControllerType(ctx->p4rtControllerType()));
    result->srcInfo = srcInfo(ctx);
    return result;
}

P4::IR::Expression *P4IRConstructor::visitIntOrStr(Antlr4P4Parser::IntOrStrContext *ctx) {
    if (ctx->INTEGER()) return parseIntegerToken(ctx->INTEGER()->getSymbol());
    auto *tok = ctx->STRING_LITERAL()->getSymbol();
    return new P4::IR::StringLiteral(srcInfo(tok), P4::cstring(tok->getText()));
}

// Encodes the p4rtControllerType argument as an IR::Expression. We reuse
// StringLiteral("") to represent the `string` keyword and IR::Constant(W)
// to represent `bit<W>`; bare INTEGER keeps the legacy pre-P4RT-2.0 form.
P4::IR::Expression *P4IRConstructor::visitP4rtControllerType(
    Antlr4P4Parser::P4rtControllerTypeContext *ctx) {
    auto si = srcInfo(ctx);
    if (ctx->STRING_KW()) return new P4::IR::StringLiteral(si, ""_cs);
    if (ctx->BIT()) return parseIntegerToken(ctx->INTEGER()->getSymbol());
    return parseIntegerToken(ctx->INTEGER()->getSymbol());
}

}  // namespace P4ANTLR
