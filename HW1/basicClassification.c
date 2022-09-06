#include <stdio.h>
#include "NumClass.h"

int isPrime(int x) {
    for (int i=2; i < x; i++) {
        if (x%i == 0) {
            return 0;
        }
    }
    return 1;
}

int isStrong(int x) {
    int ans=0;
    int currdigit;
    int temp;
    temp=x;
    while (temp>0) {
        int temp2 = 1;
        currdigit=temp%10;
        temp=temp/10;
        for (int i=1;i<=currdigit;i++) {
            temp2=temp2*i;
        }
        ans=ans+temp2;
    }
    if (ans==x) {
        return 1;
    } else {
        return 0;
    }
}

