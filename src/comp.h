/*
 * comp.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef COMP_H_
#define COMP_H_

#define NEQ 25
#define EQU 26
#define LTN 27
#define GTN 28
#define LEQ 29
#define GEQ 30

#include "op.h"

class Comp {
    Op* op1;
    Op* op2;
    int type;
public:
    Comp();
    ~Comp();

    bool parse();
    void print();
    bool exec();
};

Comp::Comp() {
    op1 = 0;
    op2 = 0;
    type = 0;
}

Comp::~Comp() {
    if (op1 != 0)
	delete op1;
    if (op2 != 0)
	delete op2;
}

bool Comp::parse() {
    int tn = toke->getTokenNumber();
    if (tn != 20) {
	printf("%s%s'\n", "Error: expected '(', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
    op1 = new Op();
    if (!op1->parse()) {
	return false;
    }
    tn = toke->getTokenNumber();
    if (tn >= NEQ && tn <= GEQ) {
	type = tn;
    } else {
	return false;
    }
    toke->skipToken();
    op2 = new Op();
    if (!op2->parse()) {
	return false;
    }
    tn = toke->getTokenNumber();
    if (tn != 21) {
	printf("%s%s'\n", "Error: expected '(', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
    return true;
}

void Comp::print() {
    printf("%s", "(");
    op1->print();
    switch (type) {
    case NEQ:
	printf(" %s ", "!=");
	break;
    case EQU:
	printf(" %s ", "==");
	break;
    case LTN:
	printf(" %s ", "<");
	break;
    case GTN:
	printf(" %s ", ">");
	break;
    case LEQ:
	printf(" %s ", "<=");
	break;
    case GEQ:
	printf(" %s ", ">=");
	break;
    }
    op2->print();
    printf("%s", ")");
}

bool Comp::exec() {
    switch (type) {
    case NEQ:
	return op1->exec() != op2->exec();
    case EQU:
	return op1->exec() == op2->exec();
    case LTN:
	return op1->exec() < op2->exec();
    case GTN:
	return op1->exec() > op2->exec();
    case LEQ:
	return op1->exec() <= op2->exec();
    case GEQ:
	return op1->exec() >= op2->exec();
    }
    return false;
}



#endif /* COMP_H_ */
