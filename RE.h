//
// Created by jason on 20/04/2022.
//

#ifndef DFAV3_RE_H
#define DFAV3_RE_H
#include <string>

using namespace std;

enum automataType{enfa, dfa, nfa, none};

class RE {
    automataType type = none;
    string regex;
public:
    RE();

    RE(const string &regex, const string &typeS);

    const string &getRegex() const;

    void setRegex(const string &regex);

    automataType getType() const;

    virtual ~RE();
};


#endif //DFAV3_RE_H
