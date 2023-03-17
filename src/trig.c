/**
 * Copyright (C) 2023 Suhas Guddeti
 * This file is part of TrigApproxLERP, which is licensed under the MIT license.
 * For more details, see ./license or write <suhas8@outlook.com>.
 */

#include "TrigApproxLERP.h"

#define PLTdefault(...) populateLookupTable(0.02, 0.01, 0.01)

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

double **populateLookupTable(double incrementer, double decrementer, double threshold) {
    int rows = 0;
    double **arr = NULL;

    addValue(&arr, 0, 0, &rows);
    if (incrementer > 30) {
        printf("WARNING: The incrementer will be too large to produce meaningful values between 0 and %f. Please decrease the incrementer to less than 30!\n", incrementer);
        exit(1);
    }
    if (decrementer >= incrementer) {
        printf("WARNING: The decrementer will be larger than the incrementer. Please decrease the decrementer to less than the incrementer!\n");
        exit(1);
    }
    if (threshold >= 1 || threshold <= 0) {
        printf("WARNING: The threshold must be between 0 and 1. Please enter a valid threshold!\n");
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
    int len = 0;
    while (arr[len] != NULL && arr[len][0] < angle) {
        len++;
    }
    if (fabs(arr[len][0] - angle) < 1E-5) {
        return negate ? -1 * arr[len][1] : arr[len][1];
    }
    double slope = (arr[len][1] - arr[len - 1][1]) / (arr[len][0] - arr[len - 1][0]);
    double answer = negate ? -1 * (arr[len - 1][1] + (slope * (angle - arr[len - 1][0]))) : arr[len - 1][1] + (slope * (angle - arr[len - 1][0]));
    return answer;
}

double lookupInv(double **arr, double ratio) {
    int len = 0;
    int negate = 0;
    if (ratio < 0) {
        negate = 1;
        ratio = 0 - ratio;
    }
    while (arr[len] != NULL && arr[len][1] < ratio) {
        len++;
    }
    if (arr[len][1] - ratio < 1E-5) {
        if (negate) {
            return 360 - arr[len][0];
        } else {
            return arr[len][0];
        }
    }
    double slope = (arr[len][0] - arr[len - 1][0]) / (arr[len][1] - arr[len - 1][1]);
    double answer = negate ? 360 - (arr[len - 1][0] + (slope * (ratio - arr[len - 1][1]))) : arr[len - 1][0] + (slope * (ratio - arr[len - 1][1]));
    return answer;
}

double approxSin(double angle) {
    double **arr = PLTdefault();
    return lookup(arr, angle);
}

double approxSinCustom(double angle, double incrementer, double decrementer, double threshold) {
    double **arr = populateLookupTable(incrementer, threshold, decrementer);
    return lookup(arr, angle);
}

double approxSinWithTable(double **arr, double angle) {
    return lookup(arr, angle);
}

double approxInvSin(double ratio) {
    assert(ratio >= -1 && ratio <= 1);
    double **arr = PLTdefault();
    return lookupInv(arr, ratio);
}

double approxInvSinCustom(double ratio, double incrementer, double decrementer, double threshold) {
    double **arr = populateLookupTable(incrementer, threshold, decrementer);
    return lookupInv(arr, ratio);
}

double approxInvSinWithTable(double **arr, double ratio) {
    return lookupInv(arr, ratio);
}

double approxCos(double angle) {
    return approxSin(angle + 90);
}

double approxCosCustom(double angle, double incrementer, double decrementer, double threshold) {
    return approxSinCustom(angle + 90, incrementer, decrementer, threshold);
}

double approxCosWithTable(double **arr, double angle) {
    return approxSinWithTable(arr, angle + 90);
}

double approxInvCos(double ratio) {
    assert(ratio >= -1 && ratio <= 1);
    double answer = 90 - approxInvSin(ratio);
    if (answer < 0)
        answer = 360 - (0 - answer);
    return answer;
}

double approxInvCosCustom(double ratio, double incrementer, double decrementer, double threshold) {
    assert(ratio >= -1 && ratio <= 1);
    double answer = 90 - approxInvSinCustom(ratio, incrementer, decrementer, threshold);
    if (answer < 0)
        answer = 360 - (0 - answer);
    return answer;
}

double approxInvCosWithTable(double **arr, double ratio) {
    assert(ratio >= -1 && ratio <= 1);
    double answer = 90 - approxInvSinWithTable(arr, ratio);
    if (answer < 0)
        answer = 360 - (0 - answer);
    return answer;
}

double approxTan(double angle) {
    double cos = approxCos(angle);
    assert(fabs(cos) != 0);
    return approxSin(angle) / cos;
}

double approxTanCustom(double angle, double incrementer, double decrementer, double threshold) {
    double cos = approxCosCustom(angle, incrementer, decrementer, threshold);
    assert(fabs(cos) != 0);
    return approxSinCustom(angle, incrementer, decrementer, threshold) / cos;
}

double approxTanWithTable(double **arr, double angle) {
    double cos = approxCosWithTable(arr, angle);
    assert(fabs(cos) != 0);
    return approxSinWithTable(arr, angle) / cos;
}

double approxInvTan(double ratio) {
    double answer = approxInvSin(ratio / sqrt(1 + ratio * ratio));
    if (answer < 0)
        answer = 360 - (0 - answer);
    return answer;
}

double approxInvTanCustom(double ratio, double incrementer, double decrementer, double threshold) {
    double answer = approxInvSinCustom(ratio / sqrt(1 + ratio * ratio), incrementer, decrementer, threshold);
    if (answer < 0)
        answer = 360 - (0 - answer);
    return answer;
}

double approxInvTanWithTable(double **arr, double ratio) {
    double answer = approxInvSinWithTable(arr, ratio / sqrt(1 + ratio * ratio));
    if (answer < 0)
        answer = 360 - (0 - answer);
    return answer;
}