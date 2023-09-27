#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "fraction.h"

#define Fraction(num, denom) ((struct Fraction) {num, denom})
#define one Fraction(1, 1)

Fraction fact(int n) {
        Fraction m = {n, 1};
        return n == 0 ? one : mul(m, fact(n - 1));
}

Fraction fact_frac(Fraction frac, int r) {
        return r == 0 ? one : mul(frac, fact_frac(sub(frac, one), r - 1));
}

Fraction solve_x(Fraction coef, Fraction approx) {
        return divide(sub(approx, one), coef);
}

void find_x(Fraction coef, Fraction approx, Fraction *multiplier, Fraction *x) {
        Fraction ten = {10, 1};
        Fraction mult = one;
        Fraction range = invert(mag(coef)); simplify(&range);
        Fraction result = solve_x(coef, divide(approx, mult));
        while (!(grtrThanFrac(result, neg(range)) && lessThanFrac(result, range))) {
                mult = mul(mult, ten);
                result = solve_x(coef, divide(approx, mult));
        }
        *multiplier = mult;
        *x = result;
}

int main(void) {
  Fraction con;
  Fraction coef;
  Fraction index;
  int term;
  Fraction approx;

  printf("\nEnter constant term: ");
  parseInput(&con);
  printf("\nEnter coefficient of x: ");
  parseInput(&coef);
  printf("\nEnter power: ");
  parseInput(&index);
  printf("\nUp to index: ");
  scanf("%d", &term);
  printf("\nApproximate (enter without the surd): ");
  parseInput(&approx);
  if (index.denom % 2 == 0 && toDec(approx) < 0) {
         printf("\nYou can't approximate a negative number for this power!\n");
         exit(EXIT_FAILURE);
  } 
  if (con.denom == 0 || coef.denom == 0 || index.denom == 0 || approx.denom == 0) {
          printf("\nDenominator can't be 0!\n");
          exit(EXIT_FAILURE);
  }

  Fraction new_coef = divide(coef, con); simplify(&new_coef);
  Fraction new_approx = divide(approx, con); simplify(&new_coef);
  Fraction x;
  Fraction multiplier;
  find_x(new_coef, new_approx, &multiplier, &x);

  printf("\n\n");
  double result = 0.0;
  for (int i = 0; i <= term; i++) {
          
          Fraction coefficient = mul(mul(divide(fact_frac(index, i), fact(i)), power(new_coef, i)), power(con, toDec(index)));
          result += toDec(coefficient) * pow(toDec(x), i);
          printf("Coefficient of x^%d: ", i);
          printFrac(coefficient);
          printf("\n\n");
  }
  printf("Using x = ");
  printFrac(x);
  printf(" for approximation..... %.15lf\n\n", index.denom == 1 ? pow(toDec(approx), toDec(index)) : result * pow(toDec(multiplier), toDec(index)));
  return 0;
}
