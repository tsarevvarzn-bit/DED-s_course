#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DEFAULT "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define VIOLET  "\033[1;35m"
#define CYAN    "\033[1;36m"

void debugPrintTheArray(const char* const array, const int number_of_elements, const int elem_size, const int left, const int right, const int number_of_elements_before);
void sortTheArray(char* const array, const int size_of_elem, const int number_of_elements, int (* compare)(const char* a, const char* b), const int number_of_elements_before);
void swap(char* const a, char* const b, const int size_of_elem);
void defaultPrintTheArray(const char* const array, const int number_of_elements, const int elem_size);
void requestInputData(int* const elem_size_p, int* const number_of_elements_p,  int (**(compare_function_p_p))(const char* a, const char* b));
void enterElements(char* const array, const int elem_size, const int number_of_elements);

int  compareIntUp(const char* a, const char* b);
int  compareIntDown(const char* a, const char* b);
int  compareCharUp(const char* a, const char* b);
int  compareCharDown(const char* a, const char* b);

int main(){

    int elem_size = 0;
    int number_of_elements = 0;
    int (*compare_function_p)(const char* a, const char* b) = compareIntUp;

    requestInputData(&elem_size, &number_of_elements, &compare_function_p);

    char* array = (char*) calloc(number_of_elements, sizeof(char) * elem_size);

    enterElements(array, elem_size, number_of_elements);

    defaultPrintTheArray(array, number_of_elements, elem_size);

    sortTheArray((char*)array, elem_size, number_of_elements, compare_function_p, 0);

    defaultPrintTheArray(array, number_of_elements, elem_size);

    free(array);
}

void defaultPrintTheArray(const char* const array, const int number_of_elements, const int elem_size){

    assert(array);
    assert(elem_size == sizeof(char) || elem_size == sizeof(int));

    printf("Array:\n" CYAN );

    if(elem_size == sizeof(char)){

        for(int i = 0; i < number_of_elements; i++){

            printf("%-5c ", (int)*(array + i * sizeof(char)));
        }

    }else{

        for(int i = 0; i < number_of_elements; i++){

            printf("%-5d ", *(array + i * sizeof(int)));
        }
    }

    printf("\n" DEFAULT );

    for(int i = 0; i < number_of_elements; i++){

        if(elem_size == sizeof(char)){

            printf("%-5d " DEFAULT, i);

        }else{

            printf("%-5d " DEFAULT, i);
        }
    }

    printf("\n");
}

void debugPrintTheArray(
     const char* const array, const int number_of_elements, const int elem_size, const int left, const int right, const int number_of_elements_before){

    assert(array);
    assert(elem_size == sizeof(char) || elem_size == sizeof(int));

    printf(DEFAULT "Array:\n" CYAN );

    for(int i = 0; i < number_of_elements_before; i++){

        printf("      ");
    }

    for(int i = 0; i < number_of_elements; i++){

        if(i < left && i < right){
            printf(CYAN);

        }else if(i == left){
            printf(GREEN);

        }else if(i == right){
            printf(YELLOW);

        }else if(i > right && i > left){
            printf(RED);

        }else{
            printf(DEFAULT);
        }

        if(elem_size == sizeof(char)){

            printf("%-5c " DEFAULT, *(array + i));

        }else{

            printf("%-5d " DEFAULT, *(((const int*) array) + i));
        }

    }

    printf("\n");

    for(int i = 0; i < number_of_elements_before; i++){

        printf("      ");
    }

    for(int i = 0; i < number_of_elements; i++){

        if(elem_size == sizeof(char)){

            printf("%-5d " DEFAULT, i);

        }else{

            printf("%-5d " DEFAULT, i);
        }
    }

    getchar();

}

