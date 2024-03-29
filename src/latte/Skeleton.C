#pragma once
/* File generated by the BNF Converter (bnfc 2.9.3). */

/*** Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Skeleton.H"


void Skeleton::visitProgram(Program *t) {} //abstract class
void Skeleton::visitTopDef(TopDef *t) {} //abstract class
void Skeleton::visitArg(Arg *t) {} //abstract class
void Skeleton::visitClassMember(ClassMember *t) {} //abstract class
void Skeleton::visitBlock(Block *t) {} //abstract class
void Skeleton::visitStmt(Stmt *t) {} //abstract class
void Skeleton::visitItem(Item *t) {} //abstract class
void Skeleton::visitComplexStart(ComplexStart *t) {} //abstract class
void Skeleton::visitComplexPart(ComplexPart *t) {} //abstract class
void Skeleton::visitTypeName(TypeName *t) {} //abstract class
void Skeleton::visitType(Type *t) {} //abstract class
void Skeleton::visitExpr(Expr *t) {} //abstract class
void Skeleton::visitAddOp(AddOp *t) {} //abstract class
void Skeleton::visitMulOp(MulOp *t) {} //abstract class
void Skeleton::visitRelOp(RelOp *t) {} //abstract class

void Skeleton::visitProg(Prog *prog) {
    /* Code For Prog Goes Here */

    if (prog->listtopdef_) prog->listtopdef_->accept(this);

}

void Skeleton::visitFnDef(FnDef *fn_def) {
    /* Code For FnDef Goes Here */

    if (fn_def->type_) fn_def->type_->accept(this);
    visitIdent(fn_def->ident_);
    if (fn_def->listarg_) fn_def->listarg_->accept(this);
    if (fn_def->block_) fn_def->block_->accept(this);

}

void Skeleton::visitClassDef(ClassDef *class_def) {
    /* Code For ClassDef Goes Here */

    visitIdent(class_def->ident_);
    if (class_def->listclassmember_) class_def->listclassmember_->accept(this);

}

void Skeleton::visitClassExtendDef(ClassExtendDef *class_extend_def) {
    /* Code For ClassExtendDef Goes Here */

    visitIdent(class_extend_def->ident_1);
    visitIdent(class_extend_def->ident_2);
    if (class_extend_def->listclassmember_) class_extend_def->listclassmember_->accept(this);

}

void Skeleton::visitAr(Ar *ar) {
    /* Code For Ar Goes Here */

    if (ar->type_) ar->type_->accept(this);
    visitIdent(ar->ident_);

}

void Skeleton::visitAttrMember(AttrMember *attr_member) {
    /* Code For AttrMember Goes Here */

    if (attr_member->type_) attr_member->type_->accept(this);
    if (attr_member->listitem_) attr_member->listitem_->accept(this);

}

void Skeleton::visitMethodMember(MethodMember *method_member) {
    /* Code For MethodMember Goes Here */

    if (method_member->type_) method_member->type_->accept(this);
    visitIdent(method_member->ident_);
    if (method_member->listarg_) method_member->listarg_->accept(this);
    if (method_member->block_) method_member->block_->accept(this);

}

void Skeleton::visitBlk(Blk *blk) {
    /* Code For Blk Goes Here */

    if (blk->liststmt_) blk->liststmt_->accept(this);

}

void Skeleton::visitEmpty(Empty *empty) {
    /* Code For Empty Goes Here */


}

void Skeleton::visitBStmt(BStmt *b_stmt) {
    /* Code For BStmt Goes Here */

    if (b_stmt->block_) b_stmt->block_->accept(this);

}

void Skeleton::visitDecl(Decl *decl) {
    /* Code For Decl Goes Here */

    if (decl->type_) decl->type_->accept(this);
    if (decl->listitem_) decl->listitem_->accept(this);

}

void Skeleton::visitAss(Ass *ass) {
    /* Code For Ass Goes Here */

    if (ass->expr_1) ass->expr_1->accept(this);
    if (ass->expr_2) ass->expr_2->accept(this);

}

void Skeleton::visitIncr(Incr *incr) {
    /* Code For Incr Goes Here */

    if (incr->expr_) incr->expr_->accept(this);

}

void Skeleton::visitDecr(Decr *decr) {
    /* Code For Decr Goes Here */

    if (decr->expr_) decr->expr_->accept(this);

}

void Skeleton::visitRet(Ret *ret) {
    /* Code For Ret Goes Here */

    if (ret->expr_) ret->expr_->accept(this);

}

void Skeleton::visitVRet(VRet *v_ret) {
    /* Code For VRet Goes Here */


}

void Skeleton::visitCond(Cond *cond) {
    /* Code For Cond Goes Here */

    if (cond->expr_) cond->expr_->accept(this);
    if (cond->stmt_) cond->stmt_->accept(this);

}

void Skeleton::visitCondElse(CondElse *cond_else) {
    /* Code For CondElse Goes Here */

    if (cond_else->expr_) cond_else->expr_->accept(this);
    if (cond_else->stmt_1) cond_else->stmt_1->accept(this);
    if (cond_else->stmt_2) cond_else->stmt_2->accept(this);

}

