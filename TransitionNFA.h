//
// Created by jason on 20/04/2022.
//

#ifndef DFAV3_TRANSITIONNFA_H
#define DFAV3_TRANSITIONNFA_H
#include <string>
#include <set>
using namespace std;

class State;

class TransitionNFA {
    State* from;
    set<State*> to;
    string input;
public:
    virtual ~TransitionNFA();

public:
    TransitionNFA();

    State *getFrom() const;

    void setFrom(State *from);

    const set<State *> &getTo() const;

    void setTo(const set<State *> &to);

    const string &getInput() const;

    void setInput(const string &input);

    void addToState(State* toState);
};


#endif //DFAV3_TRANSITIONNFA_H
