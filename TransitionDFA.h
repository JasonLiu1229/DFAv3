//
// Created by liuja on 29/03/2022.
//

#ifndef DFAV2_TRANSITIONDFA_H
#define DFAV2_TRANSITIONDFA_H
#include <string>
using namespace std;

class State;

class TransitionDFA {
    State* from;
    State* to;
    string input;
public:
    State *getFrom() const;

    void setFrom(State *from);

    State *getTo() const;

    void setTo(State *to);

    const string &getInput() const;

    void setInput(const string &input);

    TransitionDFA();

    TransitionDFA(State *from, State *to, string input);

    virtual ~TransitionDFA();
};


#endif //DFAV2_TRANSITIONDFA_H
