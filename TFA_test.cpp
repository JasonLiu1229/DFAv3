#include "DFA.h"

using namespace std;

int main() {
    DFA dfa("TFA.json");
    //DFA mindfa = dfa.minimize();
    DFA dfa2("TFA2.json");
    //dfa.printTable();
    //mindfa.print();
    cout << boolalpha << (dfa == dfa2) << endl;    // zijn ze equivalent? Zou hier zeker moeten. Dit wordt getest in de volgende vraag, maar hiermee kan je al eens proberen
    return 0;
}