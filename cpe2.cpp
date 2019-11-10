/**
 * 程序文法
 * E -> T{+T | -T}
 * T -> F{*F | /F}
 * F -> (E)|a|b|c
 */

#include "cpe2.h"
#include <stdio.h>
#include <string.h>

namespace cpe2 {

char prog[20];
char ch;
int progIndex, isSuccess;

void e(), f(), t();

void readInput() {
    progIndex = 0;
    printf("Please input the source program:\n");
    do {
        ch = (char) getchar();
        prog[progIndex++] = ch;
    } while (ch != '#');
}

int main() {
    // 输入  a+b*c#          输出   success
    // 输入  d+f#              输出   error
    // 输入  a+b*+c#        输出   error
    // 输入  a(b)#              输出   error
    readInput();

    progIndex = 0;
    isSuccess = 1;
    ch = prog[progIndex++];
    if ((ch == 'a') || (ch == 'b') || (ch == 'c') || (ch == '(')) {
        e();
    } else {
        isSuccess = 0;
    }

    if ((ch == '#') && (isSuccess == 1)) {
        printf("Success\n");
    } else {
        printf("error\n");
    }

    return 0;
}


// E -> T{+T | -T}
void e() {
    // 调用t函数
    t();
    while ((ch == '+') || (ch == '-')) {
        // 读下一个单词或符号
        ch = prog[progIndex++];
        // 调用 T 函数
        t();
    }
}

// T -> F{*F | /F}
void t() {
    // 调用 f 函数
    f();
    while ((ch == '*') || (ch == '/')) {
        // 读下一个单词符号
        ch = prog[progIndex++];
        // 调用 F 函数
        f();
    }
}


// F -> (E)|a|b|c
void f() {
    if (ch == 'a' || ch == 'b' || ch == 'c') {
        // 读下一个单词符号
        ch = prog[progIndex++];
    } else if (ch == '(') {
        // 读下一个单词符号
        ch = prog[progIndex++];
        e();
        if (ch == ')') {
            // 读下一个单词符号
            ch = prog[progIndex++];
        } else {
            isSuccess = 0;
        }
    } else {
        isSuccess = 0;
    }
}

} // Namespace cpe2 End
