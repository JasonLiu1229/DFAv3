#include "RE.h"
#include "ENFA.h"
#include <iostream>
using namespace std;

int main() {
    RE re("(m+y)*+(e+y+m+i)s",'e');
    ENFA enfa = re.toENFA();
    //enfa.printStats();
    /*// geven true
    cout << boolalpha << enfa.accepts("ys") << endl;
    cout << boolalpha << enfa.accepts("mmyyymmmym") << endl;
    cout << boolalpha << enfa.accepts("s") << endl;

    // geven false
    cout << boolalpha << enfa.accepts("ss") << endl;
    cout << boolalpha << enfa.accepts("ims") << endl;
    cout << boolalpha << enfa.accepts("mimis") << endl;*/

    return 0;
}