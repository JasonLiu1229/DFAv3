//
// Created by liuja on 29/03/2022.
//

#include "TransitionDFA.h"

State *TransitionDFA::getFrom() const {
    return from;
}

void TransitionDFA::setFrom(State *from) {
    TransitionDFA::from = from;
}

State *TransitionDFA::getTo() const {
    return to;
}

void TransitionDFA::setTo(State *to) {
    TransitionDFA::to = to;
}

TransitionDFA::TransitionDFA() {}

TransitionDFA::~TransitionDFA() {}

TransitionDFA::TransitionDFA(State *from, State *to, string input) : from(from), to(to), input(input) {}

const string &TransitionDFA::getInput() const {
    return input;
}

void TransitionDFA::setInput(const string &input) {
    TransitionDFA::input = input;
}
