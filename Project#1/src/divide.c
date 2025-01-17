
#define _CRT_SECURE_NO_WARNINGS    // strtok 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <string.h>    // strtok 함수가 선언된 헤더 파일
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#define SIZE 100


void insert(int list[], int cnt, int size)    // insert 함수를 만들어서 값을 복사한 후 뒤쪽에 붙임.
{
    for (int i = 0; i < cnt; i++) {
        for (int j = size - 1; j >= 0; j--) {
            list[j + 1] = list[j];
            list[j] = 0;
        }
    }
}


int main() {
    int num1RNum = 0, num2RNum = 0;
    int newNum1[SIZE] = { 0 };
    int newNum2[SIZE] = { 0 };
    char num1[SIZE];
    char num2[SIZE];

    printf("Please enter the floating number : ");
    scanf(" %s", num1);
    printf("Please enter the floating number : ");
    scanf(" %s", num2);

    int resSign = 1;

    if (num1[0] == '-') {
        for (int i = 1; i < strlen(num1); i++) {
            num1[i - 1] = num1[i];
        }
        num1[strlen(num1) - 1] = NULL;
        resSign *= -1;
    }
    if (num2[0] == '-') {
        for (int i = 1; i < strlen(num2); i++) {
            num2[i - 1] = num2[i];
        }
        resSign *= -1;
        num2[strlen(num2) - 1] = NULL;
    }



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

    for (int i = 0; i < strlen(num1) - num1RNum; i++) {
        newNum1[i] = num1[i] - 48;
    }
    for (int i = strlen(num1) - 1; i > strlen(num1) - num1RNum; i--) {
        newNum1[i - 1] = num1[i] - 48;
    }

    for (int i = 0; i < strlen(num2) - num2RNum; i++) {
        newNum2[i] = num2[i] - 48;
    }
    for (int i = strlen(num2) - 1; i > strlen(num2) - num2RNum; i--) {
        newNum2[i - 1] = num2[i] - 48;
    }


    // 자릿수가 다르면 인덱스 0 에 0 추가
    if (strlen(num1) - num1RNum < strlen(num2) - num2RNum) {
        int cnt = (strlen(num2) - num2RNum) - (strlen(num1) - num1RNum);
        insert(newNum1, cnt, strlen(num1) - 1);

    }
    else if (strlen(num1) - num1RNum > strlen(num2) - num2RNum) {
        int cnt = (strlen(num1) - num1RNum) - (strlen(num2) - num2RNum);
        insert(newNum2, cnt, strlen(num1) - 1);

    }

    int reNum1[SIZE] = { NULL };
    int reNum2[SIZE] = { NULL };

    for (int i = 0; i <= SIZE - 1; i++) {
        reNum1[i] = newNum1[SIZE - 1 - i];
    }
    for (int i = 0; i <= SIZE - 1; i++) {
        reNum2[i] = newNum2[SIZE - 1 - i];
    }

    // 나누기
    int subRes[SIZE] = { 0 };
    int temp[SIZE] = { 0 };
    int divRes[SIZE] = { NULL };
    int tempzeroLength;
    int num2zeroLength;
    int subCompare;
    int cnt;
    int switchNum2[SIZE] = { 0 };

    for (int i = 0; i < SIZE; i++) {
        temp[i] = reNum1[i];
    }
    for (int i = 0; i < SIZE; i++) {
        cnt = 0;

        while (1) {

            tempzeroLength = SIZE - 1;
            num2zeroLength = SIZE - 1;
            while (temp[tempzeroLength] == 0) { tempzeroLength--; }
            while (reNum2[num2zeroLength] == 0) { num2zeroLength--; }

            if (tempzeroLength == num2zeroLength) {
                subCompare = tempzeroLength;
                while (temp[subCompare] >= reNum2[subCompare]) {
                    subCompare--;
                }
                if (subCompare < tempzeroLength) {}
                else { break; }
            }
            else if (tempzeroLength < num2zeroLength) { break; }

            for (int n = 0; n <= SIZE - 1; n++) {
                subRes[n] = temp[n] - reNum2[n];
            }
            for (int n = 0; n <= SIZE - 1; n++) {
                if (n != SIZE - 1 && subRes[n] < 0) {
                    subRes[n + 1] -= 1;
                    subRes[n] += 10;
                }
            }

            int zero = 0;

            if (subRes[SIZE - 1] < 0) {
                break;
            }
            for (int n = 0; n < SIZE; n++) {
                temp[n] = subRes[n];
                if (temp[n] == 0) {
                    zero += 1;
                }
            }
            if (zero == SIZE) {
                cnt += 1;
                break;
            }
            else {
                cnt += 1;
            }


        }
        int zero = 0;

        divRes[i] = cnt;
        for (int j = 1; j < SIZE; j++) {
            reNum2[j - 1] = reNum2[j];
        }
        if (reNum2[SIZE - 1] != 0) {
            reNum2[SIZE - 1] = 0;
        }
        for (int n = 0; n < SIZE; n++) {
            if (reNum2[n] == 0) {
                zero += 1;
            }
        }
        if (zero == SIZE) {
            cnt += 1;
            break;
        }
        else {
            cnt += 1;
        }

    }


    int size = SIZE - 1;
    int zeroNum = 0;
    printf("Result (div) : ");
    while (divRes[size] == 0) {
        zeroNum += 1;
        size--;
    }
    int existNum = SIZE - zeroNum;
    if (resSign < 0) {
        printf("-");
    }
    printf("%d", divRes[0]);
    printf(".");
    for (int i = 1; i < existNum; i++)
        printf("%d", divRes[i]);

    return 0;

}