//
// Created by michael tsui on 2019-11-10.
//

#include <stdio.h>
#include <string.h>

namespace cpe1_ugly {


char prog[80];
int progIndex;
char *rwtab[6] = {"begin", "if", "then", "while", "do", "end"};

const int SYN_ERROR = -1;
const int SYN_EXIT = 0;
const int SYN_NUM = 11;
const int SYN_VARIABLE = 10;
const int SYN_PLUS = 13;
const int SYN_MINUS = 14;
const int SYN_MULTIPLY = 15;
const int SYN_DIVISION = 16;
const int SYN_COLON = 17;
const int SYN_COLON_EQ = 18;
const int SYN_LESS = 20;
const int SYN_LESS_GT = 21;
const int SYN_LESS_EQ = 22;
const int SYN_GREATER = 23;
const int SYN_GREATER_EQ = 24;
const int SYN_EQUAL = 25;
const int SYN_SEMICOLON = 26;
const int SYN_LEFT_PARENTHESIS = 27;
const int SYN_RIGHT_PARENTHESIS = 28;

int syn, sum;
char token[8];

void setToken(int newSyn, char *newToken, int newSum) {
    syn = newSyn;
    sum = newSum;
    strcpy(token, newToken);
}

bool CharIsLetter(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

bool CharIsDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

int GetKeywordSyn(char *token) {
    for (int n = 0; n < 6; n++) {
        if (strcmp(token, rwtab[n]) == 0) {
            return n + 1;
        }
    }

    return 0;
}

void scanner() {
    char token[8], ch;
    int tokenIndex = 0, sum = 0;

    for (int n = 0; n < 8; n++)
        token[n] = 0;

    ch = prog[progIndex++];
    while (ch == ' ' || ch == '\n')
        ch = prog[progIndex++];

    if (ch == 0 || ch == '#') {
        setToken(SYN_EXIT, "", 0);
        return;
    }

    if (CharIsLetter(ch)) {
        while (CharIsDigit(ch) || CharIsLetter(ch)) {
            token[tokenIndex++] = ch;
            ch = prog[progIndex++];
        }
        progIndex--;

        int keywordSyn = GetKeywordSyn(token);
        if (keywordSyn == 0) {
            setToken(SYN_VARIABLE, token, 0);
            return;
        } else {
            setToken(keywordSyn, token, 0);
            return;
        }
    }

    if (CharIsDigit(ch)) {
        while (CharIsDigit(ch)) {
            sum = sum * 10 + ch - '0';
            ch = prog[progIndex++];
        }
        progIndex--;
        setToken(SYN_NUM, "", sum);
        return;
    } else {
        switch (ch) {
            case '<':
                tokenIndex = 0;
                token[tokenIndex++] = ch;
                ch = prog[progIndex++];
                if (ch == '>') {
                    token[tokenIndex] = ch;
                    setToken(SYN_LESS_GT, token, 0);
                    return;
                } else if (ch == '=') {
                    token[tokenIndex] = ch;
                    setToken(SYN_LESS_EQ, token, 0);
                    return;
                } else {
                    progIndex--;
                    setToken(SYN_LESS, token, 0);
                    return;
                }
            case '>':
                tokenIndex = 0;
                token[tokenIndex++] = ch;
                ch = prog[progIndex++];
                if (ch == '=') {
                    token[tokenIndex] = ch;
                    setToken(SYN_GREATER_EQ, token, 0);
                    return;
                } else {
                    progIndex--;
                    setToken(SYN_GREATER, token, 0);
                    return;
                }
            case ':':
                tokenIndex = 0;
                token[tokenIndex++] = ch;
                ch = prog[progIndex++];
                if (ch == '=') {
                    token[tokenIndex] = ch;
                    setToken(SYN_COLON_EQ, token, 0);
                    return;
                } else {
                    progIndex--;
                    setToken(SYN_COLON, token, 0);
                    return;
                }
            case '+':
                token[0] = ch;
                setToken(SYN_PLUS, token, 0);
                return;
            case '-':
                token[0] = ch;
                setToken(SYN_MINUS, token, 0);
                return;
            case '*':
                token[0] = ch;
                setToken(SYN_MULTIPLY, token, 0);
                return;
            case '/':
                token[0] = ch;
                setToken(SYN_DIVISION, token, 0);
                return;
            case '=':
                token[0] = ch;
                setToken(SYN_EQUAL, token, 0);
                return;
            case ';':
                token[0] = ch;
                setToken(SYN_SEMICOLON, token, 0);
                return;
            case '(':
                token[0] = ch;
                setToken(SYN_LEFT_PARENTHESIS, token, 0);
                return;
            case ')':
                token[0] = ch;
                setToken(SYN_RIGHT_PARENTHESIS, token, 0);
                return;
            default:
                setToken(SYN_ERROR, "", 0);
                return;
        }
    }
}

int main() {
    // for #
    // (10,for)
    char ch;

    progIndex = 0;
    printf("Please input string:\n");
    do {
        ch = (char) getchar();
        prog[progIndex++] = ch;
    } while (ch != '#');
    prog[progIndex] = 0;
    progIndex = 0;
    for (;;) {
        scanner();
        if (syn == SYN_EXIT) {
            break;
        }
        switch (syn) {
            case SYN_NUM:
                printf("(%2d,%8d)\n", syn, sum);
                break;
            case SYN_ERROR:
                printf("Input Error\n");
                break;
            default:
                printf("(%2d,%8s)\n", syn, token);
        }
    }

    return 0;
}

}// Namespace cpe1 End
