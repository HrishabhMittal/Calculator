#include <iostream>
using namespace std;
#define PI 3.1415926
#define TWO_PI 2.0*PI
double rem(double i, double j) {
    if (i>0.0) {
        while (i>j) i-=j;
    } else {
        while (i<0.0) i+=j;
    }
    return i;
}
double pow(double x,int y) {
    double out=1.0;
    for (int i=0;i<y;i++) out*=x;
    return out;
}
double ln(double x) {
    if (x <= 0) {
        return 0;
    }
    double lnb=0.0;
    double term=(x-1)/(x+1);
    double termsq=term*term;
    double curterm=term;
    double factor=1.0;
    for (int i=1;i<1000;i+=2) {
        lnb+=curterm/i;
        curterm*=termsq;
    }
    lnb*=2;
    return lnb;
}
double pow(double base, double exponent) {
    if (base == 0.0) {
        return 0.0;
    }
    double lnb=ln(base);
    double result=1.0;
    double power=exponent*lnb;
    double factorial=1.0;
    double pterm= power;
    int n=1;
    while (n<100) {
        result+=pterm/factorial;
        n++;
        pterm*=power;
        factorial*=n;
    }
    return result;
}
double log(double x,double base) {
    // ln(x)=(x^h-1)/h when h->0
    return ln(x)/ln(base);
}
int factorial(int s) {
    int out=1;
    for (int i=1;i<=s;i++) {
        out*=i;
    }
    return out;
}
double sin(double x) {
    x=rem(x+PI,TWO_PI)-PI;
    double out=0.0;
    for (int i=0;i<5;i++) {
        if (i&1) out-=pow(x,2*i+1)/(double)(factorial(2*i+1));
        else out+=pow(x,2*i+1)/(double)(factorial(2*i+1));
    }
    return out;
}
double cos(double x) {
    x=rem(x+PI,TWO_PI)-PI;
    double out=0.0;
    for (int i=0;i<5;i++) {
        if (i&1) {
            out-=pow(x,2*i)/(double)(factorial(2*i));
        }
        else {
            out+=pow(x,2*i)/(double)(factorial(2*i));
        }
    }
    return out;
}