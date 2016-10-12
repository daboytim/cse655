/*
 * opimpl.h
 *
 *  Created on: May 17, 2012
 *      Author: boytim
 */

#ifndef OPIMPL_H_
#define OPIMPL_H_

Op::Op() {
    tni = 0;
    id = 0;
    exp = 0;
}

Op::~Op() {
    if (tni != 0)
	delete tni;
    if (id != 0)
	delete id;
    if (exp != 0)
	delete exp;
}

bool Op::parse() {
    int tn = toke->getTokenNumber();
    if (tn == 31) {
	tni = new Int();
	return tni->parse();
    } else if (tn == 32) {
	id = new Id();
	return id->parse();
    } else if (tn == 20) {
	toke->skipToken();
	exp = new Exp();
	if (!exp->parse()) {
	    return false;
	}
	if (toke->getTokenNumber() != 21) {
	    printf("%s\n", "Error: didnt find '('");
	    return false;
	}
	toke->skipToken();
    } else {
	printf("%s\n", "Error parsing op");
	return false;
    }
    return true;
}

void Op::print() {
    if (tni != 0) {
	tni->print();
    } else if (id != 0) {
	id->print();
    } else if (exp != 0) {
	printf("%s", "(");
	exp->print();
	printf("%s", ")");
    }
}

int Op::exec() {
    if (tni != 0) {
	return tni->exec();
    } else if (id != 0) {
	string idstr = id->exec();
	if (idstr == "") {
	     printf("%s%s%s\n", "Error: id '", id->getId().c_str(), "' not initialized");
	    printf("%s\n", "Program execution may be unpredictable");
	}
	return (*(idTable->ids))[id->getId()]->value;
    } else if (exp != 0) {
	return exp->exec();
    }
    return 0;
}


#endif /* OPIMPL_H_ */
