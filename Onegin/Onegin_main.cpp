#include "Common.h"
#include "Secure_shells.cpp"
#include "Input_output.cpp"
#include "Sort.cpp"
#include "Comparators.cpp"


int main(const int argc, char* const * argv){

    char* in_file_name = NULL;
    char* out_file_name = NULL;
    processCMDArguments(argc, argv, &in_file_name, &out_file_name);
    textData text_data = getStringsFromFile(in_file_name);
    FILE*  out = safeOpen(out_file_name, "w");

    qsort((void*) text_data.index, (size_t) text_data.num_of_lines, sizeof(smartString), compareAlphabetLeft);
    printArray(out, text_data);
    printSeparator(out);

    myQSort((void*) text_data.index, text_data.num_of_lines, sizeof(smartString), compareAlphabetRight);
    printArray(out, text_data);
    printSeparator(out);

    printText(out, text_data);

    printf("All sorting is completed and printed in file\n");
    freeTextData(text_data);
    fclose(out);
}
