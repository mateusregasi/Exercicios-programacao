// https://judge.beecrowd.com/pt/problems/view/2166

#include <stdio.h>

double raiz(double n) {
  if (!n)
    return 0;
  return 1 / (2 + raiz(n - 1));
}

double fp(double n) {
  return 1.0 + raiz(n); 
}

int main(void) {
  double n;
  scanf("%lf", &n);
  printf("%.10lf\n", fp(n));
  return 0;
}