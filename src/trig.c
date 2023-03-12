/**
 * Copyright (C) 2023 Suhas Guddeti
 * This file is part of TrigApproxLERP, which is licensed under the MIT license.
 * For more details, see ./license or write <suhas8@outlook.com>.
 */

#include "TrigApproxLERP.h"

#define PLTdefault(...) populateLookupTable(0.01, 0.01, 0.005)

double calcSin(double angle) {
    return sin(angle * (M_PI / 180));
}

int isThresholdMet(double **arr, double curr, int incrementer, double threshold, int rows) {
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

double lookup(double **arr, double angle) {
    angle = (int)angle % 360 + (angle - (int)angle);
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
    if (angle == 0)
        return 0;
    int len = 0;
    while (arr[len] != NULL && arr[len][0] < angle) {
        len++;
    }
    if (fabs(arr[len - 1][0] - angle) < 1E-5) {
        return arr[len - 1][1];
    }
    double slope = (arr[len][1] - arr[len - 1][1]) / (arr[len][0] - arr[len - 1][0]);
    double answer = negate ? -1 * arr[len - 1][1] + (slope * (angle - arr[len][0])) : arr[len - 1][1] + (slope * (angle - arr[len][0]));
    return answer;
}

double **populateLookupTable(double incrementer, double decrementer, double threshold) {
    int rows = 0;
    double **arr = NULL;

    addValue(&arr, 0, 0, &rows);
    if (incrementer > 30) {
        printf("WARNING: The incrementer will be too large to produce meaningful values between 0 and %f. Please decrease the incrementer to less than 30!\n", incrementer);
        exit(1);
    }
    addValue(&arr, incrementer, calcSin(incrementer), &rows);
    double curr = 2 * incrementer;
    while (incrementer > 0 && curr < 90) {
        if (isThresholdMet(arr, curr, incrementer, threshold, rows)) {
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

double approxSin(double angle) {
    double **arr = PLTdefault();
    return lookup(arr, angle);
}

double approxSinCustom(double angle, double incrementer, double decrementer, double threshold) {
    double **arr = populateLookupTable(incrementer, threshold, decrementer);
    return lookup(arr, angle);
}

double approxCos(double angle) {
    return approxSin(angle + 90);
}

double approxCosCustom(double angle, double incrementer, double decrementer, double threshold) {
    return approxSinCustom(angle + 90, incrementer, decrementer, threshold);
}

double approxTan(double angle) {
    double cos = approxCos(angle);
    assert(fabs(cos) != 0);
    return approxSin(angle) / cos;
}

double approxTanCustom(double angle, double incrementer, double decrementer, double threshold) {
    double cos = approxCosCustom(angle, incrementer, decrementer, threshold);
    assert(fabs(cos) != 0);
    return approxSinCustom(angle, incrementer, decrementer, threshold) / approxCosCustom(angle, incrementer, decrementer, threshold);
}