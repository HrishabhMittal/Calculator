#include "eval.cpp"

int main() {
    string s;
    getline(cin,s);
    double d;
    if (evalExpression(s,d)) cout << d << endl;
    else cout << "invalid" << endl;
}