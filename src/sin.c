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

#define PLT(...) populateLookupTable(5, 0.01, 0.001)

int main() {
    PLT();
}

double calcSin(double angle) {
    return sin(angle * (M_PI / 180));
}

void populateLookupTable(double incrementer, double threshold, double decrementer) {
    int rows = 0;
    double **arr = NULL;

    addValue(&arr, 0, 0, &rows);
    addValue(&arr, incrementer, calcSin(incrementer), &rows);
    double curr = 2 * incrementer;
    while (incrementer > 0.01 && curr < 90) {
        if (isThresholdMet(curr, arr, rows, incrementer, threshold)) {
            addValue(&arr, curr, calcSin(curr), &rows);
            curr += incrementer;
        } else {
            curr -= incrementer;
            incrementer -= decrementer;
            curr += incrementer;
        }
    }
    addValue(&arr, 90, 1, &rows);
};

int isThresholdMet(double curr, double **arr, int rows, int incrementer, double threshold) {
    double slope1 = (calcSin(curr) - arr[rows - 1][1]) / (curr - arr[rows - 1][0]);
    double slope2 = (arr[rows - 1][1] - arr[rows - 2][1]) / (arr[rows - 1][0] - arr[rows - 2][0]);
    double percentDiff = 1 - (slope1 / slope2);
    return fabs(percentDiff) < threshold;
}
void addValue(double ***old_array, double degree, double sin, int *rows) {
    double new_row[2] = {degree, sin};
    (*rows)++;
    *old_array = realloc(*old_array, *rows * sizeof(double *));
    (*old_array)[*rows - 1] = malloc(2 * sizeof(double));
    memcpy((*old_array)[*rows - 1], new_row, 2 * sizeof(double));
}

double approxSin(double angle);