#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 36

void repeating_key_xor(const char * bytes, int size_bytes, const char * key, int size_key, char * bytes_xored);
void byte2hex(const char * bytes, int size_bytes, char * hex_str);

int main() {
	int size_plaintext;
	int size_key;
	int len_hex;
	char * plaintext;
	char * key;
	char * plaintext_xored;
	char * hex_str;
	int i;

	scanf("%d", &size_plaintext);
	len_hex = size_plaintext*2;
	plaintext = malloc(size_plaintext);
	plaintext_xored = malloc(size_plaintext);
	hex_str = malloc(len_hex);

	fgetc(stdin);
	for (i = 0; i < size_plaintext; ++i)
		plaintext[i] = fgetc(stdin);

	scanf("%d", &size_key);
	key = malloc(size_key);
	scanf("%s", key);

	repeating_key_xor(plaintext, size_plaintext, key, size_key, plaintext_xored);
	byte2hex(plaintext_xored, size_plaintext, hex_str);

	printf("Input: %s\n", plaintext);
	printf("Key: %s\n", key);
	printf("Output: %s\n", hex_str);
	
	return 0;
}

void repeating_key_xor(const char * bytes, int size_bytes, const char * key, int size_key, char * bytes_xored) {
	int i, j;
	for (i = 0, j = 0; i < size_bytes; ++i, ++j) {
		if (j == size_key) j = 0;
		bytes_xored[i] = bytes[i] ^ key[j];
	}
}

void byte2hex(const char * bytes, int size_bytes, char * hex_str) {
	int i;
	for (i = 0; i < size_bytes; ++i)
		sprintf(&hex_str[2*i], "%02x", *(bytes+i));
}
