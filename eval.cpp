#include <string>
#include <vector>
#include "functions.cpp"
using namespace std;
vector<string> functions{
    "sin","cos","tan","log","ln"
};
double executefunction(string func,vector<double> arg) {
    if (func=="sin") return sin(arg[0]);
    else if (func=="cos") return cos(arg[0]);
    else if (func=="tan") return sin(arg[0])/cos(arg[0]);
    else if (func=="ln") return ln(arg[0]);
    else if (func=="log") return log(arg[0],arg[1]);
    else return 0.0;
}
int indexOf(vector<string> vec,string e) {
    for (int i=0;i<vec.size();i++) if (vec[i]==e) return i;
    return -1;
}
bool isAlpha(char i) {
    if ((i>='a' && i<='z')||(i>='A' && i<='Z')) return true;
    return false;
}
bool isAlpha(string i) {
    for (char a:i) {
        if (!isAlpha(a)) return false;
    }
    return true;
}
bool isNum(char i) {
    if (i>='0' && i<='9') return true;
    return false;
}
bool isValidSymbol(string a,string s="()+-/*^,") {
    if (a.size()!=1) return false;
    char x=a[0];
    for (char i:s) {
        if (x==i) return true;
    }
    return false;
}
bool isValidSymbol(char x,string s="()+-/*^,") {
    for (char i:s) {
        if (x==i) return true;
    }
    return false;
}
class Expr {
public:
    string s;
    int i;
    Expr(string s): s(s), i(0) {};
    string getNext() {
        if (i>=s.size()) return "";
        string out="";
        while (i<s.size() && s[i]==' ') i++;
        while (i<s.size() && (isNum(s[i])||s[i]=='.')) {
            out.push_back(s[i++]);
        }
        if (out!="") return out;
        while (i<s.size() && (isAlpha(s[i]))) {
            out.push_back(s[i++]);
        }
        if (out!="") return out;
        if (isValidSymbol(s[i])) {
            out.push_back(s[i++]);
        }
        return out;
    }
    vector<string> parseExpr() {
        vector<string> out={"("};
        int paren=1;
        while (!ended()) {
            string s=getNext();
            if (s!="") {
                out.push_back(s);
                if (s=="(") paren++;
                else if (s==")") paren--;
                if (paren<0) return {};
            }
            else return {};
        }
        out.push_back(")");
        return out;
    }
    bool ended() {
        return i>=s.size();
    }
};
int precedence(char i) {
    if (i=='+' || i=='-') return 0;
    else if (i=='/' || i=='*') return 1;
    else if (i=='^') return 2;
    else return 100;
}
bool getNum(string x,double& out) {
    double out1=0.0;
    double out2=1.0;
    bool dot=false;
    for (char i:x) {
        if (i=='.') {
            if (dot) return false;
            else dot=true;
        }
        else {
            if (!isNum(i)) return false;
            out1=out1*10.0+(double)((int)i-'0');
            if (dot) out2*=10.0;
        }
    }
    out=(out1/out2);
    return true;
}
double operate(double a,double b,string s) {
    switch (s[0]) {
        case '+': return a+b;
        case '-': return a-b;
        case '/': return a/b;
        case '*': return a*b;
        case '^': return pow(a,b);
    }
    return -1.0;
}
bool evalExpression(vector<string> in,double& out) {
    vector<string> stack;
    vector<double> vals;
    for (int i=0;i<in.size();i++) {
        string s=in[i];
        double num;
        if (isAlpha(s)) {
            //really bad way todo it but ok
            int j=indexOf(functions,s);
            if (j!=-1) {
                if (i+3<in.size()) {
                    if (in[i]!="log") {
                        if (in[i+1]=="(") {
                            string func=in[i];
                            i+=2;
                            vector<string> e{"("};
                            while (i<in.size() && in[i]!=")") e.push_back(in[i++]);
                            e.push_back(")");
                            if (i==in.size()) return false;
                            double arg;
                            if (!evalExpression(e,arg)) return false;
                            vals.push_back(executefunction(func,{arg}));
                        } else return false;
                    } else {
                        if (in[i+1]=="(") {
                            string func=in[i];
                            i+=2;
                            vector<string> e{"("};
                            while (i<in.size() && in[i]!=",") e.push_back(in[i++]);
                            e.push_back(")");
                            if (i==in.size()) return 0;
                            i++;
                            double arg;
                            if (!evalExpression(e,arg)) return false;
                            e={"("};
                            while (i<in.size() && in[i]!=")") e.push_back(in[i++]);
                            e.push_back(")");
                            if (i==in.size()) return 0;
                            double arg2;
                            if (!evalExpression(e,arg2)) return false;
                            vals.push_back(executefunction(func,{arg,arg2}));
                        } else return false;
                    }
                } else return false;
            } else return false;
        } else if (isValidSymbol(s)) {
            if (s=="(") {
                stack.push_back(s);
            } else if (s==")") {
                while (stack.back()!="(") {
                    string op=stack.back();
                    stack.pop_back();
                    if (vals.size()<2) return 0;
                    double result=operate(vals[vals.size()-2],vals[vals.size()-1],op);
                    vals.pop_back();
                    vals.back()=result;
                }
                stack.pop_back();
            } else {
                while (stack.back()!="(" && precedence(s[0])<=precedence(stack.back()[0])) {
                    string op=stack.back();
                    stack.pop_back();
                    if (vals.size()<2) return 0;
                    double result=operate(vals[vals.size()-2],vals[vals.size()-1],op);
                    vals.pop_back();
                    vals.back()=result;
                }
                stack.push_back(s);
            }
        } else if (getNum(s,num)) {
            vals.push_back(num);
        } else {
            return 0;
        }
    }
    out=vals.back();
    return 1;
}
bool evalExpression(string input,double& out) {
    Expr e{input};
    vector<string> in=e.parseExpr();
    return evalExpression(in,out);
}