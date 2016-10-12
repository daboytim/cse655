/*
 * ifimpl.h
 *
 *  Created on: May 17, 2012
 *      Author: boytim
 */

#ifndef IFIMPL_H_
#define IFIMPL_H_

If::If() {
    cond = 0;
    stmtseq1 = 0;
    stmtseq2 = 0;
}

If::~If() {
    if (cond != 0)
	delete cond;
    if (stmtseq1 != 0)
	delete stmtseq1;
    if (stmtseq2 != 0)
	delete stmtseq2;
}

bool If::parse() {
    if (toke->getTokenNumber() != 5) {
	printf("%s%s'\n", "Error: expected 'if', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
    cond = new Cond();
    if (!cond->parse()) {
	return false;
    }
    if (toke->getTokenNumber() != 6) {
	printf("%s%s'\n", "Error: expected 'then', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
    stmtseq1 = new StmtSeq();
    if (!stmtseq1->parse()) {
	return false;
    }
    if (toke->getTokenNumber() == 7) {
	toke->skipToken();
	stmtseq2 = new StmtSeq();
	if (!stmtseq2->parse()) {
	    return false;
	}
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

void If::print(int spaces) {
    for (int i=0; i<spaces; i++) {
	printf("%c", ' ');
    }
    printf("%s", "if ");
    cond->print();
    printf("%s", " then\n");
    stmtseq1->print(spaces + INDENT);
    if (stmtseq2 != 0) {
	for (int i=0; i<spaces; i++) {
	    printf("%c", ' ');
	}
	printf("%s", "else\n");
	stmtseq2->print(spaces + INDENT);
    }
    for (int i=0; i<spaces; i++) {
	printf("%c", ' ');
    }
    printf("%s", "end;\n");
	
}

void If::exec() {
    if (cond->exec()) {
	stmtseq1->exec();
    }
    if (stmtseq2 != 0) {
	stmtseq2->exec();
    }
}



#endif /* IFIMPL_H_ */
