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
class TransitionNFA;

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
    vector<TransitionNFA*> transitions;

    // type
    const string type = "ENFA";

public:
    // constructors
    ENFA();

    ENFA(const string &filename);

    // getter setters
    const set<string> &getAlphabet() const;

    void setAlphabet(const set<string> &alphabet);

    State *getStartState() const;

    void setStartState(State *startState);

    const vector<State *> &getStates() const;

    void setStates(const vector<State *> &states);

    const vector<TransitionNFA *> &getTransitions() const;

    void setTransitions(const vector<TransitionNFA *> &transitions);

    const string &getType() const;

    void addState(State* state);

    // other functions
    void printStats();

    bool accepts(const string &inputString);

    // destructors
    virtual ~ENFA();

};


#endif //DFAV3_ENFA_H
