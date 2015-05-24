#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 36

void fixed_xor(const char * hex_str1, const char * hex_str2, int buff_size, char * hex_xored);

int main() {
	char hex_str1[BUFFER_SIZE] = "1c0111001f010100061a024b53535009181c";
	char hex_str2[BUFFER_SIZE] = "686974207468652062756c6c277320657965";
	char hex_xored[BUFFER_SIZE];
	
	fixed_xor(hex_str1, hex_str2, BUFFER_SIZE, hex_xored);

	printf("%s\n", hex_xored);
	return 0;
}

void fixed_xor(const char * hex_str1, const char * hex_str2, int buff_size, char * hex_xored) {
	int size_bytes;
	char * bytes1;
	char * bytes2;
	char * bytes_xored;
	int i;

	size_bytes = ((buff_size - 1) / 2) + 1;
	bytes1 = malloc(size_bytes);
	bytes2 = malloc(size_bytes);
	bytes_xored = malloc(size_bytes);

	for (i = 0; i < buff_size/2; ++i) {
		sscanf(&hex_str1[2*i], "%2hhx", (bytes1+i));
		sscanf(&hex_str2[2*i], "%2hhx", (bytes2+i));
		*(bytes_xored+i) = *(bytes1+i) ^ *(bytes2+i);
	}

	for (i = 0; i < size_bytes; ++i)
		sprintf(&hex_xored[2*i], "%02x", *(bytes_xored+i));
}
