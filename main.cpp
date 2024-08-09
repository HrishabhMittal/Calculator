#include "eval.cpp"

int main() {
    string s;
    while (true) {
        cout << ">>";
        getline(cin,s);
        if (s=="exit") break;
        double d;
        if (evalExpression(s,d)) cout << ">>" << d << endl;
        else cout << "invalid expression" << endl;
    }
}