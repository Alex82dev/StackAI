# StackAI
StackAI от NemtyrevAI- это  эффективная виртуальная машина со стеком, которая может быть использована для разных типов задач по обучению ИИ

Добавлены следующие механизмы безопасности:

1. Контроль доступа к памяти: добавлена функция `check_memory_access()`, которая проверяет, что индексы доступа к памяти не выходят за пределы размера стека и кучи. Если индекс выходит за пределы, то генерируется исключение `std::out_of_range`.

2. Проверка границ стека: добавлена проверка на выход за пределы стека при выполнении операций с ним. Если индекс стека `SP` становится меньше `-1`, то генерируется исключение `std::out_of_range`.

3. Многопоточность: добавлена возможность запуска виртуальной машины в отдельном потоке. Это достигается запуском функции `run()` во вторичном потоке при помощи `std::thread`. Для синхронизации доступа к общей памяти виртуальной машины используется мьютекс `mtx_`.

Кроме того, был добавлен конструктор по умолчанию и деструктор класса `Stack`, а также добавлена функция `load()`, которая загружает байт-код программы в память виртуальной машины из файла.


Виртуальная машина имеет следующие возможности:

* Сохранение и восстановление состояния стека и указателя команд (CP) в файл для последующего использования.
* Выполнение команд, загруженных из файла в виде массива байт.
* Операции с числами, такие как инкремент, декремент, умножение, деление, модуль и т.д.
* Логические операции, такие как AND, OR и XOR.
* Работа со стековой памятью, включая операции PUSH, POP, DUP и SWAP.
* Работа с кучей памяти, включая операции NEW и DELETE для выделения и освобождения памяти.
* Ввод/вывод символов.
* Сохранение и восстановление состояния стека и указателя команд (CP) в файл для последующего использования.
* Выполнение команд, загруженных из файла в виде массива байт.
* Операции с числами, такие как инкремент, декремент, умножение, деление, модуль и т.д.
* Логические операции, такие как AND, OR и XOR.
* Работа со стековой памятью, включая операции PUSH, POP, DUP и SWAP.
* Работа с кучей памяти, включая операции NEW и DELETE для выделения и освобождения памяти.
* Ввод/вывод символов.

Виртуальная машина может быть использована для обучения ИИ, поскольку она предоставляет гибкую и эффективную платформу для выполнения алгоритмов машинного обучения. Кроме того, виртуальная машина может быть использована для разработки приложений, требующих изолированной среды выполнения, например, для запуска недоверенного кода или для тестирования новых алгоритмов.

Виртуальная машина реализована на языке C++, и её код является открытым и доступным для редактирования и распространения. Виртуальная машина может быть легко интегрирована в существующие приложения или использована как отдельная программа. Виртуальная машина поддерживает различные платформы, включая Windows, Linux и macOS.

Виртуальная машина была разработана Алексеем Немтыревым (NemtyrevAI) и является собственностью компании "ЦКБ".

Виртуальная машина поддерживает различные операции, такие как загрузка и извлечение значений в/из стека, арифметические и побитовые операции, чтение/запись памяти и операции потока управления.

Виртуальная машина также имеет функции загрузки и выполнения кода из бинарного файла.

Вот краткое описание доступных операций:

pushc: поместить постоянное значение в стек.
rdfp: прочитать значение из указателя текущего кадра.
wtfp: записать значение в указатель текущего кадра.
New: Выделить память в куче.
Delete: Освободить память в куче.
rd: прочитать значение из памяти.
wt: записать значение в память.
inc: увеличить верхнее значение в стеке.
dec: Уменьшить верхнее значение в стеке.
neg: инвертировать верхнее значение в стеке.
add: добавить два верхних значения в стек.
sub: вычесть верхнее значение из второго верхнего значения в стеке.
mul: умножить два верхних значения в стеке.
div: разделить второе верхнее значение на верхнее значение в стеке.
mod: вычислить модуль второго верхнего значения по верхнему значению в стеке.
shr: сдвиг верхнего значения вправо на второе верхнее значение в стеке.
shl: сдвиг верхнего значения влево на второе верхнее значение в стеке.
And: выполнить побитовую операцию И над двумя верхними значениями стека.
Or: выполнить побитовую операцию ИЛИ над двумя верхними значениями стека.
Xor: выполнить побитовую операцию XOR над двумя верхними значениями стека.
swp: поменять местами два верхних значения в стеке.
dup: Дублировать верхнее значение в стеке.
pop: извлечь верхнее значение из стека.
eq: сравнить верхнее значение с нулем и поместить результат (0 или 1) в стек.
less1: сравнить верхнее значение с нулем и поместить результат (0 или 1) в стек.
jmp: переход к указанной позиции кода.
jc: переход к указанной позиции кода, если верхнее значение в стеке не равно нулю.
call: вызов функции.
ret: Возврат из функции.
out: Вывод символа.
in: Введите символ.
load: загрузить двоичный файл в память, начиная с текущего указателя стека.
Обратите внимание, что виртуальная машина не выполняет никаких проверок границ или обработки ошибок, поэтому программист несет ответственность за то, чтобы исполняемый код не обращался к недопустимой памяти и не выполнял недопустимые операции.

