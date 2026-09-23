# Евгений Онегин

А. С. Пушкин так хорошо описал быт и нравы современной ему жизни в поэме «Евгений Онегин», что её часто называют «энциклопедией русской жизни того времени».
Но в энциклопедии всё должно быть отсортировано по алфавиту — а Пушкин, будучи гуманитарием, этого не сделал. Поможем ему, отсортировав строки его произведения.

## Что делает

Программа считывает текст произведения из файла `Onegin_text.txt` и печатает в `Onegin_sorted.txt` три версии текста:

- отсортированную в алфавитном порядке слева направо
- отсортированную в алфавитном порядке справа налево
- оригинал поэмы

## Как делает

Программа считывает текст произведения из файла `Onegin_text.txt` в оперативную память (буфер `text`), разбивает его на строки, запоминая при этом их длину. Данные о каждой считанной строке записываются в массив `index`, состоящий из структур `smartString` — хранящих в себе указатель на первый символ нужной строки и длину этой строки.

Далее с помощью функций быстрой сортировки (стандартный `qsort` из `<stdlib.h>` и собственный `myQSort`) текст произведения сортируется в алфавитном порядке слева направо и печатается в файл `Onegin_sorted.txt`, после чего текст сортируется справа налево и так же выводится в файл. В конце выводится оригинал «Евгения Онегина» в тот же файл, используя `text`. Сортировка в алфавитном порядке игнорирует все небуквенные символы и игнорирует регистр символа, за счёт чего при обратной сортировке соседние строки имеют одинаковые по произношению окончания (рифмуются).

> **!!!Оригинал священного текста при этом никак не меняется!!!** Все сортировки выполняются изменением в массиве `index`, буфер `text` с самими строчками произведения, записанными по порядку, не меняется. Все ценители русской классики могут спать спокойно!

## Как скомпилировать и запустить

Скачайте файл `Onegin.cpp`, расположите файл `Onegin_text.txt` в той же папке, что и `.cpp`. В терминале перейдите в эту папку и скомпилируйте `Onegin.cpp`.

Для компиляции проекта подойдёт любой компилятор C++, пример для `g++` (рекомендуется):

```bash
g++ .\Onegin.cpp
```

После чего компилятор создаст в этой папке исполняемый файл `a.exe`, запустите его:

```bash
.\a
```

**Готово!** В терминале должна появиться информация о работе программы, а в папке — файл `Onegin_sorted.txt` с тремя версиями произведения.

## Пример работы

Приведу пример работы на первой строфе «Онегина». Вывод в консоль:

```text
We need to reallocate memory for index: 000001B9F3022550, index size: 5, lines read: 5
We reallocate memory for index:         000001B9F3024730, index size: 10, lines read: 5
We need to reallocate memory for index: 000001B9F3024730, index size: 10, lines read: 10
We reallocate memory for index:         000001B9F3024730, index size: 20, lines read: 10
File completely read, number of strings read: 14, first string: <My uncle's goodness is extreme,>, len: 31, last string: <When will the devil take his ow>, len: 30
All sorting is completed and printed in file
```

Вывод в файл:

```text
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
```

## Структура проекта

Проект небольшой, поэтому весь код находится в одном файле `Onegin.cpp`.

Краткое описание всех используемых функций:

**Чтение и вывод**

- `smartString* getStringsFromFile(const char* const file_name, unsigned int* const num_of_lines_read_p);` — читает файл целиком в динамический буфер, разбивает его на строки (заменяя `\r\n` на `\0`), строит и возвращает массив структур `smartString`. Количество прочитанных строк пишет по указателю `num_of_lines_read_p`. Массив расширяется через `safeRealloc` при переполнении.
- `size_t getSizeOfFile(FILE* file);` — возвращает размер файла в байтах через `fstat`, то есть запросом к ОС, без чтения содержимого и без циклов.
- `void printArray(FILE* out, const smartString* const index, const unsigned int num_of_lines);` — печатает в файл `out` массив строк: номер, адрес указателя, длину и содержимое каждой строки.
- `void printText(FILE* out, const char* const text, const unsigned int number_of_lines);` — печатает в файл `out` исходный текст в оригинальном порядке, проходя по буферу `text` и ориентируясь на двойные `\0` между строками.
- `void printSeparator(FILE* out);` — печатает в файл `out` разделительную линию из символов `#` между секциями вывода.

