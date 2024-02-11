#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <bitset>
#include <vector>
#include <map>
#include <mutex>
#include <thread>

#define SIZE 10000

class Stack {
public:
    Stack();
    ~Stack();

    // Set stack pointer
    void setSP(int sp);

    // Set frame pointer
    void setFP(int fp);

    // Set code pointer
    void setCP(int cp);

    // Push frame pointer to stack
    void pushfp();

    // Pop frame pointer from stack
    void popfp();

    // Set new frame pointer to current stack pointer
    void newfp();

    // Push constant to stack
    void pushc(const int c);

    // Read frame pointer value
    void rdfp(const int index);

    // Write value to frame pointer
    void wtfp(const int index);

    // Allocate memory on heap
    void New();

    // Delete memory on heap
    void Delete();

    // Read value from memory
    void rd();

    // Write value to memory
    void wt();

    // Increment value on stack
    void inc();

    // Decrement value on stack
    void dec();

    // Negate value on stack
    void neg();

    // Add values on stack
    void add();

    // Subtract values on stack
    void sub();

    // Multiply values on stack
    void mul();

    // Divide values on stack
    void div();

    // Modulo values on stack
    void mod();

    // Bitwise shift right
    void shr();

    // Bitwise shift left
    void shl();

    // Bitwise AND
    void And();

    // Bitwise OR
    void Or();

    // Bitwise XOR
    void Xor();

    // Swap values on stack
    void swp();

    // Duplicate value on stack
    void dup();

    // Pop value from stack
    void pop();

    // Equal values on stack
    void eq();

    // Less than 0
    void less1();

    // Jump to code position
    void jmp(int index);

    // Jump to code position if value is not 0
    void jc(int index);

    // Call function
    void call(int index);

    // Return from function
    void ret();

    // Output character
    void out();

    // Input character
    void in();

    // Load file to memory
    void load(const char* filename);

    // Run code
    void run();

private:
    std::vector<uint32_t> stack_;
    std::vector<uint32_t> heap_;
    uint32_t sp_;
    uint32_t fp_;
    uint32_t cp_;
    std::map<int, uint32_t> labels_;
    std::mutex mtx_;
    std::thread thread_;

    // Check stack bounds
    void checkStackBounds();

    // Check heap bounds
    void checkHeapBounds();

    // Allocate memory on heap
    void allocateHeap(int size);

    // Free memory on heap
    void freeHeap(int index);

    // Run code in separate thread
    void runInThread();
};

#endif // STACK_H