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
double fract(double d) {
    return d-(double)((long long)d);
}
double pow(double x,int y) {
    double out=1.0;
    for (int i=0;i<y;i++) out*=x;
    return out;
}
double pow(double x,double y) {
    double out=1.0;
    bool negative=false;
    if (y<0.0) {
        y*=-1.0;
        negative=true;
    }
    out=pow(x,((int)y));
    // using basic approximation
    if (y!=0.0) {
        y=fract(y);
        double lower=x>1.0?1.0:x;
        double upper=x<=1.0?1.0:x;
        double middle=(lower+upper)/2;
        double d=1.0;
        while (fract(y)>0.00001) {
            d*=10.0;
            y*=10.0;
        }
        double pp=pow(x,((int)y));
        while (upper-lower>0.000001) {
            middle=(lower+upper)/2;
            double ppp=pow(middle,((int)d));
            if (ppp>pp) {
                upper=middle;
            } else lower=middle;
        }
        out*=middle;
    }
    if (!negative) return out;
    else return 1/out;
}
double log(double x,double base) {
    // ln(x)=(x^h-1)/h when h->0
    return (pow(x,0.0005)-1)/(pow(base,0.0005)-1);
}
double ln(double x) {
    return (pow(x,0.00001)-1)/0.00001;
}
int factorial(int s) {
    int out=1;
    for (int i=1;i<=s;i++) {
        out*=i;
    }
    return out;
}
double sin(double x) {
    x=rem(x,TWO_PI);
    double out=0.0;
    for (int i=0;i<5;i++) {
        if (i&1) out-=pow(x,2*i+1)/(double)(factorial(2*i+1));
        else out+=pow(x,2*i+1)/(double)(factorial(2*i+1));
    }
    return out;
}
double cos(double x) {
    x=rem(x,TWO_PI);
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
