#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define DEFAULT "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define VIOLET  "\033[1;35m"
#define CYAN    "\033[1;36m"

const unsigned int MIN_INDEX_SIZE = 1000;
const unsigned int MAX_STR_LEN = 10000;

struct smartString {
    char*        str;
    unsigned int len;
};

smartString* getStringsFromFile(  const char* const file_name, unsigned int* const num_of_lines_read_p);
size_t       getSizeOfFile(       FILE* file);
void         printArray(          FILE* out, const smartString* const index, const unsigned int num_of_lines);
void         printText(           FILE* out, const char* const text, const unsigned int number_of_lines);

void*        safeCalloc(          const size_t number_of_elements, const size_t size_of_element);
void*        safeRealloc(         void* const old_pointer, const size_t new_size);
FILE*        safeOpen(            const char* file_name, const char* mode);


void         myQSort(             void* const        array_void,
                                  const unsigned int number_of_elements,
                                  const unsigned int size_of_elem,
                                  int (*             compare)(const void* a, const void* b));

void         trivialSort(         void* const        array_void,
                                  const unsigned int number_of_elements,
                                  const unsigned int size_of_elem,
                                  int (*             compare)(const void* a, const void* b));

void         swap                (char* const a, char* const b, const unsigned int size_of_elem);

int          compareAlphabetLeft (const void* a, const void* b);
int          compareAlphabetRight(const void* a, const void* b);

void         printSeparator(      FILE* out);



int main(){

    unsigned int number_of_lines = 0;
    smartString* index = getStringsFromFile("Onegin_text.txt", &number_of_lines);
    char*  text = index[0].str;
    FILE*  out = safeOpen("Onegin_sorted.txt", "w");

    qsort((void*) index, (size_t) number_of_lines, sizeof(smartString), compareAlphabetLeft);
    printArray(out, index, number_of_lines);
    printSeparator(out);

    myQSort((void*) index, number_of_lines, sizeof(smartString), compareAlphabetRight);
    printArray(out, index, number_of_lines);
    printSeparator(out);

    printText(out, text, number_of_lines);
    printf("All sorting is completed and printed in file\n");

    free(text);
    free(index);
    fclose(out);

}

smartString* getStringsFromFile(const char* const file_name, unsigned int* const num_of_lines_read_p){

    assert(file_name);
    assert(num_of_lines_read_p);


    FILE* file = safeOpen(file_name, "rb");
    unsigned int num_of_characters_read = (unsigned int) getSizeOfFile(file);

    char* text = (char*) safeCalloc(num_of_characters_read, sizeof(char));
    fread((void*) text, sizeof(char), num_of_characters_read, file);

    smartString* index = (smartString*) safeCalloc(MIN_INDEX_SIZE, sizeof(smartString));
    index[0].str = text;
    *num_of_lines_read_p = 1;

    unsigned int index_size = MIN_INDEX_SIZE;
    unsigned int index_of_first_ch_in_str = 0;

    for(unsigned int i = 0; i < num_of_characters_read - 1; i++){

        if((*num_of_lines_read_p) >= index_size){

            printf("We need to reallocate memory for index: " YELLOW "%p" DEFAULT ", index size: %u, lines read: %u\n",
            index, index_size, *num_of_lines_read_p);

            index_size *= 2;
            index = (smartString*) safeRealloc(index, index_size * sizeof(smartString));

            printf("We reallocate memory for index:         " GREEN "%p" DEFAULT ", index size: %u, lines read: %u\n",
            index, index_size, *num_of_lines_read_p);
        }

        if(text[i] == '\n'){

            text[i - 1] = '\0'; //Перед ним стоит \r
            text[i] = '\0';

            index[*num_of_lines_read_p].str = text + i + 1;
            index[*num_of_lines_read_p - 1].len = i - index_of_first_ch_in_str - 1;

            index_of_first_ch_in_str = i + 1;

            (*num_of_lines_read_p)++;
        }
    }

    text[num_of_characters_read - 2] = '\0';
    text[num_of_characters_read - 1] = '\0';
    index[*num_of_lines_read_p - 1].len = num_of_characters_read - index_of_first_ch_in_str - 3;

    printf("File completely read, number of strings read: %u, first string: <%s>, len: %u, last string: <%s>, len: %u\n",
    *num_of_lines_read_p, index[0].str, index[0].len, index[*num_of_lines_read_p - 1].str, index[*num_of_lines_read_p - 1].len);

    fclose(file);

    return index;
}

size_t getSizeOfFile(FILE* file){

    assert(file);

    int descriptor = fileno(file);

    struct stat file_stats = {};

    fstat(descriptor, &file_stats);

    return file_stats.st_size;
}

void   printArray(FILE* out, const smartString* const index, const unsigned int num_of_lines){

    assert(index);

    fprintf(out, "Printing array with %u lines:\n", num_of_lines);

    for(unsigned int i = 0; i < num_of_lines; i++){

        assert(index[i].str);

        fprintf(out, "%u pointer: %p, len: %u <%s>\n", i + 1, index[i].str, index[i].len, index[i].str);
    }
}

