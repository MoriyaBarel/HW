#include <stdio.h>
#include "NumClass.h"

int Power(int num, int Pow) {
    int ans=1;
    for (int i=0;i<Pow;i++) {
        ans=ans*num;
    }
    return ans;
}

int isArmstrong(int x) {
    int ans=0;
    int counter=0;
    int temp=x;
    while (temp>0) {
        temp=temp/10;
        counter++;
    }
    temp=x;
    int currdigit;
    while (temp>0) {
        currdigit=temp%10;
        temp=temp/10;
        ans=ans+Power(currdigit, counter);
    }
    if (ans==x) {
        return 1;
    } else {
        return 0;
    }
}

int isPalindrome(int x) {
    int counter=0;
    int temp=x;
    while (temp>0) {
        temp=temp/10;
        counter++;
    }
    temp=x;
    int arr[counter];
    for (int i=0; i<counter; i++) {
        arr[i]=temp%10;
        temp=temp/10;
    }
    int i=0;
    while (i<counter/2) {
        if (arr[i]!=arr[counter-1-i]) {
            return 0;
        }
        i++;
    }
    return 1;
}