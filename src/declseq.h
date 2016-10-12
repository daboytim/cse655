/*
 * declseq.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef DEC_SEQ_H_
#define DEC_SEQ_H_

#include "decl.h"

class DeclSeq {
    Decl* decl;
    DeclSeq* declseq;
public:
    DeclSeq();
    ~DeclSeq();

    bool parse();
    void print();
};

DeclSeq::DeclSeq() {
    decl = 0;
    declseq = 0;
}

DeclSeq::~DeclSeq() {
    if (decl != 0)
	delete decl;
    if (declseq != 0)
	delete declseq;
}

bool DeclSeq::parse() {
    decl = new Decl();
    if (!decl->parse()) {
	return false;
    }
    if (toke->getTokenNumber() == 4) {
	declseq = new DeclSeq();
	return declseq->parse();
    }
    return true;
}

void DeclSeq::print() {
    decl->print();
    if (declseq != 0)
	declseq->print();
}



#endif /* DEC_SEQ_H_ */
