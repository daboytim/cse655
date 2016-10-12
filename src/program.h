/*
 * program.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#define INDENT 4

bool parseDsDone = false;

#include <vector>
#include "idvaltable.h"
#include "declseq.h"
#include "stmtseq.h"
#include "ifimpl.h"
#include "loopimpl.h"
#include "inputimpl.h"
#include "outputimpl.h"
#include "opimpl.h"
#include "facimpl.h"

class Program {
    DeclSeq* declseq;
    StmtSeq* stmtseq;
public:
    Program();
    ~Program();

    bool parse();
    void print();
    void exec();
};

Program::Program() {
    IdValTable::instance();
}

Program::~Program() {
    if (declseq != 0)
	delete declseq;
    if (stmtseq != 0)
	delete stmtseq;
}


bool Program::parse() {
    if (toke->getTokenNumber() == 1) {
	toke->skipToken();
	declseq = new DeclSeq();
	if (!declseq->parse()) {
	    return false;
	}
	parseDsDone = true;
    } else {
	printf("%s%s'\n", "Error: expected 'program', found '", toke->getToken().c_str());
	return false;
    }
    if (toke->getTokenNumber() == 2) {
	toke->skipToken();
	stmtseq = new StmtSeq();
	if (!stmtseq->parse()) {
	    return false;
	}
    } else {
	printf("%s%s'\n", "Error: expected 'begin', found '", toke->getToken().c_str());
	return false;
    }
    if (toke->getTokenNumber() != 3) {
	printf("%s%s'\n", "Error: expected 'end', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
    if (toke->getTokenNumber() != 33) {
	printf("%s%s'\n", "Error: expected 'EOF', found '", toke->getToken().c_str());
	return false;
    }
    return true;
}

void Program::print() {
    printf("%s\n", "program");
    declseq->print();
    printf("%s\n", "begin");
    stmtseq->print(INDENT);
    printf("%s\n", "end");
}

void Program::exec() {
    stmtseq->exec();
}


#endif //PROGRAM_H
