#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/stat.h>

int main(){

    FILE* file = fopen("Onegin_text.txt", "rb");
    int descriptor = fileno(file);
    struct stat file_stats = {};
    fstat(descriptor, &file_stats);

    printf("Size: %lu", file_stats.st_size);
    char* text = (char*) calloc(file_stats.st_size, sizeof(char)); //Выделяем память непосредственно под текст

    fread((void*) text, sizeof(char), file_stats.st_size, file);

    for(int i = 0; i < 1000; i++){

        printf("%d\n", text[i]);
    }
}
