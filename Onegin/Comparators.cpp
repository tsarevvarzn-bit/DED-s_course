int compareAlphabetLeft (const void* a, const void* b);
int compareAlphabetRight(const void* a, const void* b);



int compareAlphabetLeft(const void * a, const void * b){

    assert(a);
    assert(b);

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

int compareAlphabetRight(const void* a, const void* b){

    assert(a);
    assert(b);

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