void sortTheArray(char* const array, const int size_of_elem, const int number_of_elements, int (* compare)(const char* a, const char* b), const int number_of_elements_before){

    assert(array);
    assert(number_of_elements >= 0);

    if(number_of_elements <= 1){

        return;

    }else if(number_of_elements == 2){

        if(compare(array, array + size_of_elem) == 1)
            swap(array, array + size_of_elem, size_of_elem);

        return;

    }else if(number_of_elements == 3){

        if(compare(array, array + size_of_elem) == 1)
            swap(array, array + size_of_elem, size_of_elem);

        if(compare(array + size_of_elem, array + 2 * size_of_elem) == 1)
            swap(array + size_of_elem, array + 2 * size_of_elem, size_of_elem);

        if(compare(array, array + size_of_elem) == 1)
            swap(array, array + size_of_elem, size_of_elem);

        return;

    }

    char* pivot = array + (number_of_elements - 1) * size_of_elem;
    int pivot_value = 0;

    if(size_of_elem == sizeof(char)){

        pivot_value = (int) *pivot;

    }else{

        pivot_value = *((int*) pivot);
    }

    int left = 0; //Индекс левого указателя
    int right = number_of_elements - 2; //Индекс правого указателя, pivot уже в нужной части массива

    int is_bad_left = 0; //Элемент, на который указывает левый указатель, должен лежать справа
    int is_bad_right = 0; //Элемент, на который указывает правый указатель, должен лежать слева

    while(left <= right){ //Ждем, когда они пройдут друг через друга, между ними будет линия разделения

        if(is_bad_left == 0){ //Если левый элемент не зафиксирован как большой

            if(compare(array + left * size_of_elem, pivot) >= 0){ //Если левый элемент большой

                is_bad_left = 1;

                printf("Find bad left, left = %d, right = %d, pivot = %d\n", left, right, pivot_value);
                debugPrintTheArray(array, number_of_elements, size_of_elem, left, right, number_of_elements_before);

            }else{ //Если левый элемент маленький

                left++;
            }


        }else if(is_bad_right == 0){ //Если правый элемент не зафиксирован как маленький

            if(compare(array + right * size_of_elem, pivot) < 0){ //Если правый элемент маленький

                is_bad_right = 1;

                printf("Find bad right, left = %d, right = %d, pivot = %d\n", left, right, pivot_value);
                debugPrintTheArray(array, number_of_elements, size_of_elem, left, right, number_of_elements_before);

            }else{

                right--;
            }

        }else if(is_bad_left == 1 && is_bad_right == 1 && left < right){

            swap(array + size_of_elem * left, array + size_of_elem * right, size_of_elem);

            printf("Swapped, left = %d, right = %d, pivot = %d\n", left, right, pivot_value);
            debugPrintTheArray(array, number_of_elements, size_of_elem, left, right, number_of_elements_before);

            is_bad_left = 0;
            is_bad_right = 0;

            left++;
            right--;
        }
    }

    swap(array + (number_of_elements - 1) * size_of_elem, array + left * size_of_elem, size_of_elem); //Меняем самый маленький элемент >= pivot с pivot

    printf(DEFAULT "\nThe array is partially sorted, left = %d, right = %d, pivot = %d\n", left, right, pivot_value);
    debugPrintTheArray(array, number_of_elements, size_of_elem, left, right, number_of_elements_before); //ТОЛЬКО ДЛЯ INT !!!


    sortTheArray(array, size_of_elem, right + 1, compare, number_of_elements_before); // Сортируем все до центрального pivot
    sortTheArray(array + (left + 1) * size_of_elem, size_of_elem, number_of_elements - (right + 1) - 1, compare, left + 1); //Сортируем все после центрального pivot

}

int compareIntUp(const char* a, const char* b){

    assert(a);
    assert(b);

    int a_int = *((const int*) a);
    int b_int = *((const int*) b);

    if(a_int > b_int)
        return 1;

    if(a_int < b_int)
        return -1;

    return 0;
}

int compareIntDown(const char* a, const char* b){

    assert(a);
    assert(b);

    int a_int = *((const int*) a);
    int b_int = *((const int*) b);

    if(a_int > b_int)
        return -1;

    if(a_int < b_int)
        return 1;

    return 0;
}

int compareCharUp(const char* a, const char* b){

    assert(a);
    assert(b);

    if(*a > *b)
        return 1;

    if(*a < *b)
        return -1;

    return 0;
}

int compareCharDown(const char* a, const char* b){

    assert(a);
    assert(b);

    if(*a > *b)
        return -1;

    if(*a < *b)
        return 1;

    return 0;
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

void requestInputData(int* const elem_size_p, int* const number_of_elements_p, int (**(compare_function_p_p))(const char* a, const char* b)){

    printf("Enter the number of elements: ");
    scanf("%d", number_of_elements_p);
    assert(*number_of_elements_p > 0);

    getchar();

    char direction_c = 0;
    char type_c = 0;

    printf("Do you want to sort the array in ascending or descending order? a/d: ");

    scanf("%c", &direction_c);
    assert(direction_c == 'a' || direction_c == 'd');

    getchar();

    printf("Do you want to sort char or int? c/i: ");
    scanf("%c", &type_c);
    assert(type_c == 'c' || type_c == 'i');

    getchar();

    *elem_size_p = sizeof(char);

    if(direction_c == 'a'){

        if(type_c == 'i'){

            *compare_function_p_p = compareIntUp;
            *elem_size_p = sizeof(int);

        }else{

            *compare_function_p_p = compareCharUp;
        }

    }else{

        if(type_c == 'i'){

            *compare_function_p_p = compareIntDown;
            *elem_size_p = sizeof(int);

        }else{

            *compare_function_p_p = compareCharDown;
        }
    }

}

void enterElements(char* const array, const int elem_size, const int number_of_elements){

    assert(array);
    assert(elem_size == sizeof(char) || elem_size == sizeof(int));
    assert(number_of_elements > 0);

    if(elem_size == sizeof(char)){

        for(int i = 0; i < number_of_elements; i++){

            printf("Enter %d element: ", i);
            scanf("%c", array + i * sizeof(char));
            getchar();
        }
    }else{

        for(int i = 0; i < number_of_elements; i++){

            printf("Enter %d element: ", i);
            scanf("%d", ((int*) array) + i);
        }
    }
    getchar();
}
