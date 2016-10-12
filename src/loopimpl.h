/*
 * loopimpl.h
 *
 *  Created on: May 17, 2012
 *      Author: boytim
 */

#ifndef LOOPIMPL_H_
#define LOOPIMPL_H_

Loop::Loop() {
    cond = 0;
    stmtseq = 0;
}

Loop::~Loop() {
    if (cond != 0)
	delete cond;
    if (stmtseq != 0)
	delete stmtseq;
}

bool Loop::parse() {
    if (toke->getTokenNumber() != 8) {
	printf("%s%s'\n", "Error: expected 'while', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
    cond = new Cond();
    if (!cond->parse()) {
	return false;
    }
    if (toke->getTokenNumber() != 9) {
	printf("%s%s'\n", "Error: expected 'loop', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
    stmtseq = new StmtSeq();
    if (!stmtseq->parse()) {
	return false;
    }
    if (toke->getTokenNumber() != 3) {
	printf("%s%s'\n", "Error: expected 'end', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
    if (toke->getTokenNumber() != 12) {
	printf("%s%s'\n", "Error: expected ';', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
}

void Loop::print(int spaces) {
    for (int i=0; i<spaces; i++) {
	printf("%c", ' ');
    }
    printf("%s", "while ");
    cond->print();
    printf("%s", " loop\n");
    stmtseq->print(spaces + INDENT);
    for (int i=0; i<spaces; i++) {
	printf("%c", ' ');
    }
    printf("%s", "end;\n");
}

void Loop::exec() {
    while (cond->exec()) {
	stmtseq->exec();
    }
}


#endif /* LOOPIMPL_H_ */
