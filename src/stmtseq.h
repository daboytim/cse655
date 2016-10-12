/*
 * stmtseq.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef STMT_SEQ_H_
#define STMT_SEQ_H_

#include "stmt.h"

class StmtSeq {
    Stmt* stmt;
    StmtSeq* stmtseq;
public:
    StmtSeq();
    ~StmtSeq();

    bool parse();
    void print(int);
    void exec();
};

StmtSeq::StmtSeq() {
    stmt = 0;
    stmtseq = 0;
}

StmtSeq::~StmtSeq() {
    if (stmt != 0)
	delete stmt;
    if (stmtseq != 0)
	delete stmtseq;
}

bool StmtSeq::parse() {
    stmt = new Stmt();
    if (!stmt->parse()) {
	return false;
    }
    stmtseq = new StmtSeq();
    if (!stmtseq->parse()) {
	delete stmtseq;
	stmtseq = 0;
    }
    return true;
}

void StmtSeq::print(int spaces) {
    stmt->print(spaces);
    if (stmtseq != 0)
	stmtseq->print(spaces);
}

void StmtSeq::exec() {
    stmt->exec();
    if (stmtseq != 0)
	stmtseq->exec();
}


#endif /* STMT_SEQ_H_ */
