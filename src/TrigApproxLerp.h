/**
 * Copyright (C) 2023 Suhas Guddeti
 * This file is part of TrigApproxLERP, which is licensed under the MIT license.
 * For more details, see ./license or write <suhas8@outlook.com>.
 */

#ifndef LERP_H
#define LERP_H
double calcSin(double angle);
void populateLookupTable(double incrementer, double threshold, double decrementer);
void continualAddition(double **arr, int *rows, double *incrementer, double *curr, double decrementer, double threshold);
int isThresholdMet(double curr, double **arr, int rows, int incrementer, double threshold);
void addValue(double ***old_array, double degree, double sin, int *rows);
#endif
