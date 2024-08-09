#include "eval.cpp"
// couldnt really get a neat way todo this so ig this works for now
void solvequad() {
    double a,b,c;
    cout << "solving quadratic ax^2+bx+c\nenter a:" <<endl;
    cin>>a;
    cout << "enter b:";
    cin>>b;
    cout<<"enter c:";
    cin>>c;
    double d=b*b-4*a*c;
    if (d>0) {
        cout << "solutions are ";
        cout << (-b+pow(d,0.5))/(2.0*a) << ", ";
        cout << (-b-pow(d,0.5))/(2.0*a);
    } else if (d==0) {
        cout << "solution is ";
        cout << -0.5*b/a;
    } else cout << "no solution";
    cout << endl;
}