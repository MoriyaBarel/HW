#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include "ans.h"

#define TXT 1024
#define WORD 30

//calculate the gematria value of char
int gm(char ch){
    if(ch > 64 && ch < 91){
        return ch-64;
    }
    if(ch > 96 && ch < 123){
        return ch-96;
    }
    else{
        return 0;
    }
}

void Gematria(char *word,char *txt,int word_len,int txt_len){
    printf("Gematria Sequences: ");
    int i = 0;
    int word_sum = 0;
    while (i < word_len){
        word_sum += gm(word[i]);
        i++;
    }
    int avoid = 0; //using to avoid ~ printing in the beginning of the answar
    i = 0;
    while (i < txt_len){
        int txt_sum = 0;
        if(gm(txt[i]) != 0){
            int counter = 0;
            while ((i + counter) < txt_len && gm(txt[i + counter]) <= word_sum && txt_sum < word_sum) {
                txt_sum += gm((txt[i+counter]));
                counter++;
            }
            if(txt_sum == word_sum){
                if(avoid != 0){
                     printf("~");
                }
                avoid++;
                int temp = 0;
                while(temp < counter){
                    printf("%c",txt[i+temp]);
                    temp++;
                }
            }
        }
        i++;

    }
    printf("\n");  
} 

//converting char to atbash value 
char Atb(char ch) {
    char ans=ch;
    if (ch > 64 && ch < 91) {
        ans = (char)('A' + 'Z' - ch);
    }
    if (ch > 96 && ch < 123) {
        ans = (char)('a' + 'z' - ch);
    }
    return ans;
}

void Atbash(char *word,char *txt,int word_len,int txt_len){
    printf("Atbash Sequences: ");
    int avoid = 0; //using to avoid ~ printing in the beginning of the answar
    for (int i = 0; i < txt_len; i++) {
        char first_letter = Atb(word[0]);
        char last_letter = Atb(word[word_len-1]);
        if(txt[i] == first_letter){
            int counter = 1;
            int j = 1;
            while (i+counter < txt_len && j < word_len){
                if(txt[i+counter] == Atb(word[j])){
                    counter++;
                    j++;
                }
                else if(txt[i+counter] == ' '){
                    counter++;
                }
                else{
                    break;
                }
            }
            if (j == word_len){
                if(avoid != 0){
                    printf("~");
                }
                avoid++;
                int temp = 0;
                while(temp < counter){
                    printf("%c",txt[i+temp]);
                    temp++;
                }
            }
        } else if (txt[i] == last_letter) {
            int counter = 1;
            int j = word_len-2;
            while (i+counter < txt_len && j >= 0){
                if(txt[i+counter] == Atb(word[j])){
                    counter++;
                    j--;
                }
                else if(txt[i+counter] == ' '){
                    counter++;
                }
                else{
                    break;
                }
            }
            if (j == -1){
                if(avoid != 0){
                    printf("~");
                }
                avoid++;
                int temp = 0;
                while(temp < counter){
                    printf("%c",txt[i+temp]);
                    temp++;
                }
            }
        }
    }
    printf("\n");
}

//copying char array to another char array using calloc and strcpy
char* copyString(char s[], int len) {
    char* s2;
    s2 = (char*)calloc(len,sizeof(char));
 
    strcpy(s2, s);
    return (char*)s2;
}

//checking if char array contains a given char and if it contains replace the char in the array to tilda
int contains(char *copy ,char ch,int copy_len){
    for (int i = 0; i < copy_len ; i++){
        if (ch == copy[i]) {
            copy[i] = '~';
            return 1;
           }
    }
        return 0;
}

void Anagram(char *word,char *txt,int word_len,int txt_len){
    printf("Anagram Sequences: ");
    char * copy;
    int avoid = 0; //using to avoid ~ printing in the beginning of the answar
    for (int i = 0; i < txt_len; i++) {
        copy = copyString(word,word_len);
        if (contains(copy,txt[i],word_len)) {
            int counter = 1;
            int k = 1;
            int flag = 1; //update every time that contains func return 1(true)
            while (i + counter < txt_len && k < word_len) {
                if (txt[i + counter] == ' ') {
                    counter++;
                    continue;
                }
                if (contains(copy,txt[i+counter],word_len)) {
                    flag++;
                    counter++;
                }
                k++;
            }
            if (flag == word_len) {
                if (avoid != 0) {
                    printf("~");
                }
                avoid++;
                int temp = 0;
                while (temp < counter) {
                    printf("%c",txt[i + temp]);
                    temp++;
                }
            }
        }   
        free(copy); //free the memory of the copy array that storge with callc
    }
}