#include "generate_prime_numbers.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://en.wikipedia.org/wiki/Euclidean_algorithm#Implementations
int gcd(int a, int b) {
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }

  return a;
}

// Ligningen `de = 1 mod λ(n)` skal løses
//
// Hvis det skal være mere effektivt, kan følgende algoritme bruges:
// https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Pseudocode
int løs_for_d(int e, int phi) {
  for (int d = 2; d < phi; d++) {
    if ((d * e) % phi == 1) {
      return d;
    }
  }

  printf("Kunne ikke finde `d`\n");
  exit(EXIT_FAILURE);
}

// https://en.wikipedia.org/wiki/Modular_exponentiation#Pseudocode
int64_t mod_exp(int64_t x, int n, int mod) {
  if (mod == 1) {
    return 0;
  }

  int64_t result = 1;
  int64_t base = x % mod;

  while (n > 0) {
    if (n % 2 == 1) {
      result = (result * base) % mod;
    }
    base = (base * base) % mod;
    n = n / 2;
  }

  return result;
}

int64_t rsa_krypter(int m, int e, int n) { return mod_exp((int64_t)m, e, n); }

void rsa_krypter_tekst(char *tekst, int64_t *krypteret_tekst, int streng_længde,
                       int e, int n) {
  for (int i = 0; i < streng_længde; i++) {
    int m = (int)tekst[i];
    krypteret_tekst[i] = rsa_krypter(m, e, n);
  }
}

double rsa_dekrypter(int64_t c, int d, int n) { return mod_exp(c, d, n); }

void rsa_dekrypter_tekst(int64_t *krypteret_tekst, char *dekrypteret_tekst,
                         int streng_længde, int d, int n) {
  for (int i = 0; i < streng_længde; i++) {
    int64_t c = krypteret_tekst[i];
    dekrypteret_tekst[i] = rsa_dekrypter(c, d, n);
  }
}

// https://en.wikipedia.org/wiki/RSA_(cryptosystem)#Key_generation
void generer_rsa_nøgle(int *p, int *q, int *n, int *e, int *d) {
  // Step 1: Vælg to store primtal
  vælg_to_store_primtal(p, q);

  // Step 2: Bestem n hvor n = pq
  *n = (*p) * (*q);

  // Step 3: Bestem λ(n) som er lig med (p - 1)(q - 1)
  int phi = (*p - 1) * (*q - 1);

  // Step 4: Vælg e, hvor 1 < e < phi og gcd(e, phi) == 1
  // dvs. følgende ligning skal løses: `gcd(e, phi) = 1, 1 < e < phi`
  *e = -1;
  for (int i = 2; i < phi; i++) {
    int t = gcd(i, phi);
    if (t == 1) {
      *e = i;
      break;
    }
  }

  // Step 5: Bestem d
  *d = løs_for_d(*e, phi);
}

int main() {
  printf("\nTEKST DER SKAL KRYPTERES:\n");
  char *tekst = "Tobias Tranberg Viskum";
  int streng_længde = strlen(tekst);
  char dekrypteret_tekst[streng_længde];
  int64_t krypteret_tekst[streng_længde];
  printf("%s\n\n", tekst);

  printf("RSA KRYPTERINGS INFO:\n");
  int p, q, n, e, d;
  generer_rsa_nøgle(&p, &q, &n, &e, &d);

  printf("p = %d, q = %d, n = %d, e = %d, d = %d\n", p, q, n, e, d);
  printf("\n");

  printf("KRYPTERET NØGLE:\n");
  rsa_krypter_tekst(tekst, krypteret_tekst, streng_længde, e, n);

  for (int i = 0; i < streng_længde; i++) {
    printf("%lld", krypteret_tekst[i]);
  };
  printf("\n\n");

  printf("DEKRYPTERET NØGLE:\n");
  rsa_dekrypter_tekst(krypteret_tekst, dekrypteret_tekst, streng_længde, d, n);

  for (int i = 0; i < streng_længde; i++) {
    printf("%c", dekrypteret_tekst[i]);
  };
  printf("\n\n");

  return 0;
}
