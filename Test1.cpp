#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int    myStrcmp(const char *str1, const char *str2);
size_t myStrlen(const char* str);
size_t myStrnlen(const char* str, size_t strsz);
char*  myStrcpy(char* dest, const char* src);
char*  myStrcat(char* dest, const char* src);
char*  myStrdup(const char* str1);
int    myPuts(const char* str);
char*  myStrchr(char* str, int ch);
char*  myStrrchr(char* str, int ch);




int main(){

    char s1[100] = "ABOBA1";
    char s2[] = "Aboba2";
    char s3[50] = "RTRTRTRT3";

    //char prikol[0] = {};

    printf("s1, s2, s3:\n");
    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%s\n\n", s3);


    printf("1.myStrcmp\n");
    printf("Output of myStrcmp(s1, s2): %d, of orig strcmp: %d\n", myStrcmp(s1, s2), strcmp(s1, s2));

    printf("2.myStrlen\n");
    printf("Length of s1: %llu\n", myStrlen(s1));

    printf("3.myStrnlen\n");
    printf("Length of s1, strz = 3: %llu\n", myStrnlen(s1, 3));

    printf("4.myStrcpy\n");
    myStrcpy(s3, s2);
    printf("s2 copy in s3: ");
    printf("%s\n", s3);

    printf("5.myStrcat\n");
    printf("s1 + s2: ");
    myStrcat(s1, s2);
    printf("%s\n", s1);

    printf("6.myStrdup\n");
    printf("duplicate s2 in s4: ");
    char* s4 = myStrdup(s2);
    printf("%s\n", s4);

    printf("7.myPuts\n");
    printf("s1: ");
    myPuts(s1);

    printf("8.myStrchr\n");
    printf("first 'R' in s3: ");
    char* s5 = myStrchr(s3, 'R');
    if(s5 == NULL){
        printf("There is no 'R' in s3\n");
    }else{
        puts(s5);
    }

    printf("9.myStrrchr\n");
    printf("last 'R' in s3: ");
    char* s6 = myStrchr(s3, 'R');
    if(s5 == NULL){
        printf("There is no 'R' in s3\n");
    }else{
        puts(s6);
    }


    printf("s1, s2, s3:\n");
    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%s\n\n", s3);
}

size_t myStrlen(const char* str){

    if(str == NULL)
        return 0;

    int i = 0;

    while(str[i] != '\0'){
        i++;
    }

    return i;
}

size_t myStrnlen(const char* str, size_t strsz){

    if(str == NULL)
        return 0;

    size_t i = 0;

    while(str[i] != '\0'){
        if(i + 1 == strsz){
            return strsz;
        }
        i++;
    }

    return i;
}

int myPuts(const char* str){

    for(int i = 0; str[i] != '\0'; i++){
        if(putchar(str[i]) == EOF)
            return EOF;
    }

    if(putchar('\n') == EOF)
        return EOF;

    return 1;
}

char* myStrcpy(char* dest, const char* src){

    int i = 0;

    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';

    return dest;
}

char* myStrcat(char* dest, const char* src){

    int i = 0;
    int j = 0;

    while(dest[i] != '\0'){
        i++;
    }

    while(src[j] != '\0'){
        dest[i] = src[j];
        i++;
        j++;
    }

    dest[i] = '\0';

    return dest;
}

char* myStrdup(const char* str1){

    if(str1 == NULL)
        return NULL;

    int len = 0;

    while(str1[len] != '\0'){
        len++;
    }

    char* str1_copy = (char*) calloc(len + 1, sizeof(char));

    if(str1_copy == NULL){
        return NULL;
    }

    int i = 0;

    while(str1[i] != '\0'){
        str1_copy[i] = str1[i];
        i++;
    }

    str1_copy[i] = '\0';

    return str1_copy;
}

int myStrcmp(const char *str1, const char *str2){

    for(int i = 0; 1; i++){

        if(str1[i] < str2[i]){
            return -1;

        }else if(str1[i] > str2[i]){
            return 1;

        }else if(str1[i] == '\0'){
            return 0;

        }
    }
}

char*  myStrchr(char* str, int ch){

    char ch_ch = (char) ch;

    int i = 0;

    do{
        if(ch_ch == str[i]){
            return (char*) str + i;
        }
        i++;

    }while(str[i] != '\0');

    return NULL;
}

char*  myStrrchr(char* str, int ch){

    char ch_ch = (char) ch;

    int i = 0;

    int idx_of_ch = -1;

    do{
        if(ch_ch == str[i]){
            idx_of_ch = i;
        }
        i++;

    }while(str[i] != '\0');

    if(idx_of_ch == -1){
        return NULL;
    }else{
        return str + idx_of_ch;
    }
}
