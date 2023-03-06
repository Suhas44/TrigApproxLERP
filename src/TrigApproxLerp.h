/**
 * Copyright (C) 2023 Suhas Guddeti
 * This file is part of TrigApproxLERP, which is licensed under the MIT license.
 * For more details, see ./license or write <suhas8@outlook.com>.
 */

#ifndef LERP_H
#define LERP_H
double calcSin(float angle);
void populateLookupTable(int incrementer, float threshold, float decrementer);
double approxSin(float angle);
void addValue(double ***old_array, double degree, double sin, int *rows);
#endif
