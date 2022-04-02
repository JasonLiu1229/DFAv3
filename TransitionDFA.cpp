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

char TransitionDFA::getInput() const {
    return input;
}

void TransitionDFA::setInput(char input) {
    TransitionDFA::input = input;
}

TransitionDFA::TransitionDFA() {}

TransitionDFA::~TransitionDFA() {}

TransitionDFA::TransitionDFA(State *from, State *to, char input) : from(from), to(to), input(input) {}
