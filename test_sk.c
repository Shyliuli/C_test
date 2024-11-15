#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#define TEST_NUM 2        // 测试个数
#define INPUT_ARGS_NUMS 3 // 函数输入个数
// 定义输入和输出的变量类型宏
#define INPUT_TYPE_1 int
#define INPUT_TYPE_2 int
#define INPUT_TYPE_3 int
// 可以更多....
#define OUTPUT_TYPE int
// 用于判断是否有 printf 调用
INPUT_TYPE_1 input_args_1[TEST_NUM] = {1, 2}; // 输入变量_1
INPUT_TYPE_2 input_args_2[TEST_NUM] = {2, 2}; // 输入变量_2
INPUT_TYPE_3 input_args_3[TEST_NUM] = {3, 2}; // 输入变量_3
//......可以有更多，记得改INPUT_ARGS_NUMS 和 INPUT_TYPE_*
#if defined(OUTPUT_TYPE) &&OUTPUT_TYPE!=void
OUTPUT_TYPE expected_output[TEST_NUM] = {6, 1}; 
#endif         // 期待返回变量
#define PRINTF_MAX_ARGS 1000                             // printf 参数最大个数
const char *expected_printf_input[PRINTF_MAX_ARGS] = {}; // 预期printf输入
// 用来检查和比较输入参数与预期的打印输入
/*一些不用设置的东西*/
#define error_color(A)          \
    printf("\033[43m\033[31m"); \
    A;                          \
    printf("\033[0m") // 设置颜色，背景黄前景红
#define right_color(A)          \
    printf("\033[42m\033[32m"); \
    A;                          \
    printf("\033[0m")                   // 设置颜色，背景绿前景绿
int is_broken = 0;                      // 是否测试失败
int test_count=0; //测试轮数 
/*一些不用设置的东西*/

/*测试函数开始*/
void test_func(); // 声明,实现在下面，可以自己改
/*测试函数结束*/
/*辅助函数开始*/
void myprintf(const char *format, ...); // 声明
/*辅助函数结束*/
#define printf myprintf
/*待测试函数开始*/
int test(int a, int b, int c)
{
    return a + b + c;
}
void *TEST_FUNC_NAME = (void *)test; // 测试函数指针,请一并修改...
/*待测试函数结束*/
#undef printf
/*main函数*/
int main()
{
    // 测试函数调用
    test_func();
    if (is_broken)
    {
        error_color(printf("FAILED\n"));
    }
    else
    {
        right_color(printf("PASS\n"));
    }
    return 0;
}
/*main函数结束*/
// count变量
int myprintf_count = 0;
void myprintf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // 缓冲区，用于存储格式化后的输出
    char buffer[1024];
    int len = vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    // 检查格式化后的输出是否与预期的输出匹配
    if (strcmp(buffer, expected_printf_input[myprintf_count]) != 0)
    {

        // 如果不匹配，打印错误信息到标准错误输出
        error_color(printf("Error at test %d:printf Expected '%s', but got '%s'\n",test_count,expected_printf_input[myprintf_count], buffer));
        is_broken = 1;
    }

    myprintf_count++;
}
void test_func()
{
    for ( test_count = 0; test_count < TEST_NUM; test_count++)
    {
        INPUT_TYPE_1 input_arg_1 = input_args_1[test_count];
        INPUT_TYPE_2 input_arg_2 = input_args_2[test_count];
        INPUT_TYPE_3 input_arg_3 = input_args_3[test_count];
        // 调用待测试函数
        #if defined(OUTPUT_TYPE)&&OUTPUT_TYPE!=void
            OUTPUT_TYPE output;
            switch (INPUT_ARGS_NUMS)
            {
            case 0:
                output = ((OUTPUT_TYPE(*)(void))TEST_FUNC_NAME)();
                break;
            case 1:
                output = ((OUTPUT_TYPE(*)(INPUT_TYPE_1))TEST_FUNC_NAME)(input_arg_1);
                break;
            case 2:
                output = ((OUTPUT_TYPE(*)(INPUT_TYPE_1, INPUT_TYPE_2))TEST_FUNC_NAME)(input_arg_1, input_arg_2);
                break;
            case 3:
                output = ((OUTPUT_TYPE(*)(INPUT_TYPE_1, INPUT_TYPE_2, INPUT_TYPE_3))TEST_FUNC_NAME)(input_arg_1, input_arg_2, input_arg_3);
                break;

            default:
                break;
            }

            // 检查输出是否与预期一致
            if (output == expected_output[test_count])
            {
                continue;
            }
            else{
            
                error_color(printf("Test %d failed: expected %d, but got %d\n", test_count, expected_output[test_count], output));
                is_broken = 1;
            }
        
        #else
        
            switch (INPUT_ARGS_NUMS)
            {
            case 0:
                ((void (*)(void))TEST_FUNC_NAME)();
                break;
            case 1:

                ((void (*)(INPUT_TYPE_1))TEST_FUNC_NAME)(input_arg_1);

                break;
            case 2:
                ((void (*)(INPUT_TYPE_1, INPUT_TYPE_2))TEST_FUNC_NAME)(input_arg_1, input_arg_2);
                break;
            case 3:
                ((void (*)(INPUT_TYPE_1, INPUT_TYPE_2, INPUT_TYPE_3))TEST_FUNC_NAME)(input_arg_1, input_arg_2, input_arg_3);
                break;

            default:
                break;
            }
        #endif
        
    }
}