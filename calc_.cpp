#include <iostream>
using namespace std;

int sum_no(int a, int b);
int defgago(int a, int b);
int mult(int a, int b);
int divide(int a, int b);

int main(void) {
    int x, y;
    cout << "First Number: ";
    cin >> x;

    cout << "Second Number: ";
    cin >> y;

    int opt;
    cout << "Enter Option: ";
    cin >> opt;
    if(opt == 1) {
        cout << "Sum: " << sum_no(x, y) << "\n";
    }   else if (opt == 2) {
        cout << "Sub: " << defgago(x, y) << endl;
    }   else if (opt == 3) {
        cout << "Mult: " << mult(x, y) << endl;
    }   else if (opt == 4) {
        cout << "Divda: " << divide(x, y) << endl;
    }
}
int sum_no(int a, int b) {
    return a + b;
}
int defgago(int a, int b) {
    return a - b;
}
int mult(int a, int b) {
    return a * b;
}
int divide(int a, int b) {
    return a / b;
}