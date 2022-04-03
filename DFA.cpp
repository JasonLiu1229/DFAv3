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

    // table
    createTable();

    // mark final states
    for (auto state : states) {
        if (state->isFinal()){
            markSingleState(state);
        }
    }

    int totalMarked = checkTotalMarked();

    recursionTFAv2(totalMarked);
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
    for (auto state : newDFA.getStates()) {
        if (state->isFinal()){
            newDFA.markSingleState(state);
        }
    }

    int totalMarked = newDFA.checkTotalMarked();

    // minimize
    recursionTFA(totalMarked, newDFA);

    // combine equivalent states
    newDFA.convertTableTransitions(*this);

    // convert name to right type of name {...}
    newDFA.reformatNamesTFA();

    return newDFA;
}

DFA::DFA() {}

void DFA::recursionCheckReachable(DFA &dfa, State* state) {
    for (auto alpha : dfa.alphabet) {
        for (auto trans : transitions){
            if (trans->getFrom()->getName() == state->getName() and trans->getInput() == alpha){
                auto* newState = new State(trans->getTo()->getName(), trans->getTo()->isFinal(), trans->getTo()->isStart());
                bool append = true;
                for (auto stateC : dfa.states){
                    if (stateC->getName() == newState->getName()){
                        append = false;
                        break;
                    }
                }
                if (append) {
                    dfa.states.push_back(newState);
                    recursionCheckReachable(dfa, newState);
                }
                else {
                    delete newState;
                }
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

void DFA::recursionTFA(int totalMarked, DFA &newDFA) {
    for (auto alpha : alphabet) {
        for (auto mKoppel : newDFA.markedStates) {
            // find new marked koppel
            vector<State*> newMkoppelV;
            set<State*> newMkoppelS;
            for (auto mState : mKoppel){
                newMkoppelV.push_back(mState);
            }
            for (auto trans : transitions) {
                for (auto trans2 : transitions) {
                    if (trans->getTo()->getName() == newMkoppelV[0]->getName() and trans2->getTo()->getName() == newMkoppelV[1]->getName() and trans->getInput() == alpha and trans2->getInput() == alpha){
                        newMkoppelS = {newDFA.retrieveState(trans->getFrom()->getName()), newDFA.retrieveState(trans2->getFrom()->getName())};


                        // mark new koppel
                        newDFA.markSet(newMkoppelS);
                    }
                }
            }

        }
    }
    int newTotalMarked = newDFA.checkTotalMarked();

    if (newTotalMarked > totalMarked){
        recursionTFA(newTotalMarked, newDFA);
    }
}

void DFA::markSet(const set<State*> &koppelSet) {
    for (auto &koppel : table) {
        if (koppelSet == koppel.first){
            koppel.second = "X";
            markedStates.insert(koppelSet);
            break;
        }
    }
}

void DFA::markSingleState(State *state) {
    for (auto &koppel : table) {
        for (auto stateK : koppel.first) {
            if (stateK == state){
                koppel.second = "X";
                markedStates.insert(koppel.first);
            }
        }
    }
}

int DFA::checkTotalMarked() {
    return markedStates.size();
}

void DFA::convertTableTransitions(DFA &dfaRef) {
    // find all equivalent states
    set<set<State*>> equivalentStates;
    for (auto koppel : table) {
        if (koppel.second == "-"){
            equivalentStates.insert(koppel.first);
        }
    }

    // combine koppels that have one common state
    set<set<State*>> newStates;
    bool equiFind = true;
    while (equiFind) {
        newStates = {};
        for (auto koppel1: equivalentStates) {
            for (auto koppel2: equivalentStates) {
                if (koppel1 != koppel2) {
                    set<State *> intersection;
                    set_intersection(koppel1.begin(), koppel1.end(), koppel2.begin(), koppel2.end(),
                                     inserter(intersection, intersection.begin()));
                    if (!intersection.empty()) {
                        set<State *> newState;
                        set_union(koppel1.begin(), koppel1.end(), koppel2.begin(), koppel2.end(),
                                  inserter(newState, newState.begin()));
                        newStates.insert(newState);
                    }
                }
            }
        }
        if (newStates.empty()) {
            equiFind = false;
        } else {
            equivalentStates = newStates;
        }
    }
    newStates = equivalentStates;
    // combine koppels to one state
    vector<vector<State*>> newStatesV;
    newStatesV.reserve(newStates.size());

    for (const auto& setStates : newStates){
        vector<State*> vStates;
        vStates.reserve(setStates.size());
        for (auto state : setStates) {
            vStates.push_back(state);
        }
        newStatesV.push_back(vStates);
    }

    vector<State*> vStatesSingle;
    for (auto &vStates : newStatesV) {
        // convert first state to combined state
        for (int i = 1; i < vStates.size(); ++i) {
            State* converterdState = vStates[0];
            converterdState->setName(converterdState->getName() + vStates[i]->getName());
            states.erase(remove(states.begin(), states.end(), vStates[i]), states.end());
            delete vStates[i];
        }

        vStates.erase(vStates.begin() + 1, vStates.end());
        vStatesSingle.push_back(vStates[0]);
    }

    // make transition
    for (auto alphe : alphabet) {
        for (auto trans: dfaRef.getTransitions()) {
            for (auto &state: states) {
                string nameState(1, state->getName()[0]);
                if (trans->getFrom()->getName() == nameState and trans->getInput() == alphe){
                    auto *transistion = new TransitionDFA();
                    transistion->setFrom(state);
                    transistion->setInput(alphe);
                    string nameTo = trans->getTo()->getName();
                    for (auto state : states){
                        if (state->getName().find(nameTo) != string::npos){
                            transistion->setTo(state);
                            transitions.push_back(transistion);
                        }
                    }
                }
            }
        }
    }
}

void DFA::reformatNamesTFA() {
    for (auto &state : states){
        string name = state->getName();
        sort(name.begin(), name.end());

        string newName = "{";

        for (int i = 0; i < name.size(); ++i) {
            newName += name[i];
            if (i + 1 < name.size()){
                newName += ',';
            }
        }

        newName += '}';

        state->setName(newName);
    }
}

void DFA::recursionTFAv2(int totalMarked) {
    /*for (auto alpha : alphabet) {
        for (auto mKoppel : newDFA.markedStates) {
            // find new marked koppel
            vector<State*> newMkoppelV;
            set<State*> newMkoppelS;
            for (auto mState : mKoppel){
                newMkoppelV.push_back(mState);
            }
            for (auto trans : transitions) {
                for (auto trans2 : transitions) {
                    if (trans->getTo()->getName() == newMkoppelV[0]->getName() and trans2->getTo()->getName() == newMkoppelV[1]->getName() and trans->getInput() == alpha and trans2->getInput() == alpha){
                        newMkoppelS = {newDFA.retrieveState(trans->getFrom()->getName()), newDFA.retrieveState(trans2->getFrom()->getName())};


                        // mark new koppel
                        newDFA.markSet(newMkoppelS);
                    }
                }
            }

        }
    }
    int newTotalMarked = newDFA.checkTotalMarked();

    if (newTotalMarked > totalMarked){
        recursionTFA(newTotalMarked, newDFA);
    }*/

    for (auto alpha : alphabet) {
        for (auto mKoppel : markedStates){
            vector<State*> newMkoppelV;
            set<State*> newMkoppelS;
            for (auto mState : mKoppel){
                newMkoppelV.push_back(mState);
            }
            for (auto trans : transitions) {
                for (auto trans2 : transitions) {
                    if (trans->getTo()->getName() == newMkoppelV[0]->getName() and trans2->getTo()->getName() == newMkoppelV[1]->getName() and trans->getInput() == alpha and trans2->getInput() == alpha){
                        newMkoppelS = {retrieveState(trans->getFrom()->getName()), retrieveState(trans2->getFrom()->getName())};


                        // mark new koppel
                        markSet(newMkoppelS);
                    }
                }
            }

        }
    }
    int newTotalMarked = checkTotalMarked();

    if (newTotalMarked > totalMarked){
        recursionTFAv2(newTotalMarked);
    }
}

void DFA::printTable() {
    string allStates;

    // get names of all states
    for (auto state : states){
        allStates += state->getName();
    }

    // sort names
    sort(allStates.begin(), allStates.end());

    // print table
    string printTable;
    for (int y = 1; y < allStates.size() + 1; ++y) {
        for (int x = 0; x < allStates.size(); ++x) {
            if (x == 0 and y != allStates.size()){
                string s1(1, allStates[y]);
                printTable += s1 + '\t';
            }
            else if (y == allStates.size() and x != allStates.size()-1){
                string s1(1, allStates[x]);
                printTable += '\t' + s1;
            }
            else {
                if (x <= y){
                    set<State*> koppel;
                    string state1Name(1, allStates[x-1]);
                    string state2Name(1, allStates[y]);
                    State* state1 = retrieveState(state1Name);
                    State* state2 = retrieveState(state2Name);
                    koppel.insert(state1);
                    koppel.insert(state2);
                    printTable += table[koppel] + '\t';
                }
            }
        }
        printTable += '\n';
    }
    cout << printTable << endl;
}
