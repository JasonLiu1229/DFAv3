//
// Created by jason on 20/04/2022.
//

#ifndef DFAV3_ENFA_H
#define DFAV3_ENFA_H
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <set>
#include <map>

#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class State;
class TransitionDFA;

class ENFA {
    // filename
    string filename;

    // alphabet
    set<string> alphabet;

    // start state
    State* startState;

    // all states
    vector<State*> states;

    // all transitions
    vector<TransitionDFA*> transitions;

    // type
    const string type = "DFA";
};


#endif //DFAV3_ENFA_H
