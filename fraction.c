#include "fraction.h"
static int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
}

void printFrac(Fraction frac) {
        if (frac.denom == 1) {
                printf("%ld", frac.num);
        } else {
                printf("%ld/%ld", frac.num, frac.denom);
        }
}

void parseInput(Fraction *frac) {
        char str[10];
        char delims[] = " /";
        fscanf(stdin, "%s", str);
        if (strchr(str, '/') != NULL) {
                char *token = strtok(str, delims);
                frac -> num = atoi(token);
                token = strtok(NULL, delims);
                frac -> denom = atoi(token);
        } else {
                frac -> num = atoi(str);
                frac -> denom = 1;
        }
}

double toDec(Fraction frac) {
        return (double)frac.num / frac.denom;
}

void simplify(Fraction *frac) {
        if (frac -> denom < 0) {
                frac -> num *= -1;
                frac -> denom *= -1;
        }
        int hcf = gcd(abs(frac -> num), abs(frac -> denom));
        frac -> num /= hcf;
        frac -> denom /= hcf;
}

Fraction add(Fraction a, Fraction b) {
        if(a.num == 0) {
                return b;
        } else if (b.num == 0) {
                return a;
        }
        Fraction new;
        new.num = (a.num * b.denom) + (b.num * a.denom);
        new.denom = a.denom * b.denom;
        simplify(&new);
        return new;
}

Fraction sub(Fraction a, Fraction b) {
        return add(a, neg(b));
}

Fraction mul(Fraction a, Fraction b) {
        Fraction new;
        new.num = a.num * b.num;
        new.denom = a.denom * b.denom;
        simplify(&new);
        return new;
}

Fraction divide(Fraction a, Fraction b) {
        return mul(a, invert(b));
}

Fraction power(Fraction frac, double d) {
        Fraction new = {round(pow(frac.num, d)), round(pow(frac.denom, d))};
        return new;
}

bool lessThanNum(Fraction frac, double d) {
        return ((double)frac.num / frac.denom) < d;
}

bool grtrThanNum(Fraction frac, double d) {
        return ((double)frac.num / frac.denom) > d;
}

bool lessThanFrac(Fraction a, Fraction b) {
        return ((double)a.num / a.denom) < ((double)b.num / b.denom);
}

bool grtrThanFrac(Fraction a, Fraction b) {
        return ((double)a.num / a.denom) > ((double)b.num / b.denom);
}

Fraction invert(Fraction frac) {
        Fraction inverted = {frac.denom, frac.num};
        return inverted;
}

Fraction neg(Fraction frac) {
        Fraction new = {-frac.num, frac.denom};
        return new;
}

Fraction mag(Fraction frac) {
        Fraction new = {abs(frac.num), abs(frac.denom)};
        return new;
}
