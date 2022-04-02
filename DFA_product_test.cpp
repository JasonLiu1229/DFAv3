#include "DFA.h"

using namespace std;

int main() {
    DFA dfa1("DFA_product.json");
    DFA dfa2("DFA2_product.json");
    DFA product(dfa1, dfa2, true); // true betekent doorsnede, false betekent unie
    product.print();
    return 0;
}