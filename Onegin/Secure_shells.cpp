void* safeCalloc(          const size_t number_of_elements, const size_t size_of_element);
void* safeRealloc(         void* const old_pointer, const size_t new_size);
FILE* safeOpen(            const char* file_name, const char* mode);



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
