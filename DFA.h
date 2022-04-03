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

typedef map<set<State*>, string> Table;
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
    Table table;

    set<set<State*>> markedStates;

    set<State*> startingKoppel;
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

    void recursionTFA(int totalMarked, DFA &newDFA);

    void markSet(const set<State*> &koppelSet);

    void markSingleState(State* state);

    int checkTotalMarked();

    void convertTableTransitions(DFA &dfaRef);

    void reformatNamesTFA();

    void recursionTFAv2(int totalMarked);

    bool operator == (DFA &secondDFA);

    bool recursionCheckEquivalent(pair<State*, State*> koppel, set<pair<State*, State*>> &markedKoppels, DFA &secondDFA);

    Table createTablev2(DFA &secondDFA);

    void printTablev2(DFA &secondDFA);

    void recursionTFAv3(int totalMarked, DFA &secondDFA, Table& tableRef);

    static int checkTotalMarkedv2(const Table &tableRef);

    State* retrieveStatev2(const vector<State*> &vectorOfStates, const string &stateName);
};


#endif //DFAV3_DFA_H
