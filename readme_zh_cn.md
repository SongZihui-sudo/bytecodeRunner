# Bytecode Runner

> 一个简单的字节码运行器

这是一个字节码运行模拟器，支持类似于英特尔 x86 格式的字节码。

## 快速开始

在程序没有任何依赖，所以可以`git clone https://github.com/SongZihui-sudo/bytecodeRunner.git`后直接编译运行。

使用 `xmake` 编译:

```
cd bytecodeRunner
xmake
```

### 设置当前运行的字节码程序

在 `main.cpp` 文件中有 `current_code_stream` 宏，通过配置这个宏来控制要执行的程序。  
一个例子：

```c++
static std::vector< std::string > asm_code_test7
= { "test_func():", "push ebp", "mov ebp, esp", "add 1, 1",          "pr acc", "ret",
    "main():",      "push ebp", "mov ebp, esp", "call test_func()", "leave",  "ret" };

#define current_code_stream asm_code_test7
```

从文本文件运行程序：

```c++
visual_machine.visual_instruction_runner.load_file( "./example.asm" );
```

## 字节码的指令与语法

### 语法

指令格式:

```
操作码 地址码1, [地址码2]
```

标签:

```
xxx:
    指令
```

字符：'c'  
立即数: 1,2,3,4,........  
内存寻址: [立即数/寄存器/变量]

**main() 为整个程序的入口点**

### 指令

#### 有关栈

`push source(立即数/寄存器/内存)` 把 `source` push 到栈里。  
`pop [destination(寄存器)]` 把栈顶元素 `pop` 到 `destination` 里

#### 基本运算

`add num1(立即数/寄存器/内存), num2(立即数/寄存器/内存)` num1 + num2  
`sub num1(立即数/寄存器/内存), num2(立即数/寄存器/内存)` num2 - num1  
`mul num1(立即数/寄存器/内存), num2(立即数/寄存器/内存)` num1 \* num2  
`div num1(立即数/寄存器/内存), num2(立即数/寄存器/内存)` num2 / num1  
`cmp destination(立即数/寄存器/内存), source(立即数/寄存器/内存)` 比较 num1 与 num2.如果 `num1 > num2` -> `SF=1`,`num1 < num2`->`SF=0`, `num1 == num2`->`ZF=1`,`num1 != num2`->`ZF=0`.

#### 跳转

`jmp destination(立即数/寄存器/内存/标签)` 直接跳转到 `destination` 处  
`jne destination(立即数/寄存器/内存/标签)` 如果 `cmp` 比较的结果为不相等就跳转  
`je destination(立即数/寄存器/内存/标签)` 如果 `cmp` 比较的结果为相等就跳转  
`jbe destination(立即数/寄存器/内存/标签)` 如果低于或等于(<=)则跳转  
`ja destination(立即数/寄存器/内存/标签)` 如果超过(>)则跳转  
`jb destination(立即数/寄存器/内存/标签)` 如果进位位被置位则跳转  
`jnb destination(立即数/寄存器/内存/标签)` 如果进位位没有置位则跳转  
`call destination(立即数/寄存器/内存/标签)`调用 `destination` 处的函数  
`ret` 从调用的函数中返回  
`leave` 用在 main 函数的结尾来进行退出

#### 调试

`pr register_name(字符串)` 打印 `register_name` 指定的寄存器内容  
`pm source(数字) count(数字)` 打印内存地址从 `source` 开始的 `count` 个内容  
`ps` 打印栈  
`p message(字符串)` 打印自定义消息  
`exit` 退出

#### 数据传送

`mov source(立即数/寄存器/内存), destination(立即数/寄存器/内存)`  
`let source(字符串), destination(立即数)` 变量声明

## 例程

```asm
test_func():
    push ebp
    mov ebp, esp
    add esp, 16
    mov esp, acc
    add ebp 1
    mov [acc], 32
    add [acc], edi
    pr acc
    sub esp, 16
    mov esp, acc
    pop ebp
    ret
main():
    push ebp
    mov ebp, esp
    add esp, 16
    mov esp, acc
    mov edi, 1
    cmp edi, 0
    jne  22
    call test_func()
    sub esp, 16
    mov esp, acc
    pop ebp
    leave
    ret
```

```
output: acc: 21
```

## TO-DO

- [x] 通过栈实现函数
- [x] 实现函数参数传入与局部变量
- [x] 实现流程控制指令
- [x] 寄存器间接寻址
- [x] 通过 esp，ebp 对系统栈的维护
- [x] 浮点数支持
- [ ] 字符串支持
- [ ] 表达式支持
