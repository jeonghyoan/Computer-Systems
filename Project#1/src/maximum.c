#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <float.h>
#include <string.h>
#define SIZE 100

int show_maximumDouble() {
	double doubleMax = DBL_MAX;
	printf("The largest double value : %f\n\n", doubleMax);
	return 0;
}

int howToStoreinDouble() {
	double exDouble = 121212121212121212121212.1212121212121212;

	printf("The way how to represent(double) : %f \n", exDouble);

	return 0;
}

void main() {
	show_maximumDouble();
	howToStoreinDouble();
}