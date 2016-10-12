/*
 * if.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef IF_H_
#define IF_H_

#include "cond.h"

class StmtSeq;

class If {
    Cond* cond;
    StmtSeq* stmtseq1;
    StmtSeq* stmtseq2;
public:
    If();
    ~If();

    bool parse();
    void print(int);
    void exec();
};


#endif /* IF_H_ */
