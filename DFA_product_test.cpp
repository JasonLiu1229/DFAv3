#include "DFA.h"

using namespace std;

int main() {
    DFA dfa1("DFA_product3.json");
    DFA dfa2("DFA_product4.json");
    DFA product(dfa1, dfa2, false); // true betekent doorsnede, false betekent unie
    product.print();
    return 0;
}