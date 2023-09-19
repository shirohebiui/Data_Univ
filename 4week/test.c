#include <stdio.h>

int factorial(int n) {
    if(n) {
        return n * factorial(n-1);
    }
    return 1;
}

int power(int x, int n) {
    if(n%2 == 0 ) {
        return power(x*x, n/2);
    }
    if(n > 1) {
        return x * power(x, n-1);
    } else {
        return x;
    }
}

int main() {
    printf("%d\n", factorial(5));
    printf("%d\n", power(2, 8));
    return 0;
}