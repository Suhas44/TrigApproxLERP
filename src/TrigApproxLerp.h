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

double approxSin(double angle);
double approxSinCustom(double angle, double incrementer, double decrementer, double threshold);
double approxCos(double angle);
double approxCosCustom(double angle, double incrementer, double decrementer, double threshold);
double approxTan(double angle);
double approxTanCustom(double angle, double incrementer, double decrementer, double threshold);

#endif
