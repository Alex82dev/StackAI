#include <iostream>
#include <bitset>
#include <stdlib.h>
#include <fstream>
#include <cstdio>
#define SIZE 10000

using namespace std;

class Stack {
public:
    uint32_t SP = -1;
    uint32_t FP = -1;
    uint32_t CP = -1;
private:
    uint32_t* stack;
    size_t size;
    size_t heapStartIndex = SIZE - 1;

public:
    Stack() {
        size = 0;
        stack = new uint32_t[SIZE];
    }

    // Set stack pointer
    void setSP(int sp) {
        SP = sp;
        size = SP + 1;
    }

    // Set frame pointer
    void setFP(int fp) {
        FP = fp;
    }

    // Set code pointer
    void setCP(int cp) {
        CP = cp;
    }

    // Push frame pointer to stack
    void pushfp() {
        setSP(SP + 1);
        stack[SP] = FP;
    }

    // Pop frame pointer from stack
    void popfp() {
        FP = stack[SP];
        setSP(SP - 1);
    }

    // Set new frame pointer to current stack pointer
    void newfp() {
        FP = SP;
    }

    // Push constant to stack
    void pushc(const int c) {
        setSP(SP + 1);
        stack[SP] = c;
    }

    // Read frame pointer value
    void rdfp(const int index) {
        setSP(SP + 1);
        stack[SP] = stack[FP + index];
    }

    // Write value to frame pointer
    void wtfp(const int index) {
        stack[FP + index] = stack[SP];
    }

    // Allocate memory on heap
    void New() {
        int size = stack[SP];
        heapStartIndex -= size;
        stack[SP] = heapStartIndex;
    }

    // Delete memory on heap
    void Delete() {
        int index = stack[SP];
        setSP(SP - 1);
    }

    // Read value from memory
    void rd() {
        int index = stack[SP];
        stack[SP] = stack[index];
    }

    // Write value to memory
    void wt() {
        int index = stack[SP];
        setSP(SP - 1);
        stack[index] = stack[SP];
    }

    // Increment value on stack
    void inc() {
        stack[SP] = stack[SP] + 1;
    }

    // Decrement value on stack
    void dec() {
        stack[SP] = stack[SP] - 1;
    }

    // Negate value on stack
    void neg() {
        stack[SP] = ~stack[SP];
    }

    // Add values on stack
    void add() {
        int b = stack[SP];
        setSP(SP - 1);
        int a = stack[SP];
        stack[SP] = a + b;
    }

    // Subtract values on stack
    void sub() {
        int b = stack[SP];
        setSP(SP - 1);
        int a = stack[SP];
        stack[SP] = a - b;
    }

    // Multiply values on stack
    void mul() {
        int b = stack[SP];
        setSP(SP - 1);
        int a = stack[SP];
        stack[SP] = a * b;
    }

    // Divide values on stack
    void div() {
        int b = stack[SP];
        setSP(SP - 1);
        int a = stack[SP];
        stack[SP] = a / b;
    }

    // Modulo values on stack
    void mod() {
        int b = stack[SP];
        setSP(SP - 1);
        int a = stack[SP];
        stack[SP] = a % b;
    }

    // Bitwise shift right
    void shr() {
        int b = stack[SP];
        setSP(SP - 1);
        int a = stack[SP];
        stack[SP] = a >> b;
    }

    // Bitwise shift left
    void shl() {
        int b = stack[SP];
        setSP(SP - 1);
        int a = stack[SP];
        stack[SP] = a << b;
    }

    // Bitwise AND
    void And() {
        int b = stack[SP];
        setSP(SP - 1);
        int a = stack[SP];
        stack[SP] = a & b;
    }

    // Bitwise OR
    void Or() {
        int b = stack[SP];
        setSP(SP - 1);
        int a = stack[SP];
        stack[SP] = a | b;
    }

    // Bitwise XOR
    void Xor() {
        int b = stack[SP];
        setSP(SP - 1);
        int a = stack[SP];
        stack[SP] = a ^ b;
    }

    // Swap values on stack
    void swp() {
        int a = stack[SP];
        int b = stack[SP - 1];
        stack[SP] = b;
        stack[SP - 1] = a;
    }

    // Duplicate value on stack
    void dup() {
        setSP(SP + 1);
        stack[SP] = stack[SP - 1];
    }

    // Pop value from stack
    void pop() {
        setSP(SP - 1);
    }

    // Equal values on stack
    void eq() {
        int a = stack[SP];
        if (a == 0) {
            stack[SP] = 1;
        } else {
            stack[SP] = 0;
        }
    }

    // Less than 0
    void less1() {
        int a = stack[SP];
        if (a < 0) {
            stack[SP] = 1;
        } else {
            stack[SP] = 0;
        }
    }

    // Jump to code position
    void jmp(int index) {
        setCP(index);
    }

    // Jump to code position if value is not 0
    void jc(int index) {
        int a = stack[SP];
        setSP(SP - 1);
        if (a != 0) {
            setCP(index);
        }
    }

    // Call function
    void call(int index) {
        setSP(SP + 1);
        stack[SP] = CP;
        setCP(index);
    }

    // Return from function
    void ret() {
        setCP(stack[SP]);
        setSP(SP - 1);
    }

    // Output character
    void out() {
        char x = stack[SP];
        setSP(SP - 1);
        cout << x;
    }

    // Input character
    void in() {
        int input = getchar();
        setSP(SP + 1);
        stack[SP] = (int)input;
    }

   // Load file to memory
void load(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    // Allocate memory for file contents
    uint8_t* buffer = new uint8_t[size];
    size_t result = fread(buffer, size, 1, file);
    if (result != 1) {
        cerr << "Error: Cannot read file " << filename << endl;
        exit(1);
    }

    // Copy file contents to memory starting at current stack pointer
    for (size_t i = 0; i < size; ++i) {
        stack[SP + i] = buffer[i];
    }

    // Update stack pointer to reflect new memory size
    SP += size;

    // Free allocated memory
    delete[] buffer;
    }
//Stack Virtual Machine for AI DEV

//by Алексей Немтырев (NemtyrevAI)