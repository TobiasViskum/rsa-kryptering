#include "generate_prime_numbers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void choose_two_large_primes(int *p, int *q) {
  *p = -1;
  *q = -1;

  int n = 945;

  int *prime_numbers = generate_prime_numbers(n);

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
int *generate_prime_numbers(int n) {
  if (n < 2) {
    printf("No prime numbers less than 2");
    exit(EXIT_FAILURE);
  }

  // Init array
  int *is_prime = (int *)malloc((n - 2) * sizeof(char));

  if (is_prime == NULL) {
    printf("Failed to allocate memory\n");
    exit(EXIT_FAILURE);
  }

  // Sets all numbers to be prime initially
  for (int i = 0; i <= n - 2; i++) {
    is_prime[i] = 1;
  }

  int sqrt_n = (int)sqrt(n);

  for (int i = 2; i <= sqrt_n; i++) {
    if (is_prime[i] == 0) {
      continue;
    };

    for (int j = i * i; j <= n; j += i) {
      is_prime[j] = 0;
    }
  }

  return is_prime;
}
