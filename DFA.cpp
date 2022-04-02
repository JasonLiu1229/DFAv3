//
// Created by jason on 02/04/2022.
//

#include "DFA.h"
#include "State.h"
#include "TransitionDFA.h"

DFA::DFA(const string &filename) : filename(filename) {
    ifstream input(filename);

    json js;
    input >> js;

    // alphabet
    for (auto it  = js["alphabet"].begin(); it != js["alphabet"].end() ; ++it) {
        string kar = *it;

        alphabet.insert(kar);
    }

    // states
    auto statesA = js["states"];

    for (auto stateA : statesA){
        auto* state = new State(stateA["name"], (bool)stateA["accepting"], (bool)stateA["starting"]);
        states.push_back(state);
        if (state->isStart()){
            startState = state;
        }
    }

    // transitions
    auto transistionsA = js["transitions"];

    for (auto transitionA : transistionsA){
        string s1 = transitionA["input"];
        auto* trans = new TransitionDFA(retrieveState(transitionA["from"]), retrieveState(transitionA["to"]),
                                              s1);
        transitions.push_back(trans);
    }

    createTable();

}

const string &DFA::getFilename() const {
    return filename;
}

void DFA::setFilename(const string &filename) {
    DFA::filename = filename;
}

State *DFA::getStartState() const {
    return startState;
}

void DFA::setStartState(State *startState) {
    DFA::startState = startState;
}

const vector<State *> &DFA::getStates() const {
    return states;
}

void DFA::setStates(const vector<State *> &states) {
    DFA::states = states;
}

const vector<TransitionDFA *> &DFA::getTransitions() const {
    return transitions;
}

void DFA::setTransitions(const vector<TransitionDFA *> &transitions) {
    DFA::transitions = transitions;
}

const string &DFA::getType() const {
    return type;
}

DFA::~DFA() {
    for (auto &state : states) {
        delete state;
    }
    states.clear();
    for (auto &trans : transitions) {
        delete trans;
    }
    transitions.clear();
}

void DFA::print() {
    json dfa;

    for (auto & i : alphabet) {
        dfa["alphabet"] += i;
    }

    json stateJ;
    for (auto state: states) {
        stateJ["name"] = state->getName();
        if (state->isFinal()){
            stateJ["accepting"] = true;
        }
        else {
            stateJ["accepting"] = false;
        }
        if (state->isStart()){
            stateJ["starting"] = true;
        }
        else {
            stateJ["starting"] = false;
        }
        dfa["states"] += stateJ;
    }

    for (auto transition : transitions){
        string s1;
        s1 = transition->getInput();
        dfa["transitions"] += {{"from", transition->getFrom()->getName()}, {"input", s1},{"to", transition->getTo()->getName()}};
    }

    dfa["type"] = type;

    cout << setw(4) << dfa << endl;
}

State *DFA::retrieveState(const string &name) {
    for (State* state : states) {
        if(state->getName() == name){
            return state;
        }
    }
    return nullptr;
}


DFA::DFA(DFA &dfa1, DFA &dfa2, bool UD) {
    // alphabet
    set_intersection(dfa1.alphabet.begin(), dfa1.alphabet.end(), dfa2.alphabet.begin(), dfa2.alphabet.end(),
                     inserter(alphabet, alphabet.begin()));

    // startState
    auto* startStateNew = new State();
    startStateNew->setName(dfa1.getStartState()->getName() + dfa2.getStartState()->getName());
    startStateNew->setStart(true);

    if (UD){
        if (dfa1.getStartState()->isFinal() and dfa2.getStartState()->isFinal()){
            startStateNew->setFinal(true);
        }
        else {
            startStateNew->setFinal(false);
        }
        states.push_back(startStateNew);
        RecursionStateFinderPD(startStateNew, dfa1, dfa2);
    }
    else {
        if (dfa1.getStartState()->isFinal() or dfa2.getStartState()->isFinal()){
            startStateNew->setFinal(true);
        }
        else {
            startStateNew->setFinal(false);
        }
        states.push_back(startStateNew);
        RecursionStateFinderPU(startStateNew, dfa1, dfa2);
    }
    reformatNamesP();
}

