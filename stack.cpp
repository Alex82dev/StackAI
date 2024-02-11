#include "Stack.h"
#include <iostream>
#include <bitset>
#include <fstream>
#include <cstdio>

Stack::Stack() {
    stack_.resize(SIZE);
    heap_.resize(SIZE);
    sp_ = -1;
    fp_ = -1;
    cp_ = 0;
}

Stack::~Stack() {
    if (thread_.joinable()) {
        thread_.join();
    }
}

void Stack::setSP(int sp) {
    sp_ = sp;
}

void Stack::setFP(int fp) {
    fp_ = fp;
}

void Stack::setCP(int cp) {
    cp_ = cp;
}

void Stack::pushfp() {
    setSP(sp_ + 1);
    stack_[sp_] = fp_;
}

void Stack::popfp() {
    fp_ = stack_[sp_];
    setSP(sp_ - 1);
}

void Stack::newfp() {
    fp_ = sp_;
}

void Stack::pushc(const int c) {
    setSP(sp_ + 1);
    stack_[sp_] = c;
}

void Stack::rdfp(const int index) {
    setSP(sp_ + 1);
    stack_[sp_] = stack_[fp_ + index];
}

void Stack::wtfp(const int index) {
    stack_[fp_ + index] = stack_[sp_];
}

void Stack::New() {
    int size = stack_[sp_];
    allocateHeap(size);
    stack_[sp_] = heap_.size() - size - 1;
}

void Stack::Delete() {
    int index = stack_[sp_];
    freeHeap(index);
}

void Stack::rd() {
    int index = stack_[sp_];
    stack_[sp_] = heap_[index];
}

void Stack::wt() {
    int index = stack_[sp_];
    heap_[index] = stack_[sp_ - 1];
    setSP(sp_ - 1);
}

void Stack::inc() {
    stack_[sp_]++;
}

void Stack::dec() {
    stack_[sp_]--;
}

void Stack::neg() {
    stack_[sp_] = -stack_[sp_];
}

void Stack::add() {
    int b = stack_[sp_];
    setSP(sp_ - 1);
    int a = stack_[sp_];
    stack_[sp_] = a + b;
}

void Stack::sub() {
    int b = stack_[sp_];
    setSP(sp_ - 1);
    int a = stack_[sp_];
    stack_[sp_] = a - b;
}

void Stack::mul() {
    int b = stack_[sp_];
    setSP(sp_ - 1);
    int a = stack_[sp_];
    stack_[sp_] = a * b;
}

void Stack::div() {
    int b = stack_[sp_];
    setSP(sp_ - 1);
    int a = stack_[sp_];
    stack_[sp_] = a / b;
}

void Stack::mod() {
    int b = stack_[sp_];
    setSP(sp_ - 1);
    int a = stack_[sp_];
    stack_[sp_] = a % b;
}

void Stack::shr() {
    int b = stack_[sp_];
    setSP(sp_ - 1);
    int a = stack_[sp_];
    stack_[sp_] = a >> b;
}

void Stack::shl() {
    int b = stack_[sp_];
    setSP(sp_ - 1);
    int a = stack_[sp_];
    stack_[sp_] = a << b;
}

void Stack::And() {
    int b = stack_[sp_];
    setSP(sp_ - 1);
    int a = stack_[sp_];
    stack_[sp_] = a & b;
}

void Stack::Or() {
    int b = stack_[sp_];
    setSP(sp_ - 1);
    int a = stack_[sp_];
    stack_[sp_] = a | b;
}

void Stack::Xor() {
    int b = stack_[sp_];
    setSP(sp\_ - 1);
int a = stack\_[sp\_];
stack\_[sp\_] = a ^ b;
}

void Stack::swp() {
int temp = stack\_[sp\_];
stack\_[sp\_] = stack\_[sp\_ - 1];
stack\_[sp\_ - 1] = temp;
}

void Stack::dup() {
int value = stack\_[sp\_];
stack\_[sp\_ + 1] = value;
sp\_++;
}

