#include <iostream>
using namespace std;



int main() {
    int a[10];
    a[0] = 17;
    a[9] = 29;
   // cout << a << endl;
    for (int i = 1; i < sizeof(a) - 1; i++) {
        a[i] = -1;
    }

   // cout << a << endl;

    for (int i = 0; i < sizeof(a); i++) {
        a[i]++;
    }
   // cout << a << endl;

    for (int b : a) {
        cout << b << endl;
    }
    for (int i = 0; i < sizeof(a); i++) {
        cout << a[i] << ", ";
    }

    return 0;


}