#include <stdio.h>
#include <string.h>
#include "ans.h"

#define TXT 1024
#define WORD 30

int main(){

char word[WORD+1] = {0};
char *p_word = word;
char txt[TXT+1] = {0};
char *p_txt = txt;

scanf("%s",word);
int index = 0;
char c;
while(index < TXT){
    scanf("%c",&c);
    if (c == '~') {
        break;
    }
    else {
        txt[index] = c;
        index++;
    }
}

Gematria(p_word,p_txt,strlen(word),strlen(txt));
Atbash(p_word,p_txt,strlen(word),strlen(txt));
Anagram(p_word,p_txt,strlen(word),strlen(txt));

}