//
// Created by jamy on 10/1/17.
//

#ifndef SCANNER_STATES_H
#define SCANNER_STATES_H

class State;

class States {
public:
    State* white;
    State* identifier;
    State* number;
//    State* operators = new OperatorState();
};
#include "State.h"

#endif //SCANNER_STATES_H
