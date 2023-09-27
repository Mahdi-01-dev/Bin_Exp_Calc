#ifndef FRACTION_H
#define FRACTION_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct Fraction{
        int64_t num;
        int64_t denom;
} Fraction;

void printFrac(Fraction);

void parseInput(Fraction *);

double toDec(Fraction);

void simplify(Fraction *);

Fraction add(Fraction, Fraction);

Fraction sub(Fraction, Fraction);

Fraction mul(Fraction, Fraction);

Fraction divide(Fraction, Fraction);

Fraction power(Fraction, double);

bool lessThanNum(Fraction, double);

bool grtrThanNum(Fraction, double);

bool lessThanFrac(Fraction, Fraction);

bool grtrThanFrac(Fraction, Fraction);

Fraction invert(Fraction);

Fraction neg(Fraction);

Fraction mag(Fraction);

#endif //FRACTION_H