void DFA::RecursionStateFinderPD(State *state, DFA &dfa1, DFA &dfa2) {
    for (auto alpha : alphabet){
        string name = state->getName();
        string newName = "";
        auto* newState = new State(newName, false, false);
        auto newTrans = new TransitionDFA(state, nullptr, alpha);

        // state 1
        string s1(1, name[0]);
        bool final1 = false;

        for (auto trans : dfa1.getTransitions()) {
            if (trans->getFrom()->getName() == s1 and trans->getInput() == alpha){
                newName += trans->getTo()->getName();
                if (trans->getTo()->isFinal()){
                    final1 = true;
                }
            }
        }

        // state 2
        string s2(1 , name[1]);
        bool final2 = false;

        for (auto trans : dfa2.getTransitions()) {
            if (trans->getFrom()->getName() == s2 and trans->getInput() == alpha){
                newName += trans->getTo()->getName();
                if (trans->getTo()->isFinal()){
                    final2 = true;
                }
            }
        }

        // Complete new state
        newState->setName(newName);
        if (final1 and final2){
            newState->setFinal(final1);
        }

        // Check if state exist
        State* tempState; // if state does exist --> transistion
        bool exist = false;
        for (auto stateE : states){
            if (stateE->getName() == newName){
                tempState = stateE;
                exist = true;
                delete newState;
            }
        }
        if (!exist){
            states.push_back(newState);
            tempState = newState;
        }

        // Transition
        newTrans->setTo(tempState);
        transitions.push_back(newTrans);

        if (!exist){
            RecursionStateFinderPD(newState, dfa1, dfa2);
        }
    }
}

void DFA::RecursionStateFinderPU(State *state, DFA &dfa1, DFA &dfa2) {
    for (auto alpha : alphabet){
        string name = state->getName();
        string newName = "";
        auto* newState = new State(newName, false, false);
        auto newTrans = new TransitionDFA(state, nullptr, alpha);

        // state 1
        string s1(1, name[0]);
        bool final1 = false;

        for (auto trans : dfa1.getTransitions()) {
            if (trans->getFrom()->getName() == s1 and trans->getInput() == alpha){
                newName += trans->getTo()->getName();
                if (trans->getTo()->isFinal()){
                    final1 = true;
                }
            }
        }

        // state 2
        string s2(1 , name[1]);
        bool final2 = false;

        for (auto trans : dfa2.getTransitions()) {
            if (trans->getFrom()->getName() == s2 and trans->getInput() == alpha){
                newName += trans->getTo()->getName();
                if (trans->getTo()->isFinal()){
                    final2 = true;
                }
            }
        }

        // Complete new state
        newState->setName(newName);
        if (final1 or final2){
            newState->setFinal(true);
        }

        // Check if state exist
        State* tempState; // if state does exist --> transistion
        bool exist = false;
        for (auto stateE : states){
            if (stateE->getName() == newName){
                tempState = stateE;
                exist = true;
                delete newState;
            }
        }
        if (!exist){
            states.push_back(newState);
            tempState = newState;
        }

        // Transition
        newTrans->setTo(tempState);
        transitions.push_back(newTrans);

        if (!exist){
            RecursionStateFinderPU(newState, dfa1, dfa2);
        }
    }
}

void DFA::reformatNamesP() {
    for (auto &state : states) {
        string newName = "(";
        string name = state->getName();
        for (int i = 0; i < name.size(); ++i) {
            newName += name[i];
            if (i + 1 < name.size()){
                newName += ',';
            }
        }
        newName += ')';

        state->setName(newName);
    }
}

const set<string> &DFA::getAlphabet() const {
    return alphabet;
}

void DFA::setAlphabet(const set<string> &alphabet) {
    DFA::alphabet = alphabet;
}


DFA DFA::minimize() {
    DFA newDFA;

    newDFA.alphabet = alphabet;

    // check for reachable states
    auto* newStartState = new State();
    newStartState->setName(startState->getName());
    newStartState->setStart(true);
    newStartState->setFinal(startState->isFinal());

    newDFA.setStartState(newStartState);
    newDFA.states.push_back(newStartState);

    recursionCheckReachable(newDFA, newDFA.getStartState());

    // create table
    newDFA.createTable();

    // mark final states
    // minimize

    return newDFA;
}

DFA::DFA() {}

void DFA::recursionCheckReachable(DFA &dfa, State* state) {
    for (auto alpha : dfa.alphabet) {
        for (auto trans : transitions){
            if (trans->getFrom()->getName() == state->getName() and trans->getInput() == alpha){
                auto* newState = new State(trans->getTo()->getName(), trans->getTo()->isFinal(), trans->getTo()->isStart());
                dfa.states.push_back(newState);
                recursionCheckReachable(dfa, newState);
            }
        }
    }
}

void DFA::createTable() {
    for (auto state1 : states){
        for (auto state2 : states){
            set<State*> koppel;
            koppel.insert(state1);
            koppel.insert(state2);

            if (koppel.size() != 1 and !koppel.empty()){
                table[koppel] = "-";
            }
        }
    }
}

void DFA::recursionTFA(int totalMarked) {

}
