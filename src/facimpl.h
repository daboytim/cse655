/*
 * facimpl.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef FACIMPL_H_
#define FACIMPL_H_

Fac::Fac() {
    op = 0;
    fac = 0;
}

Fac::~Fac() {
    if (op != 0)
	delete op;
    if (fac != 0)
	delete fac;
}

bool Fac::parse() {
    op = new Op();
    if (!op->parse()) {
	return false;
    }
    if (toke->getTokenNumber() == 24) {
	toke->skipToken();
	fac = new Fac();
	if (!fac->parse()) {
	    return false;
	}
    }
    return true;
}

void Fac::print() {
    op->print();
    if (fac != 0) {
	printf("%s", "*");
	fac->print();
    }
}

int Fac::exec() {
    int opval = op->exec();
    if (fac != 0)
	return opval*fac->exec();
    return opval;
}


#endif /* FACIMPL_H_ */
