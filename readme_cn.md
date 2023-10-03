# Bytecode Runner
> 一个简单的字节码运行器

这是一个字节码运行模拟器，支持类似于英特尔x86格式的字节码。

## 快速开始
在程序没有任何依赖，所以可以`git clone `后直接编译运行。     
### 设置当前运行的字节码程序   
在 `main.cpp` 文件中有 `current_code_stream` 宏，通过配置这个宏来控制要执行的程序。   
一个例子：
```c++
static std::vector< std::string > asm_code_test7
= { "test_func():", "push ebp", "mov ebp esp", "add 1 1",          "pr acc", "ret",
    "main():",      "push ebp", "mov ebp esp", "call test_func()", "leave",  "ret" };

#define current_code_stream asm_code_test1
```
## 字节码的指令与语法
### 语法
操作数 []  
**main() 为整个程序的入口点**
### 指令
#### 有关栈
`push element` 把 `element` push 到栈里。
`pop dist` 把栈顶元素 `pop` 到 `dist` 里
#### 基本运算
`add num1 num2` num1 + num2
`sub num1 num2` num2 - num1
`mul num1 num2` num1 * num2
`div num1 num2` num2 / num1
`cmp num/register num/register/memory` 比较 num1 与 num2, num1 > num2，SF
#### 跳转
`jmp dist` jm
`jne`
`je`
`call`
`ret`
`leave`
#### 调试
`pr`
`pm`
`ps`
`p`
`exit`
## 例程
```asm
test_func():
    push ebp
    mov ebp esp
    add 1 1
    pr acc
    ret
main():
    push ebp
    mov ebp esp
    call test_func()
    leave
    ret
```
```
output: acc: 2
```
## 未来
添加浮点数运算指令与逻辑运算指令，还有负数与函数的参数与局部变量的处理。
