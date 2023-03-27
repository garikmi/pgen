#include "words.h"
#include <stdlib.h>

char random_lowercase_letter() { return (char)(rand() % 26 + 97); }

char random_uppercase_letter() { return (char)(rand() % 26 + 65); }

char random_number() { return (char)(rand() % 9 + 48); }

/* vowels: a, e, i, o, u */
char random_vowel(int uppercase) {
  char vowels[] = "aeiou";
  int len = sizeof(vowels) - 1;
  if (uppercase)
    return vowels[rand() % len] - 32;
  return vowels[rand() % len];
}

/* conosants: b, c, d, f, g, h, j, k, l, m, n, p, q, r, s, t, v, w, y, z */
char random_consonant(int uppercase) {
  char consonants[] = "bcdfghjklmnpqrstvwyz";
  int len = sizeof(consonants) - 1;
  if (uppercase)
    return consonants[rand() % len] - 32;
  return consonants[rand() % len];
}

/* convert first found letter to number or convert first or last to number */
void first_to_number(char *buffer, int len) {
  // replace first occurence of a letter to number
  for (int i = 0; i < len; i++) {
    if (buffer[i] == 'o' || buffer[i] == 'O') {
      buffer[i] = '0';
      return;
    } else if (buffer[i] == 'i' || buffer[i] == 'I') {
      buffer[i] = '1';
      return;
    } else if (buffer[i] == 'z' || buffer[i] == 'Z') {
      buffer[i] = '2';
      return;
    } else if (buffer[i] == 'e' || buffer[i] == 'E') {
      buffer[i] = '3';
      return;
    } else if (buffer[i] == 'a' || buffer[i] == 'A') {
      buffer[i] = '4';
      return;
    } else if (buffer[i] == 's' || buffer[i] == 'S') {
      buffer[i] = '5';
      return;
    } else if (buffer[i] == 't' || buffer[i] == 'T') {
      buffer[i] = '7';
      return;
    } else if (buffer[i] == 'b' || buffer[i] == 'G') {
      buffer[i] = '6';
      return;
    } else if (buffer[i] == 'B' || buffer[i] == 'g') {
      buffer[i] = '8';
      return;
    } else if (buffer[i] == 'q') {
      buffer[i] = '9';
      return;
    }
  }
  // replace only the first or last letter?
  if (rand() % 2) {
    *buffer = (char)(rand() % 9 + 48);
  } else {
    buffer[len - 1] = (char)(rand() % 9 + 48);
  }
}
