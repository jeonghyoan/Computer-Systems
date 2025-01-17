#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <float.h>
#include <string.h>
#define SIZE 100

int main() {
    int num1zeroLength = SIZE - 1;
    int num2zeroLength = SIZE - 1;
    int subCompare;

    char num1[SIZE];
    char num2[SIZE];

    printf("Please enter the floating number : ");
    scanf(" %s", num1);
    printf("Please enter the floating number : ");
    scanf(" %s", num2);

    int num1Sign = 1;
    int num2Sign = 1;
    int resSign = 1;

    if (num1[0] == '-') {
        for (int i = 1; i < strlen(num1); i++) {
            num1[i - 1] = num1[i];
        }
        num1[strlen(num1) - 1] = NULL;
        num1Sign *= -1;
    }
    if (num2[0] == '-') {
        for (int i = 1; i < strlen(num2); i++) {
            num2[i - 1] = num2[i];
        }
        num2Sign *= -1;
        num2[strlen(num2) - 1] = NULL;
    }

    char* sepNum1[2] = { NULL, };
    char* token1 = strtok(num1, ".");

    sepNum1[0] = token1;
    token1 = strtok(NULL, ".");
    sepNum1[1] = token1;

    char* sepNum2[2] = { NULL, };
    char* token2 = strtok(num2, ".");

    sepNum2[0] = token2;
    token2 = strtok(NULL, ".");
    sepNum2[1] = token2;

    //num1 정수부
    int i = 0, j = 1;
    int num1L[SIZE];

    while (sepNum1[0][i] != NULL) {
        i++;
    }

    for (j; j <= i; j++) {
        num1L[i - j] = sepNum1[0][j - 1] - 48;
    }

    if (i != SIZE) {
        for (i; i <= SIZE - 1; i++) {
            num1L[i] = 0;
        }
    }

    //num1 소수부
    i = 0, j = 1;
    int num1R[SIZE];

    while (sepNum1[1][i] != NULL) {
        i++;
    }
    for (j; j <= i; j++) {
        num1R[SIZE - j] = sepNum1[1][j - 1] - 48;
    }
    i = 0;
    if (j != SIZE) {
        for (i; i <= SIZE - j; i++) {
            num1R[i] = 0;
        }
    }

    //num2 정수부
    i = 0, j = 1;
    int num2L[SIZE];

    while (sepNum2[0][i] != NULL) {
        i++;
    }

    for (j; j <= i; j++) {
        num2L[i - j] = sepNum2[0][j - 1] - 48;
    }

    if (i != SIZE) {
        for (i; i <= SIZE - 1; i++) {
            num2L[i] = 0;
        }
    }

    //num2 소수부
    i = 0, j = 1;
    int num2R[SIZE];

    while (sepNum2[1][i] != NULL) {
        i++;
    }
    for (j; j <= i; j++) {
        num2R[SIZE - j] = sepNum2[1][j - 1] - 48;
    }
    i = 0;
    if (j != SIZE) {
        for (i; i <= SIZE - j; i++) {
            num2R[i] = 0;
        }
    }

    //sub
    int subResR[SIZE];
    int subResL[SIZE];
    if (num1Sign < 0 && num2Sign < 0) { // num1, num2 모두 음수일때
        while (num1L[num1zeroLength] == 0) { num1zeroLength--; }
        while (num2L[num2zeroLength] == 0) { num2zeroLength--; }

        if (num2zeroLength > num1zeroLength) {
            resSign = 1;
        }
        else if (num2zeroLength == num1zeroLength) {
            subCompare = num2zeroLength;
            while (num2L[subCompare] >= num1L[subCompare]) {
                subCompare--;
            }
            if (subCompare < num2zeroLength) { resSign = 1; }
            else { resSign = -1; }
        }
        else { resSign = -1; }

        if (resSign == 1) {
            for (int n = 0; n <= SIZE - 1; n++) {
                subResR[n] = num2R[n] - num1R[n];
                if (n != SIZE - 1 && subResR[n] < 0) {
                    num2R[n + 1] -= 1;
                    subResR[n] += 10;
                }
                else if (n == SIZE - 1 && subResR[n] < 0) {
                    num2L[0] -= 1;
                    subResR[n] += 10;
                }
            }
            if (num2L[0] == -1) {
                num2L[1] -= 1;
                num2L[0] += 10;
            }
            for (int n = 0; n <= SIZE - 1; n++) {
                subResL[n] = num2L[n] - num1L[n];
                if (n != SIZE - 1 && subResL[n] < 0) {
                    num2L[n + 1] -= 1;
                    subResL[n] += 10;
                }
            }
        }
        else {
            for (int n = 0; n <= SIZE - 1; n++) {
                subResR[n] = num1R[n] - num2R[n];
                if (n != SIZE - 1 && subResR[n] < 0) {
                    num1R[n + 1] -= 1;
                    subResR[n] += 10;
                }

                else if (n == SIZE - 1 && subResR[n] < 0) {
                    num1L[0] -= 1;
                    subResR[n] += 10;
                }
            }
            if (num1L[0] == -1) {
                num1L[1] -= 1;
                num1L[0] += 10;
            }

            for (int n = 0; n <= SIZE - 1; n++) {
                subResL[n] = num1L[n] - num2L[n];
                if (n != SIZE - 1 && subResL[n] < 0) {
                    num1L[n + 1] -= 1;
                    subResL[n] += 10;
                }
            }
        }
    }
    else if (num2Sign < 0) { // num2가 음수일때
        for (int n = 0; n <= SIZE - 1; n++) {
            subResR[n] = num1R[n] + num2R[n];
            if (n != SIZE - 1 && subResR[n] >= 10) {
                num1R[n + 1] += 1;
                subResR[n] -= 10;
            }
            else if (n == SIZE - 1 && subResR[n] >= 10) {
                num1L[0] += 1;
                subResR[n] -= 10;
            }
        }
        for (int n = 0; n <= SIZE - 1; n++) {
            subResL[n] = num1L[n] + num2L[n];
            if (n != SIZE - 1 && subResL[n] >= 10) {
                num1L[n + 1] += 1;
                subResL[n] -= 10;
            }
        }
        resSign = 1;
    }
    else if (num1Sign < 0) { // num1이 음수일때
        for (int n = 0; n <= SIZE - 1; n++) {
            subResR[n] = num1R[n] + num2R[n];
            if (n != SIZE - 1 && subResR[n] >= 10) {
                num1R[n + 1] += 1;
                subResR[n] -= 10;
            }
            else if (n == SIZE - 1 && subResR[n] >= 10) {
                num1L[0] += 1;
                subResR[n] -= 10;
            }
        }
        for (int n = 0; n <= SIZE - 1; n++) {
            subResL[n] = num1L[n] + num2L[n];
            if (n != SIZE - 1 && subResL[n] >= 10) {
                num1L[n + 1] += 1;
                subResL[n] -= 10;
            }
        }
        resSign = -1;
    }
    else { // num1, num2 모두 양수일때
        while (num1L[num1zeroLength] == 0) { num1zeroLength--; }
        while (num2L[num2zeroLength] == 0) { num2zeroLength--; }

        if (num1zeroLength > num2zeroLength) {
            resSign = 1;
        }
        else if (num1zeroLength == num2zeroLength) {
            subCompare = num1zeroLength;
            while (num1L[subCompare] >= num2L[subCompare]) {

                subCompare--;
            }
            if (subCompare < num1zeroLength) { resSign = 1; }
            else { resSign = -1; }
        }
        else { resSign = -1; }


        if (resSign == 1) {
            for (int n = 0; n <= SIZE - 1; n++) {
                subResR[n] = num1R[n] - num2R[n];
                if (n != SIZE - 1 && subResR[n] < 0) {
                    num1R[n + 1] -= 1;
                    subResR[n] += 10;
                }
                else if (n == SIZE - 1 && subResR[n] < 0) {
                    num1L[0] -= 1;
                    subResR[n] += 10;
                }
            }
            if (num1L[0] == -1) {
                num1L[1] -= 1;
                num1L[0] += 10;
            }
            for (int n = 0; n <= SIZE - 1; n++) {
                subResL[n] = num1L[n] - num2L[n];
                if (n != SIZE - 1 && subResL[n] < 0) {
                    num1L[n + 1] -= 1;
                    subResL[n] += 10;
                }
            }
        }
        else {
            for (int n = 0; n <= SIZE - 1; n++) {
                subResR[n] = num2R[n] - num1R[n];
                if (n != SIZE - 1 && subResR[n] < 0) {
                    num2R[n + 1] -= 1;
                    subResR[n] += 10;
                }
                if (num2L[0] == -1) {
                    num2L[1] -= 1;
                    num2L[0] += 10;
                }
                else if (n == SIZE - 1 && subResR[n] < 0) {
                    num2L[0] -= 1;
                    subResR[n] += 10;
                }
            }

            for (int n = 0; n <= SIZE - 1; n++) {
                subResL[n] = num2L[n] - num1L[n];
                if (n != SIZE - 1 && subResL[n] < 0) {
                    num2L[n + 1] -= 1;
                    subResL[n] += 10;
                }
            }
        }

    }

    // 빼기 결과 출력
    int zeroLength = SIZE - 1;
    printf("Result (sub) : ");

    if (resSign < 0) {
        printf("-");
    }
    while (subResL[zeroLength] == 0) { zeroLength--; }
    for (int n = zeroLength; n >= 0; n--) { printf("%d", subResL[n]); }
    printf(".");

    zeroLength = 0;
    while (subResR[zeroLength] == 0) { zeroLength++; }
    for (int n = SIZE - 1; n >= zeroLength; n--) { printf("%d", subResR[n]); }
    printf("0\n");

    return 0;

}