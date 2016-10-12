/*
 * input.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef INPUT_H_
#define INPUT_H_

class IdList;

class Input {
    IdList* idl;
public:
    Input();
    ~Input();

    bool parse();
    void print(int);
    void exec();
};


#endif /* INPUT_H_ */
