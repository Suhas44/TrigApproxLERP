/**
 * Copyright (C) 2023 Suhas Guddeti
 * This file is part of TrigApproxLERP, which is licensed under the MIT license.
 * For more details, see ./license or write <suhas8@outlook.com>.
 */

#include "TrigApproxLERP.h"

#define PLT(...) populateLookupTable(5, 0.01, 0.001)

double approxSin(double angle) {
    double **arr = PLT();
    return lookup(angle, arr);
}

double approxSinCustom(double angle, double incrementer, double threshold, double decrementer) {
    double **arr = populateLookupTable(incrementer, threshold, decrementer);
    return lookup(angle, arr);
}

double calcSin(double angle) {
    return sin(angle * (M_PI / 180));
}

double **populateLookupTable(double incrementer, double threshold, double decrementer) {
    int rows = 0;
    double **arr = NULL;

    addValue(&arr, 0, 0, &rows);
    if (incrementer > 30) {
        printf("WARNING: The incrementer will be too large to produce meaningful values between sin(0) and sin(%f). Please decrease the incrementer to less than 30!\n", incrementer);
        exit(1);
    }
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
    return arr;
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

double lookup(double gAngle, double **arr) {
    double angle = (int)gAngle % 360 + (gAngle - (int)gAngle);
    int negate = 0;
    if (angle < 0)
        angle = 360 + angle;
    if (angle > 90 && angle <= 180) {
        angle = 180 - angle;
    } else if (angle > 180 && angle <= 270) {
        angle = angle - 180;
        negate = 1;
    } else if (angle > 270 && angle < 360) {
        angle = 360 - angle;
        negate = 1;
    }
    if (angle == 90)
        return 1;
    int len = 0;
    while (arr[len] != NULL && arr[len][0] < angle) {
        len++;
    }
    double slope = (arr[len][1] - arr[len - 1][1]) / (arr[len][0] - arr[len - 1][0]);
    double answer = negate ? -1 * arr[len - 1][1] + (slope * (angle - arr[len][0])) : arr[len - 1][1] + (slope * (angle - arr[len][0]));
    return answer;
}