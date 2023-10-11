# Bytecode Runner

[中文](./readme_zh_cn.md)

> A simple bytecode runner

This is a bytecode execution emulator that supports bytecode similar to the Intel x86 format.

## Quick Start

The program does not have any dependencies, so you can compile and run it directly after `git clone https://github.com/SongZihui-sudo/bytecodeRunner.git`.

Compile using `xmake`:

```
cd bytecodeRunner
xmake
```

### Set the currently running bytecode program

There is a `current_code_stream` macro in the `main.cpp` file. You can configure this macro to control the program to be executed.
one example:

```c++
static std::vector< std::string > asm_code_test7
= { "test_func():", "push ebp", "mov ebp esp", "add 1 1", "pr acc", "ret",
     "main():", "push ebp", "mov ebp esp", "call test_func()", "leave", "ret" };

#define current_code_stream asm_code_test7
```

## Instructions and syntax of bytecode

### GRAMMAR

Command format:

```
Opcode address_code1 [address_code2]
```

Label:

```
xxx:
     instruction
```

**main() is the entry point of the entire program**

### INSTRUCTIONS

#### About the stack

`push source(immediate/register/memory)` Push `source` onto the stack.  
`pop [destination(register)]` `pop` the top element of the stack into `destination`

#### Basic operations

`add num1(immediate value/register/memory) num2(immediate value/register/memory)` num1 + num2  
`sub num1(immediate value/register/memory) num2(immediate value/register/memory)` num2 - num1  
`mul num1(immediate value/register/memory) num2(immediate value/register/memory)` num1 \* num2  
`div num1(immediate value/register/memory) num2(immediate value/register/memory)` num2 / num1  
`cmp destination(immediate value/register/memory) source(immediate value/register/memory)` Compare num1 and num2. If `num1 > num2` -> `SF=1`, `num1 < num2`->`SF= 0`, `num1 == num2`->`ZF=1`, `num1 != num2`->`ZF=0`.

#### Jump

`jmp destination(immediate value/register/memory/label)` jumps directly to `destination`  
`jne destination(immediate value/register/memory/label)` jumps if the result of `cmp` comparison is not equal  
`je destination(immediate value/register/memory/label)` jumps if the result of `cmp` comparison is equal  
`jbe destination(immediate value/register/memory/label)` jump if lower than or equal to (<=)  
`ja destination(immediate value/register/memory/label)` jump if it exceeds (>)  
`jb destination(immediate/register/memory/label)` jumps if the carry bit is set  
`jnb destination(immediate value/register/memory/label)` jumps if the carry bit is not set  
`call destination(immediate/register/memory/label)` calls the function at `destination`  
`ret` returns from the called function  
`leave` is used at the end of the main function to exit

#### debug

`pr register_name(string)` prints the contents of the register specified by `register_name`  
`pm source(number) count(number)` prints `count` contents starting from the memory address `source`
`ps` print stack  
`p message(string)` print custom message
`exit` exit

#### data transmission

`mov source(immediate number/register/memory) destination(immediate number/register/memory)`  
`let source(string) destination(immediate value)` variable declaration

## Example

```asm
test_func():
    push ebp
    mov ebp esp
    add esp 16
    mov esp acc
    add ebp 1
    mov [acc] 32
    add [acc] edi
    pr acc
    sub esp 16
    mov esp acc
    pop ebp
    ret
main():
    push ebp
    mov ebp esp
    add esp 16
    mov esp acc
    mov edi 1
    cmp edi 0
    jne  22
    call test_func()
    sub esp 16
    mov esp acc
    pop ebp
    leave
    ret
```

```
output: acc: 21
```

## TO-DO

- [x] Implement functions through stack
- [x] Implement function parameter passing and local variables
- [x] Implement process control instructions
- [x] register indirect addressing
- [x] Maintenance of system stack through esp and ebp
- [ ] Floating point support
- [ ] string support
- [ ] Expression support
