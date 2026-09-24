#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(){

    printf("%d ", errno);
    puts(strerror(errno));
    putchar('\n');

    FILE* file =fopen("FF.llsa", "rb");

    printf("%d ", errno);
    puts(strerror(errno));
    putchar('\n');

    fprintf(file, "52");

    printf("%d ", errno);
    puts(strerror(errno));
    putchar('\n');
}
