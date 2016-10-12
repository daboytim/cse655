/*
 * output.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

class IdList;

class Output {
    IdList* idl;
public:
    Output();
    ~Output();

    bool parse();
    void print(int);
    void exec();
};


#endif /* OUTPUT_H_ */
