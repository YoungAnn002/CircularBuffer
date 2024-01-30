#include<iostream>
#include "CircBuf.h"

using namespace std;

int main(){
    //Play around with copy and see how it works.

    CircBuf buff;
    

    buff.insert("ONE", 3);
    buff.get(2);
    cout << buff.examine() << endl;

    buff.insert("TWO");
    cout << buff.examine() << endl;

    buff.get();
    buff.insert("THREE");
    cout << buff.examine() << endl;
    
    return 0;
}