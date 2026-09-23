# Евгений Онегин

А. С. Пушкин так хорошо описал быт и нравы современной ему жизни в поэме «Евгений Онегин», что её часто называют «энциклопедией русской жизни того времени». 
Но в энциклопедии всё должно быть отсортировано по алфавиту — а Пушкин, будучи гуманитарием, этого не сделал, поможем ему, отсортировав строки его произведения.

## Что делает
Программа считывает текст произведения из файла Onegin_text.txt и печатает в Onegin_sorted.txt три версии текста: отсортированную в алфавитном порядке слева направо, справа налево и оригинал поэмы.

## Как делает
Программа считывает текст произведения из файла Onegin_text.txt в оперативную память (буфер text), разбивает его на строки, запоминая при этом их длину, данные о каждой считанной строке записываются в массив index, 
состоящий из структур smartString - хранящей в себе указатель на первый символ нужной строки и длину этой строки.
Далее, с помощью функций быстрой сортировки (стандартный qsort из stdlib.h и собственный) текст произведения сортируется в алфавитном порядке слева направо и печатается в файл Onegin_sorted.txt, 
после чего текст сортируется в справа на лево и так же выводится в файл, в конце выводиться оригинал Евгения Онегина в тот же файл, используя text. Сортировка в алфавитном порядке игнорирует все небуквенные символы и игнорирует регистр символа,
за счет чего при обратной сортировке соседние строки имеют одинаковые по произношению окончания (рифмуются).
!!! Оригинал священного текста при этом никак не меняется, все сортировки выполняются изменением в массиве index, 
буффер text с самими строчками произведения, записанными по порядку, не меняется, все ценители русской классики могут спать спокойно!!!

## Как скомпилировать и запустить
Скачайте файл Onegin.cpp, расположите файл Onegin_text.txt в той же папке, что и .cpp, в терминале перейдите в эту папку и скомпилируйте Onegin.cpp
Для компиляции проекта подойдет любой компилятор C++, пример для g++ (рекомендуется):
g++ .\Onegin.cpp
После чего компилятор создаст в этой папке исполняемый файл a.exe, запустите его:
.\a 
Готово!!! В терминал должна появиться информация о работе программы, а в папке появиться файл Onegin_sorted.txt с тремя версиями произведения.

## Пример работы
Приведу пример работы на первой строфе Онегина, вывод в консоль:

We need to reallocate memory for index: 000001B9F3022550, index size: 5, lines read: 5                                                                                       
We reallocate memory for index:         000001B9F3024730, index size: 10, lines read: 5                                                                                      
We need to reallocate memory for index: 000001B9F3024730, index size: 10, lines read: 10                                                 
We reallocate memory for index:         000001B9F3024730, index size: 20, lines read: 10
File completely read, number of strings read: 14, first string: <My uncle's goodness is extreme,>, len: 31, last string: <When will the devil take his ow>, len: 30
All sorting is completed and printed in file

Вывод в файл:

Printing array with 14 lines:
1 pointer: 000001B9F3023663, len: 31 <A dying man with art to soothe,>
2 pointer: 000001B9F30235A5, len: 32 <And nothing more important sees;>
3 pointer: 000001B9F30236A9, len: 36 <And physic bring with mournful face,>
4 pointer: 000001B9F30235C7, len: 23 <A paragon of virtue he!>
5 pointer: 000001B9F3023684, len: 35 <Beneath his head the pillow smooth,>
6 pointer: 000001B9F30235E0, len: 31 <But what a nuisance it will be,>
7 pointer: 000001B9F3023601, len: 36 <Chained to his bedside night and day>
8 pointer: 000001B9F3023580, len: 35 <He hath acquired the world's esteem>
9 pointer: 000001B9F3023561, len: 29 <If seriously he hath disease;>
10 pointer: 000001B9F3023540, len: 31 <My uncle's goodness is extreme,>
11 pointer: 000001B9F30236CF, len: 27 <To sigh and meditate alone:>
12 pointer: 000001B9F30236EC, len: 30 <When will the devil take his ow>
13 pointer: 000001B9F3023627, len: 30 <Without a chance to slip away.>
14 pointer: 000001B9F3023647, len: 26 <Ye need dissimulation base>



########################################################################################################################



