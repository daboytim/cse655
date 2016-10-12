/*
 * loop.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef LOOP_H_
#define LOOP_H_

#include "cond.h"

class StmtSeq;

class Loop {
    Cond* cond;
    StmtSeq* stmtseq;
public:
    Loop();
    ~Loop();

    bool parse();
    void print(int);
    void exec();
};


#endif /* LOOP_H_ */
