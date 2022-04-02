//
// Created by liuja on 29/03/2022.
//

#ifndef DFAV2_TRANSITIONDFA_H
#define DFAV2_TRANSITIONDFA_H

class State;

class TransitionDFA {
    State* from;
    State* to;
    char input;
public:
    State *getFrom() const;

    void setFrom(State *from);

    State *getTo() const;

    void setTo(State *to);

    char getInput() const;

    void setInput(char input);

    TransitionDFA();

    TransitionDFA(State *from, State *to, char input);

    virtual ~TransitionDFA();
};


#endif //DFAV2_TRANSITIONDFA_H
