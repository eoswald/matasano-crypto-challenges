#include <stdlib.h>
#include <stdio.h>

void hex2byte(const char * hex_str, int len_hex, char * bytes);
char xor_cipher(const char * bytes, int size_bytes, char * decrypted_message);

int main() {
	int len_hex;
	int size_bytes;
	char * hex_str;
	char * bytes;
	char * decrypted_message;
	char highest_char;
	
	scanf("%d", &len_hex);
	hex_str = malloc(len_hex);
	size_bytes = ((len_hex - 1) / 2) + 1;
	bytes = malloc(size_bytes);
	decrypted_message = malloc(size_bytes);

	scanf("%s", hex_str);
	hex2byte(hex_str, len_hex, bytes);
	highest_char = xor_cipher(bytes, size_bytes, decrypted_message);

	printf("Character: %c\n", highest_char);
	printf("Message: %s\n", decrypted_message);

	return 0;
}

void hex2byte(const char * hex_str, int len_hex, char * bytes) {
	int i;
	for (i = 0; i < len_hex/2; ++i)
		sscanf((hex_str+i*2), "%2hhx", (bytes+i));
}

char xor_cipher(const char * bytes, int size_bytes, char * decrypted_message) {
	int scores[128];
	int highest_score = 0;
	int num_uppercase;
	int num_lowercase;
	char highest_char;
	char byte_xored;

	int i;
	int j;
	for (i = 0; i < 128; ++i) {
		scores[i] = 0;
		num_uppercase = 0;
		num_lowercase = 0;
		for (j = 0; j < size_bytes; ++j) {
			byte_xored = *(bytes+j) ^ i;
			if (byte_xored > 64 && byte_xored < 91) {
				num_uppercase++;
				scores[i]++;
			} else if (byte_xored > 96 && byte_xored < 123) {
				num_lowercase++;
				scores[i]++;
			}
		}
		if ((scores[i] > highest_score) || (scores[i] == highest_score && num_lowercase > num_uppercase)) {
			highest_score = scores[i];
			highest_char = (char) i;
		}
	}

	for (i = 0; i < size_bytes; ++i)
		*(decrypted_message+i) = *(bytes+i) ^ highest_char;
	
	return highest_char;
}
