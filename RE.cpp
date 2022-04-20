//
// Created by jason on 20/04/2022.
//

#include "RE.h"
#include "State.h"

RE::RE(const string &regex, const char &typeS) : regex(regex) {
    if (typeS == 'e'){
        type = enfa;
    } else if (typeS == 'd'){
        type = dfa;
    } else if (typeS == 'n'){
        type = nfa;
    } else{
        type = none;
    }
}

const string &RE::getRegex() const {
    return regex;
}

void RE::setRegex(const string &regex) {
    RE::regex = regex;
}

automataType RE::getType() const {
    return type;
}

RE::RE() {}

RE::~RE() {

}

ENFA RE::toENFA() {
    ENFA enfa;

    auto* startState = new State();
    startState->setName("0");

    enfa.addState(startState);

    for (int i = 0; i < regex.size(); ++i) {
        if (regex[i] == '('){
            string tempString = regex.substr(i, i + regex.find(')'));
            recursionToENFAFinder(enfa, tempString);
        }
    }
}

void RE::recursionToENFAFinder(ENFA &enfa, const string &regex) {

}