void Stack::pop() {
sp\_--;
}

void Stack::eq() {
int b = stack\_[sp\_];
setSP(sp\_ - 1);
int a = stack\_[sp\_];
if (a == b) {
stack\_[sp\_] = 1;
} else {
stack\_[sp\_] = 0;
}
}

void Stack::less1() {
int a = stack\_[sp\_];
if (a < 0) {
stack\_[sp\_] = 1;
} else {
stack\_[sp\_] = 0;
}
}

void Stack::jmp(int index) {
cp\_ = index;
}

void Stack::jc(int index) {
int value = stack\_[sp\_];
if (value != 0) {
cp\_ = index;
}
}

void Stack::call(int index) {
pushfp();
stack\_[sp\_] = cp\_;
cp\_ = index;
}

void Stack::ret() {
cp\_ = stack\_[sp\_];
fp\_ = stack\_[sp\_ - 1];
setSP(fp\_);
}

void Stack::out() {
char c = stack\_[sp\_];
std::cout << c;
pop();
}

void Stack::in() {
char c;
std::cin >> c;
pushc((int)c);
}

void Stack::load(const char* filename) {
std::ifstream file(filename, std::ios::binary);
if (!file) {
throw std::runtime\_error("Error opening file");
}
file.seekg(0, std::ios::end);
size\_t size = file.tellg();
file.seekg(0, std::ios::beg);
char\* buffer = new char[size];
file.read(buffer, size);
for (size\_t i = 0; i < size; i++) {
stack\_[size - i - 1] = (uint32\_t)buffer[i];
}
delete\[\] buffer;
}

void Stack::run() {
while (cp\_ < sp\_) {
instruction();
}
}

