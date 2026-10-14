# MyCalculator

一个用 C 语言实现的**表达式计算器**：读取中缀表达式（如 `1.2 + 3.6 * sin((3*PI-4*PI)/4)`），
将其转换为后缀表达式（逆波兰式），再用栈求值并输出结果。

支持四则运算、括号、常量 `PI`，以及三角函数 `sin` / `cos` / `tan`。

## 文件说明

| 文件 | 作用 |
| --- | --- |
| `Calculatormain.c` | 主程序：字符分类、三角函数识别、优先级定义、中缀转后缀、后缀求值 |
| `Stack.c` / `Stack.h` | **数组栈**实现（`StackConstruct` 多一个参数，需指定初始容量） |
| `List.c` / `List.h` | 通用双向链表，链式栈的底层结构 |
| `ListStack.c` / `ListStack.h` | **链式栈**实现，基于 `List` 封装出与数组栈一致的接口 |
| `Print.c` / `Print.h` | 统一的元素 / 字符串打印接口（`StackTraverse` 的访问函数） |
| `Status.h` | 统一状态枚举 `Status`（`OK` / `ERROR`） |
| `expstrings.txt` | 10 条测试用中缀表达式 |
| `results.txt` | 上述表达式对应的期望结果 |

## 编译与运行

两套栈实现**接口兼容**，通过修改 `Calculatormain.c` 首行的 `#include` 来切换：

```c
#include "Stack.h"       // 数组栈
// #include "ListStack.h" // 链式栈
```

数组栈版本（注意 `Calculatormain.c` 中的 `StackConstruct` 需要多传一个初始容量参数）：

```bash
gcc Calculatormain.c Stack.c Print.c -o Calculatormain -lm
```

链式栈版本：

```bash
gcc Calculatormain.c List.c ListStack.c Print.c -o Calculatormain -lm
```

运行（Windows）：

```bash
./Calculatormain.exe
```

`-lm` 是必须的，因为用到了 `math.h` 中的 `sin` / `cos` / `tan`。

## 测试

`expstrings.txt` 与 `results.txt` 一一对应，可用作回归测试：

```
1.2 + 3.6 * sin((3*PI-4*PI)/4)   ->   -1.345585
2.5 * sin(PI/4) + 3.1 /cos(PI/6) ->    5.347341
0.5 * (cos(PI/3) - sin(PI/6)) + 8.2 -> 8.200000
```

## 版本库约定

`*.exe` 等编译产物由 `.gitignore` 忽略，不纳入版本管理 —— 编译产物可由源码随时重建，
提交它们只会让 diff 充满二进制噪声。克隆仓库后按上面的命令重新编译即可。

## 更新日志

- 2026-10-14 协作者补充：新增本「更新日志」小节，用于演示 `git pull`。
