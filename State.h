//
// Created by liuja on 29/03/2022.
//

#ifndef DFAV2_STATE_H
#define DFAV2_STATE_H
#include <iostream>
#include <string>

using namespace std;

class State {
    string name;
    bool final = false;
    bool start = false;
public:
    const string &getName() const;

    void setName(const string &name);

    bool isFinal() const;

    void setFinal(bool final);

    bool isStart() const;

    void setStart(bool start);

    State();

    State(const string &name, bool final, bool start);

    virtual ~State();
};


#endif //DFAV2_STATE_H
