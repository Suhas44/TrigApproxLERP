#include "TrigApproxLerp.h"
#include <math.h>
#include <stdio.h>

int main() {
    float answer = calcSin(50);
    printf("%f\n", answer);
}

float calcSin(float angle) {
    return sin(angle * (M_PI / 180));
}

void populateLookupTable(int incrementer, float threshold, float decrementer){};

float approxSin(float angle);