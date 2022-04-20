//
// Created by jason on 20/04/2022.
//

#ifndef DFAV3_RE_H
#define DFAV3_RE_H
#include <string>
#include "ENFA.h"

using namespace std;

enum automataType{enfa, dfa, nfa, none};

class RE {
    automataType type = none;
    string regex;
public:
    RE();

    RE(const string &regex, const char &typeS);

    const string &getRegex() const;

    void setRegex(const string &regex);

    automataType getType() const;

    ENFA toENFA();

    void recursionToENFAFinder(ENFA &enfa, const string& regex);

    ENFA createConcatanation(const string &input1, const string &input2);

    ENFA createKleenStar(const string &input);

    ENFA createUnion(const string &input1, const string &input2);

    virtual ~RE();
};


#endif //DFAV3_RE_H
