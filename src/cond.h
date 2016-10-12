/*
 * cond.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef COND_H_
#define COND_H_

#define NOT 1
#define AND 2
#define OR  3

#include "comp.h"

class Cond {
    Comp* comp;
    Cond* cond1;
    Cond* cond2;
    int type;
public:
    Cond();
    ~Cond();

    bool parse();
    void print();
    bool exec();
};

Cond::Cond() {
    comp = 0;
    cond1 = 0;
    cond2 = 0;
    type = 0;
}

Cond::~Cond() {
    if (comp != 0)
	delete comp;
    if (cond1 != 0)
	delete cond1;
    if (cond2 != 0)
	delete cond2;
}

bool Cond::parse() {
    int tn = toke->getTokenNumber();
    if (tn == 15) {
	type = NOT;
	toke->skipToken();
	cond1 = new Cond();
	return cond1->parse();
    } else if (tn == 16) {
	toke->skipToken();
	cond1 = new Cond();
	if (!cond1->parse()) {
	    return false;
	}
	tn = toke->getTokenNumber();
	if (tn == 18) {
	    type = AND;
	} else if (tn == 19) {
	    type = OR;
	} else {
	    return false;
	}
	toke->skipToken();
	cond2 = new Cond();
	if (!cond2->parse()) {
	    return false;
	}
	tn = toke->getTokenNumber();
	if (tn != 17) {
	    printf("%s\n", "Error: didnt find ']'");
	    return false;
	}
	toke->skipToken();
    } else {
	comp = new Comp();
	return comp->parse();
    }
    
    return true;
}

void Cond::print() {
    if (comp != 0) {
	comp->print();
	return;
    }
    switch (type) {
    case NOT:
	printf("%c", '!');
	cond1->print();
	break;
    case AND:
	printf("%c", '[');
	cond1->print();
	printf("%s", "&&");
	cond2->print();
	printf("%c", ']');
	break;
    case OR:
	printf("%c", '[');
	cond1->print();
	printf("%s", "||");
	cond2->print();
	printf("%c", ']');
	break;
    }
}

bool Cond::exec() {
    if (comp != 0) {
	return comp->exec();
    }
    switch (type) {
    case NOT:	
	return !cond1->exec();
    case AND:
	return cond1->exec() && cond2->exec();
    case OR:
	return cond1->exec() || cond2->exec();
    }
}



#endif /* COND_H_ */
