/**
 * Copyright (C) 2023 Suhas Guddeti
 * This file is part of TrigApproxLERP, which is licensed under the MIT license.
 * For more details, see ./license or write <suhas8@outlook.com>.
 */

#ifndef LERP_H
#define LERP_H

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double **populateLookupTable(double incrementer, double decrementer, double threshold);
double approxSin(double angle);
double approxSinCustom(double angle, double incrementer, double decrementer, double threshold);
double approxSinWithTable(double **arr, double angle);
double approxInvSin(double angle);
double approxInvSinCustom(double ratio, double incrementer, double decrementer, double threshold);
double approxInvSinWithTable(double **arr, double ratio);
double approxCos(double angle);
double approxCosCustom(double angle, double incrementer, double decrementer, double threshold);
double approxCosWithTable(double **arr, double angle);
double approxInvCos(double angle);
double approxInvCosCustom(double ratio, double incrementer, double decrementer, double threshold);
double approxInvCosWithTable(double **arr, double ratio);
double approxTan(double angle);
double approxTanCustom(double angle, double incrementer, double decrementer, double threshold);
double approxTanWithTable(double **arr, double angle);
double approxInvTan(double angle);
double approxInvTanCustom(double ratio, double incrementer, double decrementer, double threshold);
double approxInvTanWithTable(double **arr, double ratio);

#endif
