#include<iostream>

using namespace std;

int main(){

    string blah = "hello";

    cout << blah << endl;

    char* x = new char[8];

    int len = blah.length();

    for(int i = 0; i < len; i++){
        x[i] = blah[i];
    }
    x[len] = '\0';

    for(int i = 0; i < 7; i++){
        if(x[i] == '\0'){
            cout << '-' << endl;
        }
        cout << x[i] << endl;
    }

    return 0;
}