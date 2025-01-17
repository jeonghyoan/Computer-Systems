#define _CRT_SECURE_NO_WARNINGS    // strtok 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <string.h>    // strtok 함수가 선언된 헤더 파일
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#define SIZE 100

int main() {
    int num1RNum = 0, num2RNum = 0;
    int newNum1[SIZE] = { NULL };
    int newNum2[SIZE] = { NULL };

    char num1[SIZE];
    char num2[SIZE];

    printf("Please enter the floating number : ");
    scanf(" %s", num1);
    printf("Please enter the floating number : ");
    scanf(" %s", num2);

    int sign = 1;

    if (num1[0] == '-') {
        for (int i = 1; i < strlen(num1); i++) {
            num1[i - 1] = num1[i];
        }
        num1[strlen(num1) - 1] = NULL;
        sign *= -1;
    }
    if (num2[0] == '-') {
        for (int i = 1; i < strlen(num2); i++) {
            num2[i - 1] = num2[i];
        }
        sign *= -1;
        num2[strlen(num2) - 1] = NULL;
    }

    int mulRes[SIZE * 2] = { 0 };

    for (int i = strlen(num1); i >= 0; i--) {
        if (num1[i] != '.') {
            num1RNum += 1;
        }
        else {
            break;
        }
    }

    for (int i = strlen(num2); i >= 0; i--) {
        if (num2[i] != '.') {
            num2RNum += 1;
        }
        else {
            break;
        }
    }

    int resRNum = num1RNum + num2RNum - 2;



    for (int i = 0; i < strlen(num1) - num1RNum; i++) {
        newNum1[i] = num1[i] - 48;
    }
    for (int i = strlen(num1)-2; i >= strlen(num1) - num1RNum; i--) {
        newNum1[i] = num1[i+1] - 48;
    }

    for (int i = 0; i < strlen(num2) - num2RNum; i++) {
        newNum2[i] = num2[i] - 48;
    }
    for (int i = strlen(num2) - 2; i >= strlen(num2) - num2RNum; i--) {
        newNum2[i] = num2[i + 1] - 48;
    }

    for (int i = strlen(num1) - 2; i >= 0; i--)
    {
        for (int j = strlen(num2) - 2; j >= 0; j--)
        {
            mulRes[i + j] += newNum1[i] * newNum2[j];
        }

    }

    for (int i = strlen(num1) + strlen(num2) - 4; i > 0; i--)
    {
        if (mulRes[i] >= 10) {
            mulRes[i - 1] += mulRes[i] / 10;
            mulRes[i] %= 10;
        }
    }
    
    printf("Result (mult) : ");
    
    int existNum = strlen(num1) + strlen(num2) - 4;
    if (sign < 0) {
        printf("-");
    }
    for (int i = 0; i <= existNum - resRNum; i++)
        printf("%d", mulRes[i]);
    printf(".");
    for (int i = existNum - resRNum + 1; i <= existNum; i++)
        printf("%d", mulRes[i]);

    return 0;

}