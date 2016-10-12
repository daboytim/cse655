/*
 * exp.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef EXP_H_
#define EXP_H_

#define ADD '+'
#define SUB '-'

#include "fac.h"

class Exp {
    Fac* fac;
    Exp* exp;
    char type;
public:
    Exp();
    ~Exp();

    bool parse();
    void print();
    int exec();
};

Exp::Exp() {
    fac = 0;
    exp = 0;
    type = '\0';
}

Exp::~Exp() {
    if (fac != 0)
	delete fac;
    if (exp != 0)
	delete exp;
}

bool Exp::parse() {
    fac = new Fac();
    if (!fac->parse()) {
	return false;
    }
    int tn = toke->getTokenNumber();
    if (tn == 22) {
	toke->skipToken();
	type = ADD;
	exp = new Exp();
	if (!exp->parse()) {
	    return false;
	}
    } else if (tn == 23) {
	toke->skipToken();
	type = SUB;
	exp = new Exp();
	if (!exp->parse()) {
	    return false;
	}
    }
    return true;
}

void Exp::print() {
    fac->print();
    if (exp != 0) {
	printf(" %c ", type);
	exp->print();
    }
}

int Exp::exec() {
    int facval = fac->exec();
    if (type == ADD)
	return facval+exp->exec();
    else if (type == SUB)
	return facval-exp->exec();
    return facval;
}



#endif /* EXP_H_ */
