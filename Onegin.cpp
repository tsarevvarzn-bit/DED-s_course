#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#define DEFAULT "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define VIOLET  "\033[1;35m"
#define CYAN    "\033[1;36m"

const unsigned int MIN_INDEX_SIZE = 100;
const unsigned int MAX_STR_LEN = 10000;

void*  safeCalloc(const size_t number_of_elements, const size_t size_of_element);
void*  safeRealloc(void* const old_pointer, const size_t new_size);
FILE*  safeOpen(const char* file_name, const char* mode);

void   swap(char* const a, char* const b, const int size_of_elem);
void   myQSort(char* const        array,
               const unsigned int number_of_elements,
               const unsigned int size_of_elem,
               int (*             compare)(const void* a, const void* b));

char** getStringsFromFile(const char* const file_name, unsigned int* const num_of_lines_read_p, unsigned int* const num_of_characters_read_p);
void   printArray(FILE* out, const char* const * const index, const unsigned int num_of_lines);
void   printText(FILE* out, const char* const text, const unsigned int number_of_lines);

int    compareAlphabetLeft(const void* a, const void* b);
int    compareAlphabetRight(const void* a, const void* b);

int main(){

    unsigned int number_of_lines = 0;
    unsigned int num_of_characters_read = 0;

    char** index = getStringsFromFile("Onegin_text.txt", &number_of_lines, &num_of_characters_read);
    char* text = index[0];
    FILE* out = safeOpen("Onegin_sorted.txt", "w");

    qsort((void*) index, (size_t) number_of_lines, sizeof(char*), compareAlphabetLeft);
    printArray(out, index, number_of_lines);

    myQSort((char*) index, number_of_lines, sizeof(char*), compareAlphabetRight);
    fprintf(out, "\n\n\n########################################################################################################################\n\n\n\n");
    printArray(out, index, number_of_lines);

    fprintf(out, "\n\n\n########################################################################################################################\n\n\n\n");
    printText(out, text, number_of_lines);
    printf("All sorting is completed and printed in file\n");

    free(text);
    free(index);
}

char** getStringsFromFile(const char* const file_name, unsigned int* const num_of_lines_read_p, unsigned int* const num_of_characters_read_p){

    assert(file_name);
    assert(num_of_lines_read_p);
    assert(num_of_characters_read_p);

    FILE* file = safeOpen(file_name, "rb");
    int descriptor = fileno(file);
    struct stat file_stats = {};
    fstat(descriptor, &file_stats);
    *num_of_characters_read_p = file_stats.st_size;

    char* text = (char*) safeCalloc(*num_of_characters_read_p, sizeof(char)); //Выделяем память непосредственно под текст
    fread((void*) text, sizeof(char), *num_of_characters_read_p, file);

    unsigned int index_size = MIN_INDEX_SIZE;
    *num_of_lines_read_p = 0;

    char** index = (char**) safeCalloc(index_size, sizeof(char*)); //Дает указатель на массив указателей на char
    index[*num_of_lines_read_p] = text;
    (*num_of_lines_read_p)++;

    for(unsigned int i = 0; i < *num_of_characters_read_p - 1; i++){// Не проверяем последний символ \n

        if((*num_of_lines_read_p) >= index_size){

            printf("We need to reallocate memory for index: " YELLOW "%p" DEFAULT ", index size: %u, lines read: %u\n", index, index_size, *num_of_lines_read_p);

            index_size *= 2;
            index = (char**) safeRealloc(index, index_size * sizeof(char*));

            printf("We reallocate memory for index:         " GREEN "%p" DEFAULT ", index size: %u, lines read: %u\n", index, index_size, *num_of_lines_read_p);
        }

        if(text[i] == '\n'){

            text[i - 1] = '\0';
            text[i] = '\0';

            index[*num_of_lines_read_p] = text + i + 1;

            //printf("Read %u line, <%s>\n", *num_of_lines_read_p, index[*num_of_lines_read_p - 1]);

            (*num_of_lines_read_p)++;
        }
    }

    text[*num_of_characters_read_p - 2] = '\0';
    text[*num_of_characters_read_p - 1] = '\0';

    //printf("Read %u line, <%s>\n", *num_of_lines_read_p, index[*num_of_lines_read_p - 1]);

    printf("File completely read, number of strings read: %u, first string: <%s>, last string: <%s>\n", *num_of_lines_read_p, index[0], index[*num_of_lines_read_p - 1]);

    return index;
}

