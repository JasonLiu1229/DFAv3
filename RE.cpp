//
// Created by jason on 20/04/2022.
//

#include "RE.h"

RE::RE(const string &regex, const string &typeS) : regex(regex) {
    if (typeS == "e"){
        type = enfa;
    } else if (typeS == "d"){
        type = dfa;
    } else if (typeS == "n"){
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
