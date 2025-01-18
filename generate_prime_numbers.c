#include "generate_prime_numbers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void vælg_to_store_primtal(int *p, int *q) {
  *p = -1;
  *q = -1;

  int n = 3849;

  int *prime_numbers = generer_primtal(n);

  // Vælger de to største primtal der er genereret
  // Tallene skal gerne have en større forskel og være meget større, hvis det
  // skal være sikkert
  int difference = 48;
  int count = 0;

  for (int i = n; i >= 2; i--) {
    if (prime_numbers[i] == 0) {
      continue;
    };

    if (*p == -1) {
      *p = i;
    } else if (count < difference) {
      count++;
      continue;
    } else if (*q == -1) {
      *q = i;
      break;
    };
  };
};

// Algorithm: Sieve of Eratosthenes
// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes#Pseudocode
int *generer_primtal(int n) {
  if (n < 2) {
    printf("No prime numbers less than 2");
    exit(EXIT_FAILURE);
  }

  // Alle tal fra 0 til n-2
  int *er_primtal = (int *)malloc((n - 2) * sizeof(char));

  if (er_primtal == NULL) {
    printf("Failed to allocate memory\n");
    exit(EXIT_FAILURE);
  }

  // Sætter alle tal til at være et primtal til at starte med
  for (int i = 0; i <= n - 2; i++) {
    er_primtal[i] = 1;
  }

  // Dette er bestemt af algoritmen der følges
  int sqrt_n = (int)sqrt(n);

  // Sørger for, at kun primtallene har værdien 1
  for (int i = 2; i <= sqrt_n; i++) {
    if (er_primtal[i] == 0) {
      continue;
    };

    for (int j = i * i; j <= n; j += i) {
      er_primtal[j] = 0;
    }
  }

  return er_primtal;
}
