#include "Common.h"
#include "Secure_shells.cpp"
#include "Input_output.cpp"
#include "Sort.cpp"
#include "Comparators.cpp"


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
