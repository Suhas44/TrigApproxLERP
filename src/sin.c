/**
 * Copyright (C) 2023 Suhas Guddeti
 * This file is part of TrigApproxLERP, which is licensed under the MIT license.
 * For more details, see ./license or write <suhas8@outlook.com>.
 */

#include "TrigApproxLERP.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLT(...) populateLookupTable(5, 0.01, 0.05)

int main() {
    PLT();
}

double calcSin(float angle) {
    return sin(angle * (M_PI / 180));
}

void populateLookupTable(int incrementer, float threshold, float decrementer) {
    int rows = 0;
    double **arr = NULL;

    addValue(&arr, 0, 0, &rows);
    addValue(&arr, incrementer, calcSin(incrementer), &rows);

    addValue(&arr, 6, calcSin(6), &rows);
    addValue(&arr, 7, calcSin(7), &rows);
    addValue(&arr, 8, calcSin(8), &rows);

    for (int i = 0; i < rows; i++) {
        printf("[");
        for (int j = 0; j < 2; j++) {
            printf("%f,", arr[i][j]);
        }
        printf("]\n");
    }
};

void addValue(double ***old_array, double degree, double sin, int *rows) {
    double new_row[2] = {degree, sin};
    (*rows)++;
    *old_array = realloc(*old_array, *rows * sizeof(double *));
    (*old_array)[*rows - 1] = malloc(2 * sizeof(double));
    memcpy((*old_array)[*rows - 1], new_row, 2 * sizeof(double));
}

double approxSin(float angle);