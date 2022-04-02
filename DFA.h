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
    set<string> alphabet;

    // start state
    State* startState;

    // all states
    vector<State*> states;

    // all transitions
    vector<TransitionDFA*> transitions;

    // type
    const string type = "DFA";

    // table
    map<set<State*>, string> table;
public:
    DFA(const string &filename);

    const string &getFilename() const;

    void setFilename(const string &filename);

    State *getStartState() const;

    void setStartState(State *startState);

    const vector<State *> &getStates() const;

    const set<string> &getAlphabet() const;

    void setAlphabet(const set<string> &alphabet);

    void setStates(const vector<State *> &states);

    const vector<TransitionDFA *> &getTransitions() const;

    void setTransitions(const vector<TransitionDFA *> &transitions);

    const string &getType() const;

    DFA(DFA &dfa1, DFA &dfa2, bool UD);

    virtual ~DFA();

    void print();

    State* retrieveState(const string &name);

    void RecursionStateFinderPU(State* state, DFA &dfa1, DFA &dfa2);

    void RecursionStateFinderPD(State* state, DFA &dfa1, DFA &dfa2);

    void reformatNamesP();

    DFA minimize();

    DFA();

    void printTable();

    void recursionCheckReachable(DFA &dfa, State* state);

    void createTable();

    void recursionTFA(int totalMarked);
};


#endif //DFAV3_DFA_H
