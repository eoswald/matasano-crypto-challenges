#include <stdlib.h>
#include <stdio.h>

#define STRING_LENGTH 14

int hamming_distance(const char * s1, const char * s2, int length);
void str2bitstr(const char * str, int length, char * bitstr);
int triple_min(int a, int b, int c);

int main() {
    char str1[STRING_LENGTH] = "this is a test";
    char str2[STRING_LENGTH] = "wokka wokka!!!";

    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);
    printf("Hamming Distance: %d", hamming_distance(str1, str2, STRING_LENGTH));

    return 0;
}

int hamming_distance(const char * s1, const char * s2, int length) {
    int diff;
    char * bs1;
    char * bs2;
    int ** table;

    bs1 = malloc(length*8);
    bs2 = malloc(length*8);
    str2bitstr(s1, length, bs1);
    str2bitstr(s2, length, bs2);

    table = malloc(length*8*sizeof(int*));
    int i, j;
    for (i = 0; i < length*8; ++i)
      table[i] = malloc(length*8*sizeof(int));
    for (i = 0; i < length*8; ++i) {
      table[i][0] = i;
      table[0][i] = i;
    }
    for (i = 1; i < length*8; ++i) {
      for (j = 1; j < length*8; ++j) {
        diff = (bs1[i] == bs2[j]) ? 0 : 1;
        table[i][j] = triple_min(table[i-1][j]+1, table[i][j-1]+1, table[i-1][j-1]+diff);
      }
    }
    return table[length*8-1][length*8-1];
}

void str2bitstr(const char * str, int length, char * bitstr) {
    int bitstr_index = length*8 - 1;
    int i, j;
    char tmp;
    for (i = length-1; i >= 0; --i) {
        tmp = str[i];
        bitstr[bitstr_index] = (tmp%2 == 0) ? '0' : '1';
        bitstr_index--;
        for (j = 1; j < 8; ++j, --bitstr_index)
            bitstr[bitstr_index] = ((tmp >>= 1)%2 == 0) ? '0' : '1';
    }
    bitstr[length*8] = '\0';
}

int triple_min(int a, int b, int c) {
  return ((a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c));
}