Printing array with 14 lines:
1 pointer: 000001B9F30235E0, len: 31 <But what a nuisance it will be,>
2 pointer: 000001B9F30236A9, len: 36 <And physic bring with mournful face,>
3 pointer: 000001B9F30235C7, len: 23 <A paragon of virtue he!>
4 pointer: 000001B9F3023663, len: 31 <A dying man with art to soothe,>
5 pointer: 000001B9F3023540, len: 31 <My uncle's goodness is extreme,>
6 pointer: 000001B9F30236CF, len: 27 <To sigh and meditate alone:>
7 pointer: 000001B9F3023647, len: 26 <Ye need dissimulation base>
8 pointer: 000001B9F3023561, len: 29 <If seriously he hath disease;>
9 pointer: 000001B9F3023684, len: 35 <Beneath his head the pillow smooth,>
10 pointer: 000001B9F3023580, len: 35 <He hath acquired the world's esteem>
11 pointer: 000001B9F30236EC, len: 30 <When will the devil take his ow>
12 pointer: 000001B9F30235A5, len: 32 <And nothing more important sees;>
13 pointer: 000001B9F3023601, len: 36 <Chained to his bedside night and day>
14 pointer: 000001B9F3023627, len: 30 <Without a chance to slip away.>



########################################################################################################################



1 pointer: 000001B9F3023540 <My uncle's goodness is extreme,>
2 pointer: 000001B9F3023561 <If seriously he hath disease;>
3 pointer: 000001B9F3023580 <He hath acquired the world's esteem>
4 pointer: 000001B9F30235A5 <And nothing more important sees;>
5 pointer: 000001B9F30235C7 <A paragon of virtue he!>
6 pointer: 000001B9F30235E0 <But what a nuisance it will be,>
7 pointer: 000001B9F3023601 <Chained to his bedside night and day>
8 pointer: 000001B9F3023627 <Without a chance to slip away.>
9 pointer: 000001B9F3023647 <Ye need dissimulation base>
10 pointer: 000001B9F3023663 <A dying man with art to soothe,>
11 pointer: 000001B9F3023684 <Beneath his head the pillow smooth,>
12 pointer: 000001B9F30236A9 <And physic bring with mournful face,>
13 pointer: 000001B9F30236CF <To sigh and meditate alone:>
14 pointer: 000001B9F30236EC <When will the devil take his ow>


## Структура проекта

Проект небольшой, поэтому весь код находиться в одном файле Onegin. cpp, краткое описание всех используемых функций:

smartString* getStringsFromFile(  const char* const file_name, unsigned int* const num_of_lines_read_p); - описание
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
## Чему я научился

Понял принцип работы быстрой сортировки, написав свою версию
Научился использовать указатель на функцию, на примере компаратора, передаваемого в функцию сортировки
Глубже погрузился в адресную арифметику и преобразование типов, пока писал универсальную сортировку для массива данных любого типа и компараторы для строк
Изучил работу realloc() на примере динамически расширяющегося массива index, данные об этом как раз выводятся в консоль
Узнал об errno, strerror() и применил в оболочках для calloc(), realloc(), fopen()

## Интересные моменты и внедренные фичи

Были написанны оболочки safeCalloc(), safeRealloc(), safeOpen() для удобного и безопасного использования стандартных функций.
Выделение памяти и чтение текста было оптимизированно за счет функции getSizeOfFile(), возвращающей длину текстового файла в байтах, обращаясь к ОС (без циклов!!!).
Сортировка строк справа налево была оптимизированна с помощью внедрения структуры smartString, хранящей длину каждой строки => нам не нужно проходиться по каждой строке при каждом сравнении с помощью
strnlen(), ее длина уже известна. Более того, лишний проход по строке выполняется не 1, а 0 раз, длина строки считается с помощью дополнительного счётчика во время разбиения текста на строки, лишних проходов по тексту не происходит.
В компараторах для отладки assert()'ы проверяют не только что переданный им указатель на элемент массива не нулевой (указатель на структуру), но и то, что в этой структуре указатель на строку не нулевой (сравниваемые элементы корректны) 
Программа потребляет минимум памяти: один массив под сам текст и один массив index, который сортируется. За счет того, что мы сортируем именно index, а не сам текст, для сокращения времени работы (не перемещаем длинные строки), мы получаем
гарантию безопасности (нас не тронут ценители Пушкина, т.к. мы не трогаем оригинальный текст) и возможность всегда обратить к оригиналу, что и делаем в конце ( printText() выводит оригинальный текс, не нуждаясь в начальном index).
