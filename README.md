# Simpel_C_test
# 简易C语言函数测试框架
![测试图片](https://github.com/user-attachments/assets/57497830-2375-4452-add8-6b97e1e14e85)


## 项目简介

简易C语言函数测试框架是一个用于自动化测试C语言函数的工具。它提供了一种简单的方式来定义输入参数、预期输出以及预期打印内容，并通过自动化的方式验证函数的正确性。

## 特性

- **自动化测试**: 自动执行测试用例并验证结果。
- **多参数支持**: 支持不同数量和类型的输入参数。
- **输出验证**: 验证函数的返回值是否符合预期。
- **打印验证**: 验证函数内部调用的`printf`输出是否符合预期。
- **颜色输出**: 通过颜色区分测试通过和失败的结果，便于快速识别问题。

## 使用方法

### 1. 定义测试用例

在代码中定义测试用例的输入参数和预期输出。例如：

```c
#define TEST_NUM 2        // 测试个数
#define INPUT_ARGS_NUMS 3 // 函数输入个数
// 定义输入和输出的变量类型宏
#define INPUT_TYPE_1 int
#define INPUT_TYPE_2 int
#define INPUT_TYPE_3 int
// 可以更多....
#define OUTPUT_TYPE int
//函数返回值类型宏
#define OUTPUT_TYPE_IS_NOT_VOID 1
//如果函数不返回，定义为0，否则为1
// 用于判断是否有 printf 调用
INPUT_TYPE_1 input_args_1[TEST_NUM] = {1, 2}; // 输入变量_1
INPUT_TYPE_2 input_args_2[TEST_NUM] = {2, 2}; // 输入变量_2
INPUT_TYPE_3 input_args_3[TEST_NUM] = {3, 2}; // 输入变量_3
//......可以有更多，记得改INPUT_ARGS_NUMS 和 INPUT_TYPE_*
#if OUTPUT_TYPE_IS_NOT_VOID
OUTPUT_TYPE expected_output[TEST_NUM] = {6, 6}; 
#endif         // 期待返回变量
#define PRINTF_MAX_ARGS 1000                             // printf 参数最大个数
const char *expected_printf_input[PRINTF_MAX_ARGS] = {}; // 预期printf输入
```
需注意：输入变量小于3时，只需要按需更改INPUT_TYPE和input_args;若无输入则无须更改.<br>
同理，如果是void函数，无须更改expected_output,但是需要将OUTPUT_TYPE改为void,并设置OUTPUT_TYPE_IS_NOT_VOID为0<br>
最后，expected_printf_input按照测试顺序填写，例如存在3个测试，预期测试1无输出，测试2输出“ab”,测试3输出“cd”，则这样填：
```c
const char *expected_printf_input[PRINTF_MAX_ARGS] = {"ab","cd"}; // 预期printf输入

```
### 2. 定义待测试函数

定义待测试的函数，并将其指针赋值给`TEST_FUNC_NAME`。例如：

```c
int test(int a, int b, int c)
{
    return a + b + c;
}

void *TEST_FUNC_NAME = (void *)test;
```

### 3. 运行测试

编译并运行程序，框架将自动执行测试用例并输出结果。

```bash
gcc test_sk.c -o test_sk
./test_sk
```

### 4. 查看测试结果

测试结果将以彩色输出的形式显示，绿色表示测试通过，红色表示测试失败。



## 贡献

欢迎提交问题和改进建议。请通过GitHub的Issue和Pull Request功能参与项目。

## 许可证

本项目采用BSD许可证。详细信息请参阅LICENSE文件。


