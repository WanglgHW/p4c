// Generated from /Users/georgewang/Tofino/p4c/frontends/p4-antlr4/P4Parser.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link P4Parser}.
 */
public interface P4ParserListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link P4Parser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(P4Parser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(P4Parser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#declaration}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration(P4Parser.DeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#declaration}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration(P4Parser.DeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#nonTypeName}.
	 * @param ctx the parse tree
	 */
	void enterNonTypeName(P4Parser.NonTypeNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#nonTypeName}.
	 * @param ctx the parse tree
	 */
	void exitNonTypeName(P4Parser.NonTypeNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#name}.
	 * @param ctx the parse tree
	 */
	void enterName(P4Parser.NameContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#name}.
	 * @param ctx the parse tree
	 */
	void exitName(P4Parser.NameContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#nonTableKwName}.
	 * @param ctx the parse tree
	 */
	void enterNonTableKwName(P4Parser.NonTableKwNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#nonTableKwName}.
	 * @param ctx the parse tree
	 */
	void exitNonTableKwName(P4Parser.NonTableKwNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#annotationName}.
	 * @param ctx the parse tree
	 */
	void enterAnnotationName(P4Parser.AnnotationNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#annotationName}.
	 * @param ctx the parse tree
	 */
	void exitAnnotationName(P4Parser.AnnotationNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#optAnnotations}.
	 * @param ctx the parse tree
	 */
	void enterOptAnnotations(P4Parser.OptAnnotationsContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#optAnnotations}.
	 * @param ctx the parse tree
	 */
	void exitOptAnnotations(P4Parser.OptAnnotationsContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#annotations}.
	 * @param ctx the parse tree
	 */
	void enterAnnotations(P4Parser.AnnotationsContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#annotations}.
	 * @param ctx the parse tree
	 */
	void exitAnnotations(P4Parser.AnnotationsContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#annotation}.
	 * @param ctx the parse tree
	 */
	void enterAnnotation(P4Parser.AnnotationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#annotation}.
	 * @param ctx the parse tree
	 */
	void exitAnnotation(P4Parser.AnnotationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#annotationBody}.
	 * @param ctx the parse tree
	 */
	void enterAnnotationBody(P4Parser.AnnotationBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#annotationBody}.
	 * @param ctx the parse tree
	 */
	void exitAnnotationBody(P4Parser.AnnotationBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#annotationToken}.
	 * @param ctx the parse tree
	 */
	void enterAnnotationToken(P4Parser.AnnotationTokenContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#annotationToken}.
	 * @param ctx the parse tree
	 */
	void exitAnnotationToken(P4Parser.AnnotationTokenContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#optTrailingComma}.
	 * @param ctx the parse tree
	 */
	void enterOptTrailingComma(P4Parser.OptTrailingCommaContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#optTrailingComma}.
	 * @param ctx the parse tree
	 */
	void exitOptTrailingComma(P4Parser.OptTrailingCommaContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#parameterList}.
	 * @param ctx the parse tree
	 */
	void enterParameterList(P4Parser.ParameterListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#parameterList}.
	 * @param ctx the parse tree
	 */
	void exitParameterList(P4Parser.ParameterListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#nonEmptyParameterList}.
	 * @param ctx the parse tree
	 */
	void enterNonEmptyParameterList(P4Parser.NonEmptyParameterListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#nonEmptyParameterList}.
	 * @param ctx the parse tree
	 */
	void exitNonEmptyParameterList(P4Parser.NonEmptyParameterListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#parameter}.
	 * @param ctx the parse tree
	 */
	void enterParameter(P4Parser.ParameterContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#parameter}.
	 * @param ctx the parse tree
	 */
	void exitParameter(P4Parser.ParameterContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#direction}.
	 * @param ctx the parse tree
	 */
	void enterDirection(P4Parser.DirectionContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#direction}.
	 * @param ctx the parse tree
	 */
	void exitDirection(P4Parser.DirectionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code specializedTypeRef}
	 * labeled alternative in {@link P4Parser#typeRef}.
	 * @param ctx the parse tree
	 */
	void enterSpecializedTypeRef(P4Parser.SpecializedTypeRefContext ctx);
	/**
	 * Exit a parse tree produced by the {@code specializedTypeRef}
	 * labeled alternative in {@link P4Parser#typeRef}.
	 * @param ctx the parse tree
	 */
	void exitSpecializedTypeRef(P4Parser.SpecializedTypeRefContext ctx);
	/**
	 * Enter a parse tree produced by the {@code headerStackTypeRef}
	 * labeled alternative in {@link P4Parser#typeRef}.
	 * @param ctx the parse tree
	 */
	void enterHeaderStackTypeRef(P4Parser.HeaderStackTypeRefContext ctx);
	/**
	 * Exit a parse tree produced by the {@code headerStackTypeRef}
	 * labeled alternative in {@link P4Parser#typeRef}.
	 * @param ctx the parse tree
	 */
	void exitHeaderStackTypeRef(P4Parser.HeaderStackTypeRefContext ctx);
	/**
	 * Enter a parse tree produced by the {@code typeNameRef}
	 * labeled alternative in {@link P4Parser#typeRef}.
	 * @param ctx the parse tree
	 */
	void enterTypeNameRef(P4Parser.TypeNameRefContext ctx);
	/**
	 * Exit a parse tree produced by the {@code typeNameRef}
	 * labeled alternative in {@link P4Parser#typeRef}.
	 * @param ctx the parse tree
	 */
	void exitTypeNameRef(P4Parser.TypeNameRefContext ctx);
	/**
	 * Enter a parse tree produced by the {@code tupleTypeRef}
	 * labeled alternative in {@link P4Parser#typeRef}.
	 * @param ctx the parse tree
	 */
	void enterTupleTypeRef(P4Parser.TupleTypeRefContext ctx);
	/**
	 * Exit a parse tree produced by the {@code tupleTypeRef}
	 * labeled alternative in {@link P4Parser#typeRef}.
	 * @param ctx the parse tree
	 */
	void exitTupleTypeRef(P4Parser.TupleTypeRefContext ctx);
	/**
	 * Enter a parse tree produced by the {@code baseTypeRef}
	 * labeled alternative in {@link P4Parser#typeRef}.
	 * @param ctx the parse tree
	 */
	void enterBaseTypeRef(P4Parser.BaseTypeRefContext ctx);
	/**
	 * Exit a parse tree produced by the {@code baseTypeRef}
	 * labeled alternative in {@link P4Parser#typeRef}.
	 * @param ctx the parse tree
	 */
	void exitBaseTypeRef(P4Parser.BaseTypeRefContext ctx);
	/**
	 * Enter a parse tree produced by the {@code p4listTypeRef}
	 * labeled alternative in {@link P4Parser#typeRef}.
	 * @param ctx the parse tree
	 */
	void enterP4listTypeRef(P4Parser.P4listTypeRefContext ctx);
	/**
	 * Exit a parse tree produced by the {@code p4listTypeRef}
	 * labeled alternative in {@link P4Parser#typeRef}.
	 * @param ctx the parse tree
	 */
	void exitP4listTypeRef(P4Parser.P4listTypeRefContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#namedType}.
	 * @param ctx the parse tree
	 */
	void enterNamedType(P4Parser.NamedTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#namedType}.
	 * @param ctx the parse tree
	 */
	void exitNamedType(P4Parser.NamedTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#prefixedType}.
	 * @param ctx the parse tree
	 */
	void enterPrefixedType(P4Parser.PrefixedTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#prefixedType}.
	 * @param ctx the parse tree
	 */
	void exitPrefixedType(P4Parser.PrefixedTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#typeName}.
	 * @param ctx the parse tree
	 */
	void enterTypeName(P4Parser.TypeNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#typeName}.
	 * @param ctx the parse tree
	 */
	void exitTypeName(P4Parser.TypeNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#p4listType}.
	 * @param ctx the parse tree
	 */
	void enterP4listType(P4Parser.P4listTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#p4listType}.
	 * @param ctx the parse tree
	 */
	void exitP4listType(P4Parser.P4listTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#tupleType}.
	 * @param ctx the parse tree
	 */
	void enterTupleType(P4Parser.TupleTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#tupleType}.
	 * @param ctx the parse tree
	 */
	void exitTupleType(P4Parser.TupleTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#specializedType}.
	 * @param ctx the parse tree
	 */
	void enterSpecializedType(P4Parser.SpecializedTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#specializedType}.
	 * @param ctx the parse tree
	 */
	void exitSpecializedType(P4Parser.SpecializedTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#baseType}.
	 * @param ctx the parse tree
	 */
	void enterBaseType(P4Parser.BaseTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#baseType}.
	 * @param ctx the parse tree
	 */
	void exitBaseType(P4Parser.BaseTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#typeOrVoid}.
	 * @param ctx the parse tree
	 */
	void enterTypeOrVoid(P4Parser.TypeOrVoidContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#typeOrVoid}.
	 * @param ctx the parse tree
	 */
	void exitTypeOrVoid(P4Parser.TypeOrVoidContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#optTypeParameters}.
	 * @param ctx the parse tree
	 */
	void enterOptTypeParameters(P4Parser.OptTypeParametersContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#optTypeParameters}.
	 * @param ctx the parse tree
	 */
	void exitOptTypeParameters(P4Parser.OptTypeParametersContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#typeParameters}.
	 * @param ctx the parse tree
	 */
	void enterTypeParameters(P4Parser.TypeParametersContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#typeParameters}.
	 * @param ctx the parse tree
	 */
	void exitTypeParameters(P4Parser.TypeParametersContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#typeParameterList}.
	 * @param ctx the parse tree
	 */
	void enterTypeParameterList(P4Parser.TypeParameterListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#typeParameterList}.
	 * @param ctx the parse tree
	 */
	void exitTypeParameterList(P4Parser.TypeParameterListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#typeArg}.
	 * @param ctx the parse tree
	 */
	void enterTypeArg(P4Parser.TypeArgContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#typeArg}.
	 * @param ctx the parse tree
	 */
	void exitTypeArg(P4Parser.TypeArgContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#typeArgumentList}.
	 * @param ctx the parse tree
	 */
	void enterTypeArgumentList(P4Parser.TypeArgumentListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#typeArgumentList}.
	 * @param ctx the parse tree
	 */
	void exitTypeArgumentList(P4Parser.TypeArgumentListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#realTypeArg}.
	 * @param ctx the parse tree
	 */
	void enterRealTypeArg(P4Parser.RealTypeArgContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#realTypeArg}.
	 * @param ctx the parse tree
	 */
	void exitRealTypeArg(P4Parser.RealTypeArgContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#realTypeArgumentList}.
	 * @param ctx the parse tree
	 */
	void enterRealTypeArgumentList(P4Parser.RealTypeArgumentListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#realTypeArgumentList}.
	 * @param ctx the parse tree
	 */
	void exitRealTypeArgumentList(P4Parser.RealTypeArgumentListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#typeDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterTypeDeclaration(P4Parser.TypeDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#typeDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitTypeDeclaration(P4Parser.TypeDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#derivedTypeDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterDerivedTypeDeclaration(P4Parser.DerivedTypeDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#derivedTypeDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitDerivedTypeDeclaration(P4Parser.DerivedTypeDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#headerTypeDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterHeaderTypeDeclaration(P4Parser.HeaderTypeDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#headerTypeDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitHeaderTypeDeclaration(P4Parser.HeaderTypeDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#structTypeDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterStructTypeDeclaration(P4Parser.StructTypeDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#structTypeDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitStructTypeDeclaration(P4Parser.StructTypeDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#headerUnionDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterHeaderUnionDeclaration(P4Parser.HeaderUnionDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#headerUnionDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitHeaderUnionDeclaration(P4Parser.HeaderUnionDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#structFieldList}.
	 * @param ctx the parse tree
	 */
	void enterStructFieldList(P4Parser.StructFieldListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#structFieldList}.
	 * @param ctx the parse tree
	 */
	void exitStructFieldList(P4Parser.StructFieldListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#structField}.
	 * @param ctx the parse tree
	 */
	void enterStructField(P4Parser.StructFieldContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#structField}.
	 * @param ctx the parse tree
	 */
	void exitStructField(P4Parser.StructFieldContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#enumDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterEnumDeclaration(P4Parser.EnumDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#enumDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitEnumDeclaration(P4Parser.EnumDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#specifiedIdentifierList}.
	 * @param ctx the parse tree
	 */
	void enterSpecifiedIdentifierList(P4Parser.SpecifiedIdentifierListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#specifiedIdentifierList}.
	 * @param ctx the parse tree
	 */
	void exitSpecifiedIdentifierList(P4Parser.SpecifiedIdentifierListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#specifiedIdentifier}.
	 * @param ctx the parse tree
	 */
	void enterSpecifiedIdentifier(P4Parser.SpecifiedIdentifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#specifiedIdentifier}.
	 * @param ctx the parse tree
	 */
	void exitSpecifiedIdentifier(P4Parser.SpecifiedIdentifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#errorDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterErrorDeclaration(P4Parser.ErrorDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#errorDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitErrorDeclaration(P4Parser.ErrorDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#matchKindDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterMatchKindDeclaration(P4Parser.MatchKindDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#matchKindDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitMatchKindDeclaration(P4Parser.MatchKindDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#identifierList}.
	 * @param ctx the parse tree
	 */
	void enterIdentifierList(P4Parser.IdentifierListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#identifierList}.
	 * @param ctx the parse tree
	 */
	void exitIdentifierList(P4Parser.IdentifierListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#typedefDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterTypedefDeclaration(P4Parser.TypedefDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#typedefDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitTypedefDeclaration(P4Parser.TypedefDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#packageTypeDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterPackageTypeDeclaration(P4Parser.PackageTypeDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#packageTypeDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitPackageTypeDeclaration(P4Parser.PackageTypeDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#parserDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterParserDeclaration(P4Parser.ParserDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#parserDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitParserDeclaration(P4Parser.ParserDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#parserTypeDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterParserTypeDeclaration(P4Parser.ParserTypeDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#parserTypeDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitParserTypeDeclaration(P4Parser.ParserTypeDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#parserLocalElements}.
	 * @param ctx the parse tree
	 */
	void enterParserLocalElements(P4Parser.ParserLocalElementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#parserLocalElements}.
	 * @param ctx the parse tree
	 */
	void exitParserLocalElements(P4Parser.ParserLocalElementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#parserLocalElement}.
	 * @param ctx the parse tree
	 */
	void enterParserLocalElement(P4Parser.ParserLocalElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#parserLocalElement}.
	 * @param ctx the parse tree
	 */
	void exitParserLocalElement(P4Parser.ParserLocalElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#parserStates}.
	 * @param ctx the parse tree
	 */
	void enterParserStates(P4Parser.ParserStatesContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#parserStates}.
	 * @param ctx the parse tree
	 */
	void exitParserStates(P4Parser.ParserStatesContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#parserState}.
	 * @param ctx the parse tree
	 */
	void enterParserState(P4Parser.ParserStateContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#parserState}.
	 * @param ctx the parse tree
	 */
	void exitParserState(P4Parser.ParserStateContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#parserStatements}.
	 * @param ctx the parse tree
	 */
	void enterParserStatements(P4Parser.ParserStatementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#parserStatements}.
	 * @param ctx the parse tree
	 */
	void exitParserStatements(P4Parser.ParserStatementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#parserStatement}.
	 * @param ctx the parse tree
	 */
	void enterParserStatement(P4Parser.ParserStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#parserStatement}.
	 * @param ctx the parse tree
	 */
	void exitParserStatement(P4Parser.ParserStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#parserBlockStatement}.
	 * @param ctx the parse tree
	 */
	void enterParserBlockStatement(P4Parser.ParserBlockStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#parserBlockStatement}.
	 * @param ctx the parse tree
	 */
	void exitParserBlockStatement(P4Parser.ParserBlockStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#transitionStatement}.
	 * @param ctx the parse tree
	 */
	void enterTransitionStatement(P4Parser.TransitionStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#transitionStatement}.
	 * @param ctx the parse tree
	 */
	void exitTransitionStatement(P4Parser.TransitionStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#stateExpression}.
	 * @param ctx the parse tree
	 */
	void enterStateExpression(P4Parser.StateExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#stateExpression}.
	 * @param ctx the parse tree
	 */
	void exitStateExpression(P4Parser.StateExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#selectExpression}.
	 * @param ctx the parse tree
	 */
	void enterSelectExpression(P4Parser.SelectExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#selectExpression}.
	 * @param ctx the parse tree
	 */
	void exitSelectExpression(P4Parser.SelectExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#selectCaseList}.
	 * @param ctx the parse tree
	 */
	void enterSelectCaseList(P4Parser.SelectCaseListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#selectCaseList}.
	 * @param ctx the parse tree
	 */
	void exitSelectCaseList(P4Parser.SelectCaseListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#selectCase}.
	 * @param ctx the parse tree
	 */
	void enterSelectCase(P4Parser.SelectCaseContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#selectCase}.
	 * @param ctx the parse tree
	 */
	void exitSelectCase(P4Parser.SelectCaseContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#keysetExpression}.
	 * @param ctx the parse tree
	 */
	void enterKeysetExpression(P4Parser.KeysetExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#keysetExpression}.
	 * @param ctx the parse tree
	 */
	void exitKeysetExpression(P4Parser.KeysetExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#tupleKeysetExpression}.
	 * @param ctx the parse tree
	 */
	void enterTupleKeysetExpression(P4Parser.TupleKeysetExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#tupleKeysetExpression}.
	 * @param ctx the parse tree
	 */
	void exitTupleKeysetExpression(P4Parser.TupleKeysetExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#simpleExpressionList}.
	 * @param ctx the parse tree
	 */
	void enterSimpleExpressionList(P4Parser.SimpleExpressionListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#simpleExpressionList}.
	 * @param ctx the parse tree
	 */
	void exitSimpleExpressionList(P4Parser.SimpleExpressionListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#reducedSimpleKeysetExpression}.
	 * @param ctx the parse tree
	 */
	void enterReducedSimpleKeysetExpression(P4Parser.ReducedSimpleKeysetExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#reducedSimpleKeysetExpression}.
	 * @param ctx the parse tree
	 */
	void exitReducedSimpleKeysetExpression(P4Parser.ReducedSimpleKeysetExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#simpleKeysetExpression}.
	 * @param ctx the parse tree
	 */
	void enterSimpleKeysetExpression(P4Parser.SimpleKeysetExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#simpleKeysetExpression}.
	 * @param ctx the parse tree
	 */
	void exitSimpleKeysetExpression(P4Parser.SimpleKeysetExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#valueSetDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterValueSetDeclaration(P4Parser.ValueSetDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#valueSetDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitValueSetDeclaration(P4Parser.ValueSetDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#controlDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterControlDeclaration(P4Parser.ControlDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#controlDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitControlDeclaration(P4Parser.ControlDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#controlTypeDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterControlTypeDeclaration(P4Parser.ControlTypeDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#controlTypeDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitControlTypeDeclaration(P4Parser.ControlTypeDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#controlLocalDeclarations}.
	 * @param ctx the parse tree
	 */
	void enterControlLocalDeclarations(P4Parser.ControlLocalDeclarationsContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#controlLocalDeclarations}.
	 * @param ctx the parse tree
	 */
	void exitControlLocalDeclarations(P4Parser.ControlLocalDeclarationsContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#controlLocalDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterControlLocalDeclaration(P4Parser.ControlLocalDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#controlLocalDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitControlLocalDeclaration(P4Parser.ControlLocalDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#controlBody}.
	 * @param ctx the parse tree
	 */
	void enterControlBody(P4Parser.ControlBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#controlBody}.
	 * @param ctx the parse tree
	 */
	void exitControlBody(P4Parser.ControlBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#externDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterExternDeclaration(P4Parser.ExternDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#externDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitExternDeclaration(P4Parser.ExternDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#methodPrototypes}.
	 * @param ctx the parse tree
	 */
	void enterMethodPrototypes(P4Parser.MethodPrototypesContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#methodPrototypes}.
	 * @param ctx the parse tree
	 */
	void exitMethodPrototypes(P4Parser.MethodPrototypesContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#functionPrototype}.
	 * @param ctx the parse tree
	 */
	void enterFunctionPrototype(P4Parser.FunctionPrototypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#functionPrototype}.
	 * @param ctx the parse tree
	 */
	void exitFunctionPrototype(P4Parser.FunctionPrototypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#methodPrototype}.
	 * @param ctx the parse tree
	 */
	void enterMethodPrototype(P4Parser.MethodPrototypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#methodPrototype}.
	 * @param ctx the parse tree
	 */
	void exitMethodPrototype(P4Parser.MethodPrototypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#instantiation}.
	 * @param ctx the parse tree
	 */
	void enterInstantiation(P4Parser.InstantiationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#instantiation}.
	 * @param ctx the parse tree
	 */
	void exitInstantiation(P4Parser.InstantiationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#optObjInitializer}.
	 * @param ctx the parse tree
	 */
	void enterOptObjInitializer(P4Parser.OptObjInitializerContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#optObjInitializer}.
	 * @param ctx the parse tree
	 */
	void exitOptObjInitializer(P4Parser.OptObjInitializerContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#objDeclarations}.
	 * @param ctx the parse tree
	 */
	void enterObjDeclarations(P4Parser.ObjDeclarationsContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#objDeclarations}.
	 * @param ctx the parse tree
	 */
	void exitObjDeclarations(P4Parser.ObjDeclarationsContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#objDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterObjDeclaration(P4Parser.ObjDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#objDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitObjDeclaration(P4Parser.ObjDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#optConstructorParameters}.
	 * @param ctx the parse tree
	 */
	void enterOptConstructorParameters(P4Parser.OptConstructorParametersContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#optConstructorParameters}.
	 * @param ctx the parse tree
	 */
	void exitOptConstructorParameters(P4Parser.OptConstructorParametersContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#tableDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterTableDeclaration(P4Parser.TableDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#tableDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitTableDeclaration(P4Parser.TableDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#tablePropertyList}.
	 * @param ctx the parse tree
	 */
	void enterTablePropertyList(P4Parser.TablePropertyListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#tablePropertyList}.
	 * @param ctx the parse tree
	 */
	void exitTablePropertyList(P4Parser.TablePropertyListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#tableProperty}.
	 * @param ctx the parse tree
	 */
	void enterTableProperty(P4Parser.TablePropertyContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#tableProperty}.
	 * @param ctx the parse tree
	 */
	void exitTableProperty(P4Parser.TablePropertyContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#optCONST}.
	 * @param ctx the parse tree
	 */
	void enterOptCONST(P4Parser.OptCONSTContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#optCONST}.
	 * @param ctx the parse tree
	 */
	void exitOptCONST(P4Parser.OptCONSTContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#keyElementList}.
	 * @param ctx the parse tree
	 */
	void enterKeyElementList(P4Parser.KeyElementListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#keyElementList}.
	 * @param ctx the parse tree
	 */
	void exitKeyElementList(P4Parser.KeyElementListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#keyElement}.
	 * @param ctx the parse tree
	 */
	void enterKeyElement(P4Parser.KeyElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#keyElement}.
	 * @param ctx the parse tree
	 */
	void exitKeyElement(P4Parser.KeyElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#actionList}.
	 * @param ctx the parse tree
	 */
	void enterActionList(P4Parser.ActionListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#actionList}.
	 * @param ctx the parse tree
	 */
	void exitActionList(P4Parser.ActionListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#actionRef}.
	 * @param ctx the parse tree
	 */
	void enterActionRef(P4Parser.ActionRefContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#actionRef}.
	 * @param ctx the parse tree
	 */
	void exitActionRef(P4Parser.ActionRefContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#prefixedNonTypeName}.
	 * @param ctx the parse tree
	 */
	void enterPrefixedNonTypeName(P4Parser.PrefixedNonTypeNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#prefixedNonTypeName}.
	 * @param ctx the parse tree
	 */
	void exitPrefixedNonTypeName(P4Parser.PrefixedNonTypeNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#entry}.
	 * @param ctx the parse tree
	 */
	void enterEntry(P4Parser.EntryContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#entry}.
	 * @param ctx the parse tree
	 */
	void exitEntry(P4Parser.EntryContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#entryPriority}.
	 * @param ctx the parse tree
	 */
	void enterEntryPriority(P4Parser.EntryPriorityContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#entryPriority}.
	 * @param ctx the parse tree
	 */
	void exitEntryPriority(P4Parser.EntryPriorityContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#entriesList}.
	 * @param ctx the parse tree
	 */
	void enterEntriesList(P4Parser.EntriesListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#entriesList}.
	 * @param ctx the parse tree
	 */
	void exitEntriesList(P4Parser.EntriesListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#actionDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterActionDeclaration(P4Parser.ActionDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#actionDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitActionDeclaration(P4Parser.ActionDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterVariableDeclaration(P4Parser.VariableDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitVariableDeclaration(P4Parser.VariableDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#variableDeclarationWithoutSemicolon}.
	 * @param ctx the parse tree
	 */
	void enterVariableDeclarationWithoutSemicolon(P4Parser.VariableDeclarationWithoutSemicolonContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#variableDeclarationWithoutSemicolon}.
	 * @param ctx the parse tree
	 */
	void exitVariableDeclarationWithoutSemicolon(P4Parser.VariableDeclarationWithoutSemicolonContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#constantDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterConstantDeclaration(P4Parser.ConstantDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#constantDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitConstantDeclaration(P4Parser.ConstantDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#declarator}.
	 * @param ctx the parse tree
	 */
	void enterDeclarator(P4Parser.DeclaratorContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#declarator}.
	 * @param ctx the parse tree
	 */
	void exitDeclarator(P4Parser.DeclaratorContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#optInitializer}.
	 * @param ctx the parse tree
	 */
	void enterOptInitializer(P4Parser.OptInitializerContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#optInitializer}.
	 * @param ctx the parse tree
	 */
	void exitOptInitializer(P4Parser.OptInitializerContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#initializer}.
	 * @param ctx the parse tree
	 */
	void enterInitializer(P4Parser.InitializerContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#initializer}.
	 * @param ctx the parse tree
	 */
	void exitInitializer(P4Parser.InitializerContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#functionDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterFunctionDeclaration(P4Parser.FunctionDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#functionDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitFunctionDeclaration(P4Parser.FunctionDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#argumentList}.
	 * @param ctx the parse tree
	 */
	void enterArgumentList(P4Parser.ArgumentListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#argumentList}.
	 * @param ctx the parse tree
	 */
	void exitArgumentList(P4Parser.ArgumentListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#nonEmptyArgList}.
	 * @param ctx the parse tree
	 */
	void enterNonEmptyArgList(P4Parser.NonEmptyArgListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#nonEmptyArgList}.
	 * @param ctx the parse tree
	 */
	void exitNonEmptyArgList(P4Parser.NonEmptyArgListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#argument}.
	 * @param ctx the parse tree
	 */
	void enterArgument(P4Parser.ArgumentContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#argument}.
	 * @param ctx the parse tree
	 */
	void exitArgument(P4Parser.ArgumentContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#expressionList}.
	 * @param ctx the parse tree
	 */
	void enterExpressionList(P4Parser.ExpressionListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#expressionList}.
	 * @param ctx the parse tree
	 */
	void exitExpressionList(P4Parser.ExpressionListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#kvList}.
	 * @param ctx the parse tree
	 */
	void enterKvList(P4Parser.KvListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#kvList}.
	 * @param ctx the parse tree
	 */
	void exitKvList(P4Parser.KvListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#kvPair}.
	 * @param ctx the parse tree
	 */
	void enterKvPair(P4Parser.KvPairContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#kvPair}.
	 * @param ctx the parse tree
	 */
	void exitKvPair(P4Parser.KvPairContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(P4Parser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(P4Parser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code methodCallStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterMethodCallStmt(P4Parser.MethodCallStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code methodCallStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitMethodCallStmt(P4Parser.MethodCallStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code typeArgsMethodCallStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterTypeArgsMethodCallStmt(P4Parser.TypeArgsMethodCallStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code typeArgsMethodCallStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitTypeArgsMethodCallStmt(P4Parser.TypeArgsMethodCallStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code assignmentStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentStmt(P4Parser.AssignmentStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code assignmentStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentStmt(P4Parser.AssignmentStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code mulAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterMulAssignStmt(P4Parser.MulAssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code mulAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitMulAssignStmt(P4Parser.MulAssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code divAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterDivAssignStmt(P4Parser.DivAssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code divAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitDivAssignStmt(P4Parser.DivAssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code modAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterModAssignStmt(P4Parser.ModAssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code modAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitModAssignStmt(P4Parser.ModAssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code addAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterAddAssignStmt(P4Parser.AddAssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code addAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitAddAssignStmt(P4Parser.AddAssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code subAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterSubAssignStmt(P4Parser.SubAssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code subAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitSubAssignStmt(P4Parser.SubAssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code addSatAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterAddSatAssignStmt(P4Parser.AddSatAssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code addSatAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitAddSatAssignStmt(P4Parser.AddSatAssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code subSatAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterSubSatAssignStmt(P4Parser.SubSatAssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code subSatAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitSubSatAssignStmt(P4Parser.SubSatAssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code shlAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterShlAssignStmt(P4Parser.ShlAssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code shlAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitShlAssignStmt(P4Parser.ShlAssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code shrAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterShrAssignStmt(P4Parser.ShrAssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code shrAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitShrAssignStmt(P4Parser.ShrAssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code bandAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterBandAssignStmt(P4Parser.BandAssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code bandAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitBandAssignStmt(P4Parser.BandAssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code borAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterBorAssignStmt(P4Parser.BorAssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code borAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitBorAssignStmt(P4Parser.BorAssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code bxorAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterBxorAssignStmt(P4Parser.BxorAssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code bxorAssignStmt}
	 * labeled alternative in {@link P4Parser#assignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitBxorAssignStmt(P4Parser.BxorAssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#emptyStatement}.
	 * @param ctx the parse tree
	 */
	void enterEmptyStatement(P4Parser.EmptyStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#emptyStatement}.
	 * @param ctx the parse tree
	 */
	void exitEmptyStatement(P4Parser.EmptyStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#exitStatement}.
	 * @param ctx the parse tree
	 */
	void enterExitStatement(P4Parser.ExitStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#exitStatement}.
	 * @param ctx the parse tree
	 */
	void exitExitStatement(P4Parser.ExitStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#returnStatement}.
	 * @param ctx the parse tree
	 */
	void enterReturnStatement(P4Parser.ReturnStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#returnStatement}.
	 * @param ctx the parse tree
	 */
	void exitReturnStatement(P4Parser.ReturnStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#conditionalStatement}.
	 * @param ctx the parse tree
	 */
	void enterConditionalStatement(P4Parser.ConditionalStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#conditionalStatement}.
	 * @param ctx the parse tree
	 */
	void exitConditionalStatement(P4Parser.ConditionalStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#breakStatement}.
	 * @param ctx the parse tree
	 */
	void enterBreakStatement(P4Parser.BreakStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#breakStatement}.
	 * @param ctx the parse tree
	 */
	void exitBreakStatement(P4Parser.BreakStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#continueStatement}.
	 * @param ctx the parse tree
	 */
	void enterContinueStatement(P4Parser.ContinueStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#continueStatement}.
	 * @param ctx the parse tree
	 */
	void exitContinueStatement(P4Parser.ContinueStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#directApplication}.
	 * @param ctx the parse tree
	 */
	void enterDirectApplication(P4Parser.DirectApplicationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#directApplication}.
	 * @param ctx the parse tree
	 */
	void exitDirectApplication(P4Parser.DirectApplicationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#blockStatement}.
	 * @param ctx the parse tree
	 */
	void enterBlockStatement(P4Parser.BlockStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#blockStatement}.
	 * @param ctx the parse tree
	 */
	void exitBlockStatement(P4Parser.BlockStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#statOrDeclList}.
	 * @param ctx the parse tree
	 */
	void enterStatOrDeclList(P4Parser.StatOrDeclListContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#statOrDeclList}.
	 * @param ctx the parse tree
	 */
	void exitStatOrDeclList(P4Parser.StatOrDeclListContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#statementOrDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterStatementOrDeclaration(P4Parser.StatementOrDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#statementOrDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitStatementOrDeclaration(P4Parser.StatementOrDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#switchStatement}.
	 * @param ctx the parse tree
	 */
	void enterSwitchStatement(P4Parser.SwitchStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#switchStatement}.
	 * @param ctx the parse tree
	 */
	void exitSwitchStatement(P4Parser.SwitchStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#switchCases}.
	 * @param ctx the parse tree
	 */
	void enterSwitchCases(P4Parser.SwitchCasesContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#switchCases}.
	 * @param ctx the parse tree
	 */
	void exitSwitchCases(P4Parser.SwitchCasesContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#switchCase}.
	 * @param ctx the parse tree
	 */
	void enterSwitchCase(P4Parser.SwitchCaseContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#switchCase}.
	 * @param ctx the parse tree
	 */
	void exitSwitchCase(P4Parser.SwitchCaseContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#switchLabel}.
	 * @param ctx the parse tree
	 */
	void enterSwitchLabel(P4Parser.SwitchLabelContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#switchLabel}.
	 * @param ctx the parse tree
	 */
	void exitSwitchLabel(P4Parser.SwitchLabelContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#forStatement}.
	 * @param ctx the parse tree
	 */
	void enterForStatement(P4Parser.ForStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#forStatement}.
	 * @param ctx the parse tree
	 */
	void exitForStatement(P4Parser.ForStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#forInitStatements}.
	 * @param ctx the parse tree
	 */
	void enterForInitStatements(P4Parser.ForInitStatementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#forInitStatements}.
	 * @param ctx the parse tree
	 */
	void exitForInitStatements(P4Parser.ForInitStatementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#declOrAssignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void enterDeclOrAssignmentOrMethodCallStatement(P4Parser.DeclOrAssignmentOrMethodCallStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#declOrAssignmentOrMethodCallStatement}.
	 * @param ctx the parse tree
	 */
	void exitDeclOrAssignmentOrMethodCallStatement(P4Parser.DeclOrAssignmentOrMethodCallStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#assignmentOrMethodCallStatementWithoutSemicolon}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentOrMethodCallStatementWithoutSemicolon(P4Parser.AssignmentOrMethodCallStatementWithoutSemicolonContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#assignmentOrMethodCallStatementWithoutSemicolon}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentOrMethodCallStatementWithoutSemicolon(P4Parser.AssignmentOrMethodCallStatementWithoutSemicolonContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#forUpdateStatements}.
	 * @param ctx the parse tree
	 */
	void enterForUpdateStatements(P4Parser.ForUpdateStatementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#forUpdateStatements}.
	 * @param ctx the parse tree
	 */
	void exitForUpdateStatements(P4Parser.ForUpdateStatementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#forCollectionExpr}.
	 * @param ctx the parse tree
	 */
	void enterForCollectionExpr(P4Parser.ForCollectionExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#forCollectionExpr}.
	 * @param ctx the parse tree
	 */
	void exitForCollectionExpr(P4Parser.ForCollectionExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code memberLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void enterMemberLvalue(P4Parser.MemberLvalueContext ctx);
	/**
	 * Exit a parse tree produced by the {@code memberLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void exitMemberLvalue(P4Parser.MemberLvalueContext ctx);
	/**
	 * Enter a parse tree produced by the {@code indexLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void enterIndexLvalue(P4Parser.IndexLvalueContext ctx);
	/**
	 * Exit a parse tree produced by the {@code indexLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void exitIndexLvalue(P4Parser.IndexLvalueContext ctx);
	/**
	 * Enter a parse tree produced by the {@code parenLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void enterParenLvalue(P4Parser.ParenLvalueContext ctx);
	/**
	 * Exit a parse tree produced by the {@code parenLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void exitParenLvalue(P4Parser.ParenLvalueContext ctx);
	/**
	 * Enter a parse tree produced by the {@code plusSliceLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void enterPlusSliceLvalue(P4Parser.PlusSliceLvalueContext ctx);
	/**
	 * Exit a parse tree produced by the {@code plusSliceLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void exitPlusSliceLvalue(P4Parser.PlusSliceLvalueContext ctx);
	/**
	 * Enter a parse tree produced by the {@code pathLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void enterPathLvalue(P4Parser.PathLvalueContext ctx);
	/**
	 * Exit a parse tree produced by the {@code pathLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void exitPathLvalue(P4Parser.PathLvalueContext ctx);
	/**
	 * Enter a parse tree produced by the {@code sliceLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void enterSliceLvalue(P4Parser.SliceLvalueContext ctx);
	/**
	 * Exit a parse tree produced by the {@code sliceLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void exitSliceLvalue(P4Parser.SliceLvalueContext ctx);
	/**
	 * Enter a parse tree produced by the {@code thisLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void enterThisLvalue(P4Parser.ThisLvalueContext ctx);
	/**
	 * Exit a parse tree produced by the {@code thisLvalue}
	 * labeled alternative in {@link P4Parser#lvalue}.
	 * @param ctx the parse tree
	 */
	void exitThisLvalue(P4Parser.ThisLvalueContext ctx);
	/**
	 * Enter a parse tree produced by the {@code thisExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterThisExpr(P4Parser.ThisExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code thisExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitThisExpr(P4Parser.ThisExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code structDotsExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterStructDotsExpr(P4Parser.StructDotsExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code structDotsExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitStructDotsExpr(P4Parser.StructDotsExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code integerExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterIntegerExpr(P4Parser.IntegerExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code integerExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitIntegerExpr(P4Parser.IntegerExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code modExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterModExpr(P4Parser.ModExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code modExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitModExpr(P4Parser.ModExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code castExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterCastExpr(P4Parser.CastExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code castExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitCastExpr(P4Parser.CastExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code trueExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterTrueExpr(P4Parser.TrueExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code trueExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitTrueExpr(P4Parser.TrueExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code subExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterSubExpr(P4Parser.SubExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code subExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitSubExpr(P4Parser.SubExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code bandExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterBandExpr(P4Parser.BandExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code bandExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitBandExpr(P4Parser.BandExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code parenExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterParenExpr(P4Parser.ParenExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code parenExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitParenExpr(P4Parser.ParenExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code concatExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterConcatExpr(P4Parser.ConcatExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code concatExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitConcatExpr(P4Parser.ConcatExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code neqExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterNeqExpr(P4Parser.NeqExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code neqExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitNeqExpr(P4Parser.NeqExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code typeCallExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterTypeCallExpr(P4Parser.TypeCallExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code typeCallExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitTypeCallExpr(P4Parser.TypeCallExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code grtExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterGrtExpr(P4Parser.GrtExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code grtExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitGrtExpr(P4Parser.GrtExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code methodCallExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterMethodCallExpr(P4Parser.MethodCallExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code methodCallExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitMethodCallExpr(P4Parser.MethodCallExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code landExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterLandExpr(P4Parser.LandExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code landExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitLandExpr(P4Parser.LandExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ternaryExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterTernaryExpr(P4Parser.TernaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ternaryExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitTernaryExpr(P4Parser.TernaryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code lorExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterLorExpr(P4Parser.LorExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code lorExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitLorExpr(P4Parser.LorExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code structExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterStructExpr(P4Parser.StructExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code structExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitStructExpr(P4Parser.StructExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code mulExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterMulExpr(P4Parser.MulExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code mulExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitMulExpr(P4Parser.MulExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code divExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterDivExpr(P4Parser.DivExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code divExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitDivExpr(P4Parser.DivExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code falseExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterFalseExpr(P4Parser.FalseExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code falseExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitFalseExpr(P4Parser.FalseExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code listExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterListExpr(P4Parser.ListExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code listExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitListExpr(P4Parser.ListExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code shrExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterShrExpr(P4Parser.ShrExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code shrExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitShrExpr(P4Parser.ShrExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code constructorCallExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterConstructorCallExpr(P4Parser.ConstructorCallExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code constructorCallExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitConstructorCallExpr(P4Parser.ConstructorCallExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code stringLiteralExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterStringLiteralExpr(P4Parser.StringLiteralExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code stringLiteralExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitStringLiteralExpr(P4Parser.StringLiteralExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code invalidExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterInvalidExpr(P4Parser.InvalidExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code invalidExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitInvalidExpr(P4Parser.InvalidExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code lnotExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterLnotExpr(P4Parser.LnotExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code lnotExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitLnotExpr(P4Parser.LnotExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code memberExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterMemberExpr(P4Parser.MemberExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code memberExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitMemberExpr(P4Parser.MemberExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code plusSliceExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterPlusSliceExpr(P4Parser.PlusSliceExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code plusSliceExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitPlusSliceExpr(P4Parser.PlusSliceExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code addSatExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterAddSatExpr(P4Parser.AddSatExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code addSatExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitAddSatExpr(P4Parser.AddSatExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code arrayIndexExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterArrayIndexExpr(P4Parser.ArrayIndexExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code arrayIndexExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitArrayIndexExpr(P4Parser.ArrayIndexExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code uplusExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterUplusExpr(P4Parser.UplusExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code uplusExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitUplusExpr(P4Parser.UplusExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code sliceExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterSliceExpr(P4Parser.SliceExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code sliceExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitSliceExpr(P4Parser.SliceExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code dotsExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterDotsExpr(P4Parser.DotsExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code dotsExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitDotsExpr(P4Parser.DotsExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code borExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterBorExpr(P4Parser.BorExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code borExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitBorExpr(P4Parser.BorExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code errorMemberExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterErrorMemberExpr(P4Parser.ErrorMemberExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code errorMemberExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitErrorMemberExpr(P4Parser.ErrorMemberExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code eqExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterEqExpr(P4Parser.EqExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code eqExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitEqExpr(P4Parser.EqExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code addExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterAddExpr(P4Parser.AddExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code addExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitAddExpr(P4Parser.AddExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code lssExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterLssExpr(P4Parser.LssExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code lssExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitLssExpr(P4Parser.LssExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code cmplExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterCmplExpr(P4Parser.CmplExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code cmplExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitCmplExpr(P4Parser.CmplExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code negExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterNegExpr(P4Parser.NegExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code negExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitNegExpr(P4Parser.NegExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code pathExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterPathExpr(P4Parser.PathExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code pathExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitPathExpr(P4Parser.PathExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code leqExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterLeqExpr(P4Parser.LeqExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code leqExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitLeqExpr(P4Parser.LeqExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code shlExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterShlExpr(P4Parser.ShlExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code shlExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitShlExpr(P4Parser.ShlExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code geqExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterGeqExpr(P4Parser.GeqExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code geqExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitGeqExpr(P4Parser.GeqExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code subSatExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterSubSatExpr(P4Parser.SubSatExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code subSatExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitSubSatExpr(P4Parser.SubSatExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code bxorExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterBxorExpr(P4Parser.BxorExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code bxorExpr}
	 * labeled alternative in {@link P4Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitBxorExpr(P4Parser.BxorExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link P4Parser#nonBraceExpression}.
	 * @param ctx the parse tree
	 */
	void enterNonBraceExpression(P4Parser.NonBraceExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link P4Parser#nonBraceExpression}.
	 * @param ctx the parse tree
	 */
	void exitNonBraceExpression(P4Parser.NonBraceExpressionContext ctx);
}