void Skeleton::visitWhile(While *while_) {
    /* Code For While Goes Here */

    if (while_->expr_) while_->expr_->accept(this);
    if (while_->stmt_) while_->stmt_->accept(this);

}

void Skeleton::visitForEach(ForEach *for_each) {
    /* Code For ForEach Goes Here */

    if (for_each->typename_) for_each->typename_->accept(this);
    visitIdent(for_each->ident_1);
    visitIdent(for_each->ident_2);
    if (for_each->stmt_) for_each->stmt_->accept(this);

}

void Skeleton::visitSExp(SExp *s_exp) {
    /* Code For SExp Goes Here */

    if (s_exp->expr_) s_exp->expr_->accept(this);

}

void Skeleton::visitNoInit(NoInit *no_init) {
    /* Code For NoInit Goes Here */

    visitIdent(no_init->ident_);

}

void Skeleton::visitInit(Init *init) {
    /* Code For Init Goes Here */

    visitIdent(init->ident_);
    if (init->expr_) init->expr_->accept(this);

}

void Skeleton::visitCBracketed(CBracketed *c_bracketed) {
    /* Code For CBracketed Goes Here */

    if (c_bracketed->complexstart_) c_bracketed->complexstart_->accept(this);

}

void Skeleton::visitCMember(CMember *c_member) {
    /* Code For CMember Goes Here */

    visitIdent(c_member->ident_1);
    visitIdent(c_member->ident_2);

}

void Skeleton::visitCMemberB(CMemberB *c_member_b) {
    /* Code For CMemberB Goes Here */

    visitIdent(c_member_b->ident_1);
    visitIdent(c_member_b->ident_2);

}

void Skeleton::visitCArray(CArray *c_array) {
    /* Code For CArray Goes Here */

    if (c_array->typename_) c_array->typename_->accept(this);
    if (c_array->expr_) c_array->expr_->accept(this);

}

void Skeleton::visitCArrayB(CArrayB *c_array_b) {
    /* Code For CArrayB Goes Here */

    visitIdent(c_array_b->ident_);
    if (c_array_b->expr_) c_array_b->expr_->accept(this);

}

void Skeleton::visitCFunction(CFunction *c_function) {
    /* Code For CFunction Goes Here */

    visitIdent(c_function->ident_);
    if (c_function->listexpr_) c_function->listexpr_->accept(this);

}

void Skeleton::visitNewObject(NewObject *new_object) {
    /* Code For NewObject Goes Here */

    if (new_object->typename_) new_object->typename_->accept(this);

}

void Skeleton::visitNewArray(NewArray *new_array) {
    /* Code For NewArray Goes Here */

    if (new_array->typename_) new_array->typename_->accept(this);
    if (new_array->expr_) new_array->expr_->accept(this);

}

void Skeleton::visitVariable(Variable *variable) {
    /* Code For Variable Goes Here */

    visitIdent(variable->ident_);

}

void Skeleton::visitArrElement(ArrElement *arr_element) {
    /* Code For ArrElement Goes Here */

    if (arr_element->expr_) arr_element->expr_->accept(this);

}

void Skeleton::visitMethod(Method *method) {
    /* Code For Method Goes Here */

    if (method->listexpr_) method->listexpr_->accept(this);

}

void Skeleton::visitInt(Int *int_) {
    /* Code For Int Goes Here */


}

void Skeleton::visitStr(Str *str) {
    /* Code For Str Goes Here */


}

void Skeleton::visitBool(Bool *bool_) {
    /* Code For Bool Goes Here */


}

void Skeleton::visitVoid(Void *void_) {
    /* Code For Void Goes Here */


}

void Skeleton::visitClass(Class *class_) {
    /* Code For Class Goes Here */

    visitIdent(class_->ident_);

}

void Skeleton::visitArr(Arr *arr) {
    /* Code For Arr Goes Here */

    if (arr->typename_) arr->typename_->accept(this);

}

void Skeleton::visitNotArr(NotArr *not_arr) {
    /* Code For NotArr Goes Here */

    if (not_arr->typename_) not_arr->typename_->accept(this);

}

void Skeleton::visitEVar(EVar *e_var) {
    /* Code For EVar Goes Here */

    visitIdent(e_var->ident_);

}

void Skeleton::visitEBracketVar(EBracketVar *e_bracket_var) {
    /* Code For EBracketVar Goes Here */

    visitIdent(e_bracket_var->ident_);

}

void Skeleton::visitEComplex(EComplex *e_complex) {
    /* Code For EComplex Goes Here */

    if (e_complex->complexstart_) e_complex->complexstart_->accept(this);
    if (e_complex->listcomplexpart_) e_complex->listcomplexpart_->accept(this);

}

void Skeleton::visitENullCast(ENullCast *e_null_cast) {
    /* Code For ENullCast Goes Here */

    visitIdent(e_null_cast->ident_);

}

void Skeleton::visitELitInt(ELitInt *e_lit_int) {
    /* Code For ELitInt Goes Here */

    visitInteger(e_lit_int->integer_);

}

