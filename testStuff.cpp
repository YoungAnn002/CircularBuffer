#include<iostream>
#include "CircBuf.h"

using namespace std;

int main(){
    //Play around with copy and see how it works.

    CircBuf buff;
    

    // buff.insert("ONE", 3);
    // buff.get(2);
    // cout << buff.examine() << endl;

    // buff.insert("TWO");
    // cout << buff.examine() << endl;

    // buff.get();
    // buff.insert("THREE");
    // cout << buff.examine() << endl;
    
    // buff.get(3);
    // cout << buff.examine() << endl;

    // buff.insert("FOUR", 4);
    // cout << buff.examine() << endl;

    // string threefour = buff.get(10);
    // cout << threefour << endl;

    // buff.insert("hello");
    // cout << buff.examine() << endl;
    // buff.shrink();
    // cout << buff.examine() << endl;

    buff.insert("The Quick Brown Fox Jumped Over the Lazy Poodle");
    cout << buff.examine() << endl;
    

    
    return 0;
}