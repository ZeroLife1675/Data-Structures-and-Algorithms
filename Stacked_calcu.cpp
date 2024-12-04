#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    }
    return 0;
}

string infixToPostfix(string infix) {
    stack<char> operators;
    string postfix = "";
    for (int i = 0; i < infix.length(); i++) {
        if (isdigit(infix[i])) {
            while (i < infix.length() && isdigit(infix[i])) {
                postfix += infix[i];
                i++;
            }
            postfix += ' ';
            i--;
        }
        else if (infix[i] == '(') {
            operators.push(infix[i]);
        }
        else if (infix[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            operators.pop();
        }
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
            while (!operators.empty() && precedence(operators.top()) >= precedence(infix[i])) {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            operators.push(infix[i]);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        postfix += ' ';
        operators.pop();
    }

    return postfix;
}

int evaluatePostfix(string postfix) {
    stack<int> values;
    for (int i = 0; i < postfix.length(); i++) {
        if (isdigit(postfix[i])) {
            int num = 0;
            while (i < postfix.length() && isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            values.push(num);
        }

        else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
            int val2 = values.top();
            values.pop();
            int val1 = values.top();
            values.pop();
            values.push(applyOp(val1, val2, postfix[i]));
        }
    }

    return values.top();
}

int main() {
    string infix;
    cout << "Enter an arithmetic expression in infix notation (e.g., 3 + 5 - 2 * 3 / 2): ";
    getline(cin, infix);

    string postfix = infixToPostfix(infix);

    int result = evaluatePostfix(postfix);
    cout << "Result: " << result << endl;

    return 0;
}