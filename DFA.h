//
// Created by jason on 02/04/2022.
//

#ifndef DFAV3_DFA_H
#define DFAV3_DFA_H
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

class DFA {
    // filename
    string filename;

    // alphabet
    set<char> alphabet;

    // start state
    State* startState;

    // all states
    set<State*> states;

    // all transitions
    vector<TransitionDFA*> transitions;

    // type
    const string type = "DFA";
public:
    DFA(const string &filename);

    const string &getFilename() const;

    void setFilename(const string &filename);

    const set<char> &getAlphabet() const;

    void setAlphabet(const set<char> &alphabet);

    State *getStartState() const;

    void setStartState(State *startState);

    const set<State *> &getStates() const;

    void setStates(const set<State *> &states);

    const vector<TransitionDFA *> &getTransitions() const;

    void setTransitions(const vector<TransitionDFA *> &transitions);

    const string &getType() const;

    DFA(DFA dfa1, DFA dfa2, bool UD);

    virtual ~DFA();

    void print();
};


#endif //DFAV3_DFA_H