Чтобы использовать виртуальную машину, вы можете создать двоичный файл, содержащий исполняемый код, и загрузить его в память с помощью loadфункции. Код должен быть в формате с прямым порядком байтов, где каждая инструкция закодирована как 32-битное целое число без знака. 

Набор инструкций следующий:

0x0: NOP (нет операции)
0x1: PUSHC (постоянное нажатие)
0x2: RDFP (считывание указателя кадра)
0x3: WTFP (запись указателя кадра)
0x10: NEW (выделить память)
0x11: DELETE (освободить память)
0x12: RD (чтение памяти)
0x13: WT (запись в память)
0x20: INC (приращение)
0x21: DEC (декремент)
0x22: NEG (отрицание)
0x23: ADD (добавить)
0x24: SUB (вычесть)
0x25: MUL (умножить)
0x26: DIV (разделить)
0x27: MOD (модуль)
0x28: SHR (сдвиг вправо)
0x29: SHL (сдвиг влево)
0x2A: AND (побитовое И)
0x2B: OR (побитовое ИЛИ)
0x2C: XOR (побитовое исключающее ИЛИ)
0x30: SWP (своп)
0x31: DUP (дубликат)
0x32: POP (поп)
0x40: EQ (равный)
0x41: LESS1 (меньше нуля)
0x50: JMP (прыжок)
0x51: JC (прыжок, если не ноль)
0x58: CALL (звонок)
0x59: RET (возврат)
0x80: OUT (выход)
0x81: IN (вход)
Виртуальная машина также использует следующие регистры:

SP: указатель стека
FP: указатель кадра
CP: указатель кода

Стек растет вниз, а куча растет вверх. Стек и куча используют одно и то же пространство памяти, поэтому необходимо соблюдать осторожность, чтобы не перезаписать данные друг друга!!!


Примеры использования:

1. Загрузка команд из файла и выполнение их на виртуальной машине:

2. 
```c
#include "Stack.h"

int main() {
    Stack vm;
    const char* filename = "commands.bin";
    vm.load(filename);
    vm.run();
    return 0;
}
```
2. Сохранение и восстановление состояния стека и указателя команд (CP) в файл:
```c
#include "Stack.h"

int main() {
    Stack vm;
    // Загрузка и выполнение команд
    const char* filename = "commands.bin";
    vm.load(filename);
    vm.run();

    // Сохранение состояния стека и CP в файл
    vm.saveState("state.bin");

    // Чтение состояния стека и CP из файла и продолжение выполнения команд
    vm.loadState("state.bin");
    vm.run();

    return 0;
}
```
3. Работа со стеком и кучей памяти:
```c
#include "Stack.h"

int main() {
    Stack vm;

    // Выделение памяти на куче
    vm.pushc(100); // размер блока памяти
    vm.New();       // выделение памяти

    // Запись данных в блок памяти
    vm.pushc(0);    // индекс блока памяти
    vm.pushc(123);  // данные
    vm.wt();        // запись данных в блок памяти

    // Чтение данных из блока памяти
    vm.pushc(0);    // индекс блока памяти
    vm.rd();        // чтение данных из блока памяти

    // Освобождение памяти на куче
    vm.pushc(0);    // индекс блока памяти
    vm.Delete();    // освобождение памяти

    return 0;
}
```