void Stack::instruction() {
switch (stack\_[cp\_]) {
case 0x00: // NOP
cp\_++;
break;
case 0x01: // PUSHFP
pushfp();
cp\_++;
break;
case 0x02: // POPFP
popfp();
cp\_++;
break;
case 0x03: // NEWFP
newfp();
cp\_++;
break;
case 0x04: // PUSHC
int value = stack\_[cp\_ + 1];
pushc(value);
cp\_ += 2;
break;
case 0x05: // RDFP
int index = stack\_[cp\_ + 1];
rdfp(index);
cp\_ += 2;
break;
case 0x06: // WTFP
int index2 = stack\_[cp\_ + 1];
wtfp(index2);
cp\_ += 2;
break;
case 0x10: // NEW
int size = stack\_[cp\_ + 1];
New();
cp\_ += 2;
break;
case 0x11: // DELETE
int index3 = stack\_[cp\_];
Delete();
cp\_++;
break;
case 0x12: // RD
int index4 = stack\_[cp\_];
rd();
cp\_++;
break;
case 0x13: // WT
int index5 = stack\_[cp\_];
wt();
cp\_++;
break;
case 0x20: // INC
inc();
cp\_++;
break;
case 0x21: // DEC
dec();
cp\_++;
break;
case 0x22: // NEG
neg();
cp\_++;
break;
case 0x23: // ADD
add();
cp\_++;
break;
case 0x24: // SUB
sub();
cp\_++;
break;
case 0x25: // MUL
mul();
cp\_++;
break;
case 0x26: // DIV
div();
cp\_++;
break;
case 0x27: // MOD
mod();
cp\_++;
break;
case 0x28: // SHR
shr();
cp\_++;
break;
case 0x29: // SH
void Stack::Xor() {
int b = stack\_[sp\_];
setSP(sp\_ - 1);
int a = stack\_[sp\_];
stack\_[sp\_] = a ^ b;
}

void Stack::swp() {
int temp = stack\_[sp\_];
stack\_[sp\_] = stack\_[sp\_ - 1];
stack\_[sp\_ - 1] = temp;
}

void Stack::dup() {
stack\_[sp\_ + 1] = stack\_[sp\_];
sp\_++;
}

void Stack::pop() {
if (sp\_ <= 0) {
throw std::runtime\_error("Stack underflow");
}
sp\_--;
}

void Stack::eq() {
int b = stack\_[sp\_];
setSP(sp\_ - 1);
int a = stack\_[sp\_];
stack\_[sp\_] = (a == b) ? 1 : 0;
}

void Stack::less1() {
int a = stack\_[sp\_];
stack\_[sp\_] = (a < 0) ? 1 : 0;
}

void Stack::jmp(int index) {
cp\_ = index;
}

void Stack::jc(int index) {
int a = stack\_[sp\_];
setSP(sp\_ - 1);
if (a == 0) {
cp\_++;
} else {
cp\_ = index;
}
}

void Stack::call(int index) {
pushfp();
stack\_[sp\_] = cp\_;
setSP(sp\_ + 1);
cp\_ = index;
}

void Stack::ret() {
setCP(stack\_[sp\_]);
setSP(fp\_);
}

void Stack::out() {
char x = (char)stack\_[sp\_];
setSP(sp\_ - 1);
std::cout << x;
}

void Stack::in() {
char input;
std::cin >> input;
stack\_[sp\_] = (uint32\_t)input;
setSP(sp\_ + 1);
}

void Stack::run() {
while (cp\_ < SIZE) {
switch (stack\_[cp\_]) {
case 0x0: // NOP
cp\_++;
break;
case 0x1: // PUSHFP
pushfp();
cp\_++;
break;
case 0x2: // POPFP
popfp();
cp\_++;
break;
case 0x3: // NEWFP
newfp();
cp\_++;
break;
case 0x4: // PUSHC
cp\_ += 2;
pushc(stack\_[cp\_ - 2]);
break;
case 0x5: // RDFP
cp\_ += 2;
rdfp(stack\_[cp\_ - 2]);
break;
case 0x6: // WTFP
cp\_ += 2;
wtfp(stack\_[cp\_ - 2]);
break;
case 0x10: // NEW
cp\_ += 2;
New();
break;
case 0x11: // DELETE
cp\_++;
Delete();
break;
case 0x12: // RD
cp\_++;
rd();
break;
case 0x13: // WT
cp\_++;
wt();
break;
case 0x20: // INC
inc();
cp\_++;
break;
case 0x21: // DEC
dec();
cp\_++;
break;
case 0x22: // NEG
neg();
cp\_++;
break;
case 0x23: // ADD
add();
cp\_++;
break;
case 0x24: // SUB
sub();
cp\_++;
break;
case 0x25: // MUL
mul();
cp\_++;
break;
case 0x26: // DIV
div();
cp\_++;
break;
case 0x27: // MOD
mod();
cp\_++;
break;
case 0x28: // SHR
shr();
cp\_++;
break;
case 0x29: // SHL
shl();
cp\_++;
break;
case 0x2A: // AND
And();
cp\_++;
break;
case 0x2B: // OR
Or();
cp\_++;
break;
case 0x2C: // XOR
Xor();
cp\_++;
break;
case 0x30: // SWP
swp();
cp\_++;
break;
case 0x31: // DUP
dup();
cp\_++;
break;
case 0x32: // POP
pop();
cp\_++;
break;
case 0x40: // EQ
eq();
cp\_++;
break;
case 0x41: // LESS1
less1();
cp\_++;
break;
case 0x50: // JMP
cp\_ = stack\_[cp\_];
break;
case 0x51: // JC
cp\_++;
jc(stack\_[cp\_]);
break;
case 0x58: // CALL
call(stack\_[cp\_]);
cp\_++;
break;
case 0x59: // RET
ret();
break;
case 0x80: // OUT
out();
cp\_++;
break;
case 0x81: // IN
in();
cp\_++;
break;
default:
throw std::runtime\_error("Unknown opcode");
}
}
}

Stack::\~Stack() {
delete\[\] stack;
delete heap;
}

int main() {
Stack vm;
const char\* filename = "program.bin";
vm.load(filename);
vm.run();
return 0;
}
