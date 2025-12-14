#include <bits/stdc++.h>

using namespace std;

// e^x = 1 + x^1/1! + x^2 / 2! + ... + x^n / n!

float e(int x, int n) {
    static int den = 1;
    static int num = 1;
    if(n == 0)
        return 1.0;
    else {
        float nextlevel_retval = e(x, n-1);
        den = den*n;
        num *= x;
        return nextlevel_retval + (float)num / den;
    }
}

int main() {
    printf("%.4f", e(4, 10));
}