void   printArray(FILE* out, const char* const * const index, const unsigned int num_of_lines){

    assert(index);
    assert(*index);

    fprintf(out, "Printing array with %u lines:\n", num_of_lines);

    for(unsigned int i = 0; i < num_of_lines; i++){

        fprintf(out, "%u pointer: %p <%s>\n", i + 1, index[i], index[i]);
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

void*  safeRealloc(void* const old_pointer, const size_t new_size){

    void* new_pointer = realloc(old_pointer, new_size);

    if(new_pointer == NULL){

        printf(RED "ERROR: realloc can't allocate enough memory, old pointer: %p, new pointer: %p, new size %zu" DEFAULT, old_pointer, new_pointer, new_size);
        exit(1);
    }

    return new_pointer;
}

FILE*  safeOpen(const char* const file_name, const char* const mode){

    assert(file_name);
    assert(mode);

    FILE* file_p = fopen(file_name, mode);

    if(file_p == NULL){

        printf(RED "ERROR: fopen can't open file, name of the file: %s, mode: %s" DEFAULT, file_name, mode);
        exit(1);
    }

    return file_p;
}

int    compareAlphabetLeft(const void * a, const void * b){

    const char* str1 = *((const char * const* ) a);
    const char* str2 = *((const char * const* ) b);

    unsigned int i = 0;
    unsigned int j = 0;

    while(i <= MAX_STR_LEN && j <= MAX_STR_LEN){

        if(!isalpha((int) str1[i]) && str1[i] != '\0'){

            i++;

        }else if(!isalpha((int) str2[j]) && str2[j] != '\0'){

            j++;

        }else{

            if(tolower(str1[i]) < tolower(str2[j])){

                return -1;

            }else if(tolower(str1[i]) > tolower(str2[j])){

                return 1;

            }else if(str1[i] == '\0'){

                return 0;
            }

            i++;
            j++;
        }
    }

    return 0;
}

int    compareAlphabetRight(const void* a, const void* b){

    assert(a);
    assert(b);

    const char* str1 = *((const char* const* ) a);
    const char* str2 = *((const char* const* ) b);

    int i = (int) strnlen(str1, MAX_STR_LEN);
    int j = (int) strnlen(str2, MAX_STR_LEN);

    if(i == j && i == 0)
        return 0;

    if(i == 0)
        return -1;

    if(j == 0)
        return 1;

    i--;
    j--;

    while(i >= 0 && j >= 0){

        if(!isalpha((int) str1[i]) && str1[i] != '\0'){

            i--;

        }else if(!isalpha((int) str2[j]) && str2[j] != '\0'){

            j--;

        }else{

            if(tolower(str1[i]) < tolower(str2[j])){

                return -1;

            }else if(tolower(str1[i]) > tolower(str2[j])){

                return 1;

            }else if(str1[i] == '\0'){

                return 0;
            }

            i--;
            j--;
        }
    }

    return 0;
}

void myQSort(char* const        array,
             const unsigned int number_of_elements,
             const unsigned int size_of_elem,
             int (*             compare)(const void* a, const void* b)){ //TODO void*

    assert(array);

    if(number_of_elements <= 1){

        return;

    }else if(number_of_elements == 2){

        if(compare((const void*) array, (const void*) (array + size_of_elem)) == 1)
            swap(array, array + size_of_elem, size_of_elem);

        return;

    }else if(number_of_elements == 3){

        if(compare((const void*) array, (const void*) (array + size_of_elem)) == 1)
            swap(array, array + size_of_elem, size_of_elem);

        if(compare((const void*) (array + size_of_elem), (const void*) (array + 2 * size_of_elem)) == 1)
            swap(array + size_of_elem, array + 2 * size_of_elem, size_of_elem);

        if(compare((const void*) array, (const void*) (array + size_of_elem)) == 1)
            swap(array, array + size_of_elem, size_of_elem);

        return;

    }

    char* pivot = array + (number_of_elements - 1) * size_of_elem;

    int left = 0; //Индекс левого указателя
    int right = number_of_elements - 2; //Индекс правого указателя, pivot уже в нужной части массива

    int is_bad_left = 0; //Элемент, на который указывает левый указатель, должен лежать справа
    int is_bad_right = 0; //Элемент, на который указывает правый указатель, должен лежать слева

    while(left <= right){ //Ждем, когда они пройдут друг через друга, между ними будет линия разделения

        if(is_bad_left == 0){ //Если левый элемент не зафиксирован как большой

            if(compare((const void*) (array + left * size_of_elem), (const void*) pivot) >= 0){ //Если левый элемент большой

                is_bad_left = 1;

            }else{ //Если левый элемент маленький

                left++;
            }


        }else if(is_bad_right == 0){ //Если правый элемент не зафиксирован как маленький

            if(compare((const void*) (array + right * size_of_elem), (const void*) (pivot)) < 0){ //Если правый элемент маленький

                is_bad_right = 1;

            }else{

                right--;
            }

        }else if(is_bad_left == 1 && is_bad_right == 1 && left < right){

            swap(array + size_of_elem * left, array + size_of_elem * right, size_of_elem);

            is_bad_left = 0;
            is_bad_right = 0;

            left++;
            right--;
        }
    }

    swap(array + (number_of_elements - 1) * size_of_elem, array + left * size_of_elem, size_of_elem); //Меняем самый маленький элемент >= pivot с pivot


    myQSort(array,  right + 1, size_of_elem, compare); // Сортируем все до центрального pivot
    myQSort(array + (left + 1) * size_of_elem, number_of_elements - (right + 1) - 1, size_of_elem, compare); //Сортируем все после центрального pivot

}

void swap(char* const a, char* const b, const int size_of_elem){

    assert(a);
    assert(b);
    assert(size_of_elem > 0);

    for(int i = 0; i < size_of_elem; i++){

        char temp = *(a + i);
        *(a + i) = *(b + i);
        *(b + i) = temp;
    }

}

void printText(FILE* out, const char* const text, const unsigned int number_of_lines){

    assert(out);
    assert(text);

    unsigned int i = 0;
    unsigned int number_of_printed_lines = 1;

    fprintf(out, "%u pointer: %p <%s>\n", number_of_printed_lines, text, text);

    while(number_of_printed_lines < number_of_lines){

        if(text[i] == '\0'){

            i += 2;

            number_of_printed_lines++;
            fprintf(out, "%u pointer: %p <%s>\n", number_of_printed_lines, text + i, text + i);

        }else{

            i++;
        }
    }
}