**Безопасные обёртки над стандартными функциями**

- `void* safeCalloc(const size_t number_of_elements, const size_t size_of_element);` — обёртка над `calloc`. При неудаче печатает в `stderr` причину через `strerror(errno)` и завершает программу с `EXIT_FAILURE`.
- `void* safeRealloc(void* const old_pointer, const size_t new_size);` — обёртка над `realloc` с той же обработкой ошибок.
- `FILE* safeOpen(const char* const file_name, const char* const mode);` — обёртка над `fopen`

**Сортировка**

- `void myQSort(void* const array_void, const unsigned int number_of_elements, const unsigned int size_of_elem, int (*compare)(const void* a, const void* b));` — собственная реализация quicksort. Опорный элемент — последний в массиве. Для массивов из ≤ 3 элементов вызывает `trivialSort`. Работает с любым типом данных через указатель на функцию-компаратор (аналог стандартного `qsort`).
- `void trivialSort(void* const array_void, const unsigned int number_of_elements, const unsigned int size_of_elem, int (*compare)(const void* a, const void* b));` — сортировка массива из ≤ 3 элементов сортировочной сеткой. Вызывается из `myQSort` как база рекурсии.
- `void swap(char* const a, char* const b, const unsigned int size_of_elem);` — побайтовый обмен двух элементов произвольного размера.

**Компараторы**

- `int compareAlphabetLeft(const void* a, const void* b);` — компаратор для сортировки «слева направо»: сравнивает строки посимвольно с начала, пропуская не-буквы и игнорируя регистр. Возвращает `-1`, `0` или `1`.
- `int compareAlphabetRight(const void* a, const void* b);` — компаратор для сортировки «справа налево»: то же самое, но идёт с конца строки к началу. Благодаря этому соседние строки рифмуются.

## Чему я научился

- Понял принцип работы быстрой сортировки, написав свою версию.
- Научился использовать указатель на функцию на примере компаратора, передаваемого в функцию сортировки.
- Глубже погрузился в адресную арифметику и преобразование типов, пока писал универсальную сортировку для массива данных любого типа и компараторы для строк.
- Изучил работу `realloc()` на примере динамически расширяющегося массива `index` — данные об этом как раз выводятся в консоль.
- Узнал об `errno`, `strerror()` и применил в обёртках для `calloc()`, `realloc()`, `fopen()`.

## Интересные моменты и внедрённые фичи

- **Обёртки `safeCalloc()`, `safeRealloc()`, `safeOpen()`** написаны для удобного и безопасного использования стандартных функций: при ошибке печатают причину через `strerror(errno)` и корректно завершают программу.
- **Выделение памяти и чтение текста оптимизированы** за счёт функции `getSizeOfFile()`, возвращающей длину текстового файла в байтах, обращаясь к ОС (без циклов!).
- **Сортировка строк справа налево оптимизирована** с помощью структуры `smartString`, хранящей длину каждой строки. Компаратору не нужно проходить по каждой строке при каждом сравнении через `strnlen()` — её длина уже известна. Более того, лишний проход по строке выполняется не 1, а 0 раз: длина строки считается с помощью дополнительного счётчика во время разбиения текста на строки, лишних проходов по тексту не происходит.
- **`assert` в компараторах** для отладки проверяют не только то, что переданный им указатель на элемент массива не нулевой (указатель на структуру), но и то, что в этой структуре указатель на строку не нулевой (сравниваемые элементы корректны).
- **Программа потребляет минимум памяти**: один массив под сам текст и один массив `index`, который сортируется. За счёт того, что мы сортируем именно `index`, а не сам текст (не перемещаем длинные строки), мы получаем гарантию безопасности (оригинальный текст не трогается) и возможность всегда обратиться к оригиналу — что и делаем в конце: `printText()` выводит оригинальный текст, не нуждаясь в начальном `index`.
