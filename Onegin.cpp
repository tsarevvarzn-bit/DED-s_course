#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define DEFAULT "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define VIOLET  "\033[1;35m"
#define CYAN    "\033[1;36m"

const unsigned int BUFFER_SIZE = 10000;
const unsigned int BUFFER_SIZE = 10000;

void*  safeCalloc(const size_t number_of_elements, const size_t size_of_element);
FILE*  safeOpen(const char* file_name, const char* mode);

char** getStringsFromFile(const char* file_name);

int main(){

    FILE* = fopen("Onegin_orig.txt", "r");

}

char** getStringsFromFile(const char* file_name){

    assert(file_name);

    FILE* file = safeOpen(file_name, "r");

    char* buffer = (char*) safeCalloc(BUFFER_SIZE, sizeof(char));

    unsigned int array_size = BUFFER_SIZE;
    unsigned int num_of_lines_read = 0;

    char** array = (char**) safeCalloc(array_size, sizeof(char*)); //Дает указатель на массив указателей на char

    while(fgets(buffer, BUFFER_SIZE, file)){

        if(num_of_lines_read >= array_size){

            array = realloc((void*) array, array_size * 2); //Расширяем память по массив указателей на строки
        }
    }

}

void*  safeCalloc(const size_t number_of_elements, const size_t size_of_element){

    void* pointer = calloc(number_of_elements, size_of_element);

    if(pointer == NULL){

        printf(RED "ERROR: calloc can't allocate enough memory, number of elements: %zu, size of one element: %zu, total: %zu" DEFAULT,
               number_of_elements, size_of_element, number_of_elements * size_of_element);
        exit(1);
    }

    return pointer;
}

void* safeRealloc(void* old_pointer, const size_t new_size){

    void* new_pointer = realloc(pointer, new_size);

    if(pointer == NULL){

        printf(RED "ERROR: realloc can't allocate enough memory, old pointer: %p, new size %zu" DEFAULT, old_pointer, new_size);
        exit(1);
    }

    return pointer;
}

FILE*  safeOpen(const char* file_name, const char* mode){

    assert(file_name);
    assert(mode);

    FILE* file_p = fopen(file_name, mode);

    if(file_p == NULL){

        printf(RED "ERROR: fopen can't open file, name of the file: %s, mode: %s" DEFAULT, file_name, mode);
        exit(1);
    }

    return file_p;
}
