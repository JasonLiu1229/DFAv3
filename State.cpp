//
// Created by liuja on 29/03/2022.
//

#include "State.h"

const string &State::getName() const {
    return name;
}

void State::setName(const string &name) {
    State::name = name;
}

bool State::isFinal() const {
    return final;
}

void State::setFinal(bool final) {
    State::final = final;
}

bool State::isStart() const {
    return start;
}

void State::setStart(bool start) {
    State::start = start;
}

State::State() {}

State::~State() {}

State::State(const string &name, bool final, bool start) : name(name), final(final), start(start) {}
