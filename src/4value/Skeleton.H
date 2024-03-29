/* File generated by the BNF Converter (bnfc 2.9.3). */

#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.H"


class Skeleton : public Visitor {
public:
    void visitProgram(Program *p);

    void visitCodeBlock(CodeBlock *p);

    void visitNonJmpStmt(NonJmpStmt *p);

    void visitJmpStmt(JmpStmt *p);

    void visitAtom(Atom *p);

    void visitBinOp(BinOp *p);

    void visitProg(Prog *p);

    void visitBlock(Block *p);

    void visitStmtBinOp(StmtBinOp *p);

    void visitStmtNoOp(StmtNoOp *p);

    void visitStmtCall(StmtCall *p);

    void visitStmtDoNothing(StmtDoNothing *p);

    void visitStmtGoto(StmtGoto *p);

    void visitStmtGoNext(StmtGoNext *p);

    void visitStmtCondJmp(StmtCondJmp *p);

    void visitStmtRet(StmtRet *p);

    void visitStmtVRet(StmtVRet *p);

    void visitAtomVar(AtomVar *p);

    void visitAtomInt(AtomInt *p);

    void visitAtomStr(AtomStr *p);

    void visitAddOp(AddOp *p);

    void visitSubOp(SubOp *p);

    void visitMulOp(MulOp *p);

    void visitDivOp(DivOp *p);

    void visitModOp(ModOp *p);

    void visitLTH(LTH *p);

    void visitLE(LE *p);

    void visitGTH(GTH *p);

    void visitGE(GE *p);

    void visitEQU(EQU *p);

    void visitNE(NE *p);

    void visitListCodeBlock(ListCodeBlock *p);

    void visitListNonJmpStmt(ListNonJmpStmt *p);

    void visitListJmpStmt(ListJmpStmt *p);

    void visitListAtom(ListAtom *p);

    void visitInteger(Integer x);

    void visitChar(Char x);

    void visitDouble(Double x);

    void visitString(String x);

    void visitIdent(Ident x);

    void visitUIdent(UIdent x);

};


#endif
