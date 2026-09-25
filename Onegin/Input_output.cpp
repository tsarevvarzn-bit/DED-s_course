void         processCMDArguments(const int argc, char* const * argv, char** const name_from_p, char** const name_to_p);
textData     getStringsFromFile( const char* const file_name);
void         splitTextOnStrings( textData* text_data_p);

size_t       getSizeOfFile(      FILE* file);

void         printArray(         FILE* out, textData text_data);
void         printText(          FILE* out, textData text_data);
void         printSeparator(     FILE* out);



void         processCMDArguments(const int argc, char* const * argv, char** const name_from_p, char** const name_to_p){

    assert(argv);
    assert(name_from_p);
    assert(name_to_p);

    int getopt_out = 0;

    while ((getopt_out = getopt(argc, argv, "f:t:")) != -1)
    {
        switch (getopt_out)
        {
            case 'f':
                *name_from_p = optarg;
                break;

            case 't':
                *name_to_p = optarg;
                break;

            default:
                break;
        }
    }

    if(*name_from_p == NULL || *name_to_p == NULL){

        printf(RED "ERROR: please, enter correct CMD arguments: -f name_of_input_file.txt -t name_of_output_file.txt\n" DEFAULT);
        exit(EXIT_FAILURE);
    }

}

textData getStringsFromFile(const char* const file_name){

    assert(file_name);

    textData text_data = {};

    FILE* file = safeOpen(file_name, "rb");
    text_data.num_of_characters = (unsigned int) getSizeOfFile(file);

    text_data.text = (char*) safeCalloc(text_data.num_of_characters, sizeof(char));
    fread((void*) text_data.text, sizeof(char), text_data.num_of_characters, file);

    text_data.index = (smartString*) safeCalloc(MIN_INDEX_SIZE, sizeof(smartString));

    splitTextOnStrings(&text_data);

    printf("File completely read, number of strings read: %u, first string: <%s>, len: %u, last string: <%s>, len: %u\n",
    text_data.num_of_lines,
    text_data.index[0].str,
    text_data.index[0].len,
    text_data.index[text_data.num_of_lines - 1].str,
    text_data.index[text_data.num_of_lines - 1].len);

    fclose(file);

    return text_data;
}

size_t getSizeOfFile(FILE* file){

    assert(file);

    int descriptor = fileno(file);

    struct stat file_stats = {};

    fstat(descriptor, &file_stats);

    return file_stats.st_size;
}

void   printArray(FILE* out, textData text_data){

    assert(out);
    assert(text_data.index);

    fprintf(out, "Printing array with %u lines:\n", text_data.num_of_lines);

    for(unsigned int i = 0; i < text_data.num_of_lines; i++){

        assert(text_data.index[i].str);

        fprintf(out, "%u pointer: %p, len: %u <%s>\n", i + 1, text_data.index[i].str, text_data.index[i].len, text_data.index[i].str);
    }
}

void   printText(FILE* out, textData text_data){

    assert(out);
    assert(text_data.text);

    unsigned int i = 0;
    unsigned int number_of_printed_lines = 1;

    fprintf(out, "%u pointer: %p <%s>\n", number_of_printed_lines, text_data.text, text_data.text);

    while(number_of_printed_lines < text_data.num_of_lines){

        if(text_data.text[i] == '\0'){

            i += 2;

            number_of_printed_lines++;
            fprintf(out, "%u pointer: %p <%s>\n", number_of_printed_lines, text_data.text + i, text_data.text + i);

        }else{

            i++;
        }
    }
}

void printSeparator(FILE* out){

    assert(out);
    fprintf(out, "\n\n\n########################################################################################################################\n\n\n\n");
}

void splitTextOnStrings(textData* text_data_p){

    assert(text_data_p->index);
    assert(text_data_p->text);

    text_data_p->index[0].str = text_data_p->text;
    text_data_p->num_of_lines = 1;

    unsigned int index_size = MIN_INDEX_SIZE;
    unsigned int index_of_first_ch_in_str = 0;

    for(unsigned int i = 0; i < text_data_p->num_of_characters - 1; i++){

        if((text_data_p->num_of_lines) >= index_size){

            printf("We need to reallocate memory for index: " YELLOW "%p" DEFAULT ", index size: %u, lines read: %u\n",
            text_data_p->index, index_size, text_data_p->num_of_lines);

            index_size *= 2;
            text_data_p->index = (smartString*) safeRealloc(text_data_p->index, index_size * sizeof(smartString));

            printf("We reallocate memory for index:         " GREEN "%p" DEFAULT ", index size: %u, lines read: %u\n",
            text_data_p->index, index_size, text_data_p->num_of_lines);
        }

        if(text_data_p->text[i] == '\n'){

            text_data_p->text[i - 1] = '\0'; //Перед ним стоит \r
            text_data_p->text[i] = '\0';

            text_data_p->index[text_data_p->num_of_lines].str = text_data_p->text + i + 1;
            text_data_p->index[text_data_p->num_of_lines - 1].len = i - index_of_first_ch_in_str - 1;

            index_of_first_ch_in_str = i + 1;

            (text_data_p->num_of_lines)++;
        }
    }

    text_data_p->text[text_data_p->num_of_characters - 2] = '\0';
    text_data_p->text[text_data_p->num_of_characters - 1] = '\0';
    text_data_p->index[text_data_p->num_of_lines - 1].len = text_data_p->num_of_characters - index_of_first_ch_in_str - 3;

}

