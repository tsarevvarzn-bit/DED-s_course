smartString* getStringsFromFile(  const char* const file_name, unsigned int* const num_of_lines_read_p);

size_t       getSizeOfFile(       FILE* file);

void         printArray(          FILE* out, const smartString* const index, const unsigned int num_of_lines);
void         printText(           FILE* out, const char* const text, const unsigned int number_of_lines);
void         printSeparator(      FILE* out);


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

void printSeparator(FILE* out){

    assert(out);
    fprintf(out, "\n\n\n########################################################################################################################\n\n\n\n");
}
