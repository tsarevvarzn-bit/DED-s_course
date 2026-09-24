void myQSort(    void* const        array_void,
                 const unsigned int number_of_elements,
                 const unsigned int size_of_elem,
                 int (*             compare)(const void* a, const void* b));

void trivialSort(void* const        array_void,
                 const unsigned int number_of_elements,
                 const unsigned int size_of_elem,
                 int (*             compare)(const void* a, const void* b));

void swap       (char* const a, char* const b, const unsigned int size_of_elem);



void myQSort(    void* const        array_void,
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
