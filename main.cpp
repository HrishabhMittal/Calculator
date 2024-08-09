#include "quadratic.cpp"
void calculate() {
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
int main() {
    string s;
    while (true) {
        cout << "commands\n 1.> calculate => do some simple math\n 2.> quaratic => solve a quaratic" << endl;
        getline(cin,s);
        if (s=="exit") break;
        else if (s=="calculate") calculate();
        else if (s=="quadratic") {
            char c='y';
            while (c=='y') {
                solvequad();
                cout << "continue?(y/n)";
                cin>>c;
            }
        } else {
            cout << "unrecognised command";
        }
    }
}