void   printText(FILE* out, const char* const text, const unsigned int number_of_lines){

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

void*  safeCalloc(const size_t number_of_elements, const size_t size_of_element){

    void* pointer = calloc(number_of_elements, size_of_element);

    if(pointer == NULL){

        printf(RED "ERROR: calloc(number_of_elements, size_of_element), number of elements: %zu, size of one element: %zu, total: %zu, failed: %s" DEFAULT,
               number_of_elements, size_of_element, number_of_elements * size_of_element, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return pointer;
}

void*  safeRealloc(void* const old_pointer, const size_t new_size){

    assert(old_pointer);

    void* new_pointer = realloc(old_pointer, new_size);

    if(new_pointer == NULL){

        printf(RED "ERROR: realloc(old_pointer, new_size), old pointer: %p, new size %zu, failed: %s" DEFAULT,
               old_pointer, new_size, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return new_pointer;
}

FILE*  safeOpen(const char* const file_name, const char* const mode){

    assert(file_name);
    assert(mode);

    FILE* file_p = fopen(file_name, mode);

    if(file_p == NULL){

        printf(RED "ERROR: fopen(file_name, mode), name of the file: %s, mode: %s, failed: %s" DEFAULT,
        file_name, mode, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return file_p;
}

void   myQSort(void* const        array_void,
               const unsigned int number_of_elements,
               const unsigned int size_of_elem,
               int (*             compare)(const void* a, const void* b)){

    assert(array_void);
    assert(compare);

    char* array = (char*) array_void;

    if(number_of_elements <= 3){

        trivialSort(array_void, number_of_elements, size_of_elem, compare);
        return;
    }

    char* separating_element_p = array + (number_of_elements - 1) * size_of_elem;

    int left = 0;
    int right = number_of_elements - 2; //Индекс правого указателя, separating_element_p уже в нужной части массива

    bool is_bad_left = 0; //Элемент, на который указывает левый указатель, должен лежать справа
    bool is_bad_right = 0; //Элемент, на который указывает правый указатель, должен лежать слева

    while(left <= right){ //Ждем, когда они пройдут друг через друга, между ними будет линия разделения

        if(is_bad_left == 0){ //Если левый элемент не зафиксирован как большой

            if(compare((const void*) (array + left * size_of_elem), (const void*) separating_element_p) >= 0){ //Если левый элемент большой

                is_bad_left = 1;

            }else{

                left++;
            }


        }else if(is_bad_right == 0){ //Если правый элемент не зафиксирован как маленький

            if(compare((const void*) (array + right * size_of_elem), (const void*) (separating_element_p)) < 0){ //Если правый элемент маленький

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

    swap(array + (number_of_elements - 1) * size_of_elem, array + left * size_of_elem, size_of_elem); //Меняем самый маленький элемент >= separating_element с separating_element

    myQSort((void*) array,  right + 1, size_of_elem, compare); // Сортируем все до центрального separating_element
    myQSort((void*) (array + (left + 1) * size_of_elem), number_of_elements - (right + 1) - 1, size_of_elem, compare); //Сортируем все после центрального separating_element

}

void   trivialSort(void* const        array_void,
                   const unsigned int number_of_elements,
                   const unsigned int size_of_elem,
                   int (*             compare)(const void* a, const void* b)){

    assert(array_void);
    assert(compare);
    assert(number_of_elements <= 3);

    char* array = (char*) array_void;

    if(number_of_elements <= 1){

        return;

    }else if(number_of_elements == 2){

        if(compare((const void*) array, (const void*) (array + size_of_elem)) == 1)
            swap(array, array + size_of_elem, size_of_elem);

        return;

    }else{

        if(compare((const void*) array, (const void*) (array + size_of_elem)) == 1)
            swap(array, array + size_of_elem, size_of_elem);

        if(compare((const void*) (array + size_of_elem), (const void*) (array + 2 * size_of_elem)) == 1)
            swap(array + size_of_elem, array + 2 * size_of_elem, size_of_elem);

        if(compare((const void*) array, (const void*) (array + size_of_elem)) == 1)
            swap(array, array + size_of_elem, size_of_elem);

        return;

    }
}

void   swap(char* const a, char* const b, const unsigned int size_of_elem){

    assert(a);
    assert(b);

    for(unsigned int i = 0; i < size_of_elem; i++){

        char temp = *(a + i);
        *(a + i) = *(b + i);
        *(b + i) = temp;
    }

}

int    compareAlphabetLeft(const void * a, const void * b){

    assert(a);
    assert(b);

    //TODO - DONE проверять и строки
    const smartString smart_str1 = *((const smartString *) a);
    const smartString smart_str2 = *((const smartString *) b);

    const char * const str1 = smart_str1.str;
    const char * const str2 = smart_str2.str;

    assert(str1);
    assert(str2);

    unsigned int i = 0;
    unsigned int j = 0;

    while(i < smart_str1.len || j < smart_str2.len){

        if(!isalpha((int) str1[i]) && i < smart_str1.len){

            i++;

        }else if(!isalpha((int) str2[j]) && j < smart_str2.len){

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
    assert(b);//TODO - DONE ассерт на то, что указатель *a тоже не нулевой, что там есть строка

    const smartString smart_str1 = *((const smartString *) a);
    const smartString smart_str2 = *((const smartString *) b);

    const char * const str1 = smart_str1.str;
    const char * const str2 = smart_str2.str;

    int i = (int) smart_str1.len;
    int j = (int) smart_str2.len;

    assert(str1);
    assert(str2);

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

void printSeparator(FILE* out){

    assert(out);
    fprintf(out, "\n\n\n########################################################################################################################\n\n\n\n");
}
