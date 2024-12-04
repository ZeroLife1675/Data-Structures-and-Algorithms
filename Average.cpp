#include <iostream>

using namespace std;

int main() {

    float exam1, exam2, exam3;
    float average;
    const float passingGrade = 70.0;
    cout << "Enter the score for exam 1: ";
    cin >> exam1;
    cout << "Enter the score for exam 2: ";
    cin >> exam2;
    cout << "Enter the score for exam 3: ";
    cin >> exam3;

    average = (exam1 + exam2 + exam3) / 3;
    cout << "Average score: " << average << endl;

    if (average >= passingGrade) {
        cout << "Result passed." << endl;
    } else {
        cout << "Result failed." << endl;
    }

    return 0;
}