void Skeleton::visitELitTrue(ELitTrue *e_lit_true) {
    /* Code For ELitTrue Goes Here */


}

void Skeleton::visitELitFalse(ELitFalse *e_lit_false) {
    /* Code For ELitFalse Goes Here */


}

void Skeleton::visitEString(EString *e_string) {
    /* Code For EString Goes Here */

    visitString(e_string->string_);

}

void Skeleton::visitNeg(Neg *neg) {
    /* Code For Neg Goes Here */

    if (neg->expr_) neg->expr_->accept(this);

}

void Skeleton::visitNot(Not *not_) {
    /* Code For Not Goes Here */

    if (not_->expr_) not_->expr_->accept(this);

}

void Skeleton::visitEMul(EMul *e_mul) {
    /* Code For EMul Goes Here */

    if (e_mul->expr_1) e_mul->expr_1->accept(this);
    if (e_mul->mulop_) e_mul->mulop_->accept(this);
    if (e_mul->expr_2) e_mul->expr_2->accept(this);

}

void Skeleton::visitEAdd(EAdd *e_add) {
    /* Code For EAdd Goes Here */

    if (e_add->expr_1) e_add->expr_1->accept(this);
    if (e_add->addop_) e_add->addop_->accept(this);
    if (e_add->expr_2) e_add->expr_2->accept(this);

}

void Skeleton::visitERel(ERel *e_rel) {
    /* Code For ERel Goes Here */

    if (e_rel->expr_1) e_rel->expr_1->accept(this);
    if (e_rel->relop_) e_rel->relop_->accept(this);
    if (e_rel->expr_2) e_rel->expr_2->accept(this);

}

void Skeleton::visitEAnd(EAnd *e_and) {
    /* Code For EAnd Goes Here */

    if (e_and->expr_1) e_and->expr_1->accept(this);
    if (e_and->expr_2) e_and->expr_2->accept(this);

}

void Skeleton::visitEOr(EOr *e_or) {
    /* Code For EOr Goes Here */

    if (e_or->expr_1) e_or->expr_1->accept(this);
    if (e_or->expr_2) e_or->expr_2->accept(this);

}

void Skeleton::visitPlus(Plus *plus) {
    /* Code For Plus Goes Here */


}

void Skeleton::visitMinus(Minus *minus) {
    /* Code For Minus Goes Here */


}

void Skeleton::visitTimes(Times *times) {
    /* Code For Times Goes Here */


}

void Skeleton::visitDiv(Div *div) {
    /* Code For Div Goes Here */


}

void Skeleton::visitMod(Mod *mod) {
    /* Code For Mod Goes Here */


}

void Skeleton::visitLTH(LTH *lth) {
    /* Code For LTH Goes Here */


}

void Skeleton::visitLE(LE *le) {
    /* Code For LE Goes Here */


}

void Skeleton::visitGTH(GTH *gth) {
    /* Code For GTH Goes Here */


}

void Skeleton::visitGE(GE *ge) {
    /* Code For GE Goes Here */


}

void Skeleton::visitEQU(EQU *equ) {
    /* Code For EQU Goes Here */


}

void Skeleton::visitNE(NE *ne) {
    /* Code For NE Goes Here */


}


void Skeleton::visitListClassMember(ListClassMember *list_class_member) {
    for (ListClassMember::iterator i = list_class_member->begin(); i != list_class_member->end(); ++i) {
        (*i)->accept(this);
    }
}

void Skeleton::visitListTopDef(ListTopDef *list_top_def) {
    for (ListTopDef::iterator i = list_top_def->begin(); i != list_top_def->end(); ++i) {
        (*i)->accept(this);
    }
}

void Skeleton::visitListArg(ListArg *list_arg) {
    for (ListArg::iterator i = list_arg->begin(); i != list_arg->end(); ++i) {
        (*i)->accept(this);
    }
}

void Skeleton::visitListStmt(ListStmt *list_stmt) {
    for (ListStmt::iterator i = list_stmt->begin(); i != list_stmt->end(); ++i) {
        (*i)->accept(this);
    }
}

void Skeleton::visitListItem(ListItem *list_item) {
    for (ListItem::iterator i = list_item->begin(); i != list_item->end(); ++i) {
        (*i)->accept(this);
    }
}

void Skeleton::visitListComplexPart(ListComplexPart *list_complex_part) {
    for (ListComplexPart::iterator i = list_complex_part->begin(); i != list_complex_part->end(); ++i) {
        (*i)->accept(this);
    }
}

void Skeleton::visitListExpr(ListExpr *list_expr) {
    for (ListExpr::iterator i = list_expr->begin(); i != list_expr->end(); ++i) {
        (*i)->accept(this);
    }
}


void Skeleton::visitInteger(Integer x) {
    /* Code for Integer Goes Here */
}

void Skeleton::visitChar(Char x) {
    /* Code for Char Goes Here */
}

void Skeleton::visitDouble(Double x) {
    /* Code for Double Goes Here */
}

void Skeleton::visitString(String x) {
    /* Code for String Goes Here */
}

void Skeleton::visitIdent(Ident x) {
    /* Code for Ident Goes Here */
}



