//
// Created by jason on 02/04/2022.
//

#include "DFA.h"
#include "State.h"
#include "TransitionDFA.h"

DFA::DFA(const string &filename) : filename(filename) {

}

const string &DFA::getFilename() const {
    return filename;
}

void DFA::setFilename(const string &filename) {
    DFA::filename = filename;
}

const set<char> &DFA::getAlphabet() const {
    return alphabet;
}

void DFA::setAlphabet(const set<char> &alphabet) {
    DFA::alphabet = alphabet;
}

State *DFA::getStartState() const {
    return startState;
}

void DFA::setStartState(State *startState) {
    DFA::startState = startState;
}

const set<State *> &DFA::getStates() const {
    return states;
}

void DFA::setStates(const set<State *> &states) {
    DFA::states = states;
}

const vector<TransitionDFA *> &DFA::getTransitions() const {
    return transitions;
}

void DFA::setTransitions(const vector<TransitionDFA *> &transitions) {
    DFA::transitions = transitions;
}

const string &DFA::getType() const {
    return type;
}

DFA::DFA(DFA dfa1, DFA dfa2, bool UD) {

}

DFA::~DFA() {
    for (auto &state : states) {
        delete state;
    }
    states.clear();
    for (auto &trans : transitions) {
        delete trans;
    }
    transitions.clear();
}

void DFA::print() {
    json dfa;

    for (auto & i : alphabet) {
        string s1;
        s1 = (char)i;
        dfa["alphabet"] += s1;
    }

    for (auto state: states) {
        bool final = state->isFinal();
        bool start = state->isStart();
        dfa["states"] += {{"accepting", final},
                          {"name",      state->getName()},
                          {"starting",  start}};
    }

    for (auto transition : transitions){
        string s1;
        s1 = (char)transition->getInput();
        dfa["transitions"] += {{"from", transition->getFrom()->getName()}, {"input", s1},{"to", transition->getTo()->getName()}};
    }

    dfa["type"] = type;

    cout << setw(4) << dfa << endl;
}
