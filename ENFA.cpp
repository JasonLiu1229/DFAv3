//
// Created by jason on 20/04/2022.
//

#include "ENFA.h"

ENFA::ENFA(const string &filename) : filename(filename) {}

ENFA::ENFA() {}

ENFA::~ENFA() {

}

const set<string> &ENFA::getAlphabet() const {
    return alphabet;
}

void ENFA::setAlphabet(const set<string> &alphabet) {
    ENFA::alphabet = alphabet;
}

State *ENFA::getStartState() const {
    return startState;
}

void ENFA::setStartState(State *startState) {
    ENFA::startState = startState;
}

const vector<State *> &ENFA::getStates() const {
    return states;
}

void ENFA::setStates(const vector<State *> &states) {
    ENFA::states = states;
}

const vector<TransitionNFA *> &ENFA::getTransitions() const {
    return transitions;
}

void ENFA::setTransitions(const vector<TransitionNFA *> &transitions) {
    ENFA::transitions = transitions;
}

const string &ENFA::getType() const {
    return type;
}

void ENFA::printStats() {

}

bool ENFA::accepts(const string &inputString) {
    return false;
}

void ENFA::addState(State* state) {
    states.push_back(state);
}
