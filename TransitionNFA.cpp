//
// Created by jason on 20/04/2022.
//

#include "TransitionNFA.h"

TransitionNFA::TransitionNFA() {}

TransitionNFA::~TransitionNFA() {

}

State *TransitionNFA::getFrom() const {
    return from;
}

void TransitionNFA::setFrom(State *from) {
    TransitionNFA::from = from;
}

const set<State *> &TransitionNFA::getTo() const {
    return to;
}

void TransitionNFA::setTo(const set<State *> &to) {
    TransitionNFA::to = to;
}

const string &TransitionNFA::getInput() const {
    return input;
}

void TransitionNFA::setInput(const string &input) {
    TransitionNFA::input = input;
}

void TransitionNFA::addToState(State *toState) {
    to.insert(toState);
}
