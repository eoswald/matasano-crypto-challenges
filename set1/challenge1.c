#include <stdlib.h>
#include <stdio.h>

void hex2byte(const char * hex_str, int len_hex, char * bytes);
void byte2base64(const char * bytes, int size_bytes, char * base64_str);

int main() {
	int len_hex;
	int size_bytes;
	int len_base64;
	char * hex_str;
	char * bytes;
	char * base64_str;
	
	scanf("%d", &len_hex);
	hex_str = malloc(len_hex);
	size_bytes = ((len_hex - 1) / 2) + 1;
	len_base64 = ((size_bytes*4 - 1) / 3) + 1;
	bytes = malloc(size_bytes);
	base64_str = malloc(len_base64);

	scanf("%s", hex_str);
	hex2byte(hex_str, len_hex, bytes);
	byte2base64(bytes, size_bytes, base64_str);

	printf("%s\n", base64_str);
	return 0;
}

void hex2byte(const char * hex_str, int len_hex, char * bytes) {
	int i;
	for (i = 0; i < len_hex/2; ++i)
		sscanf((hex_str+i*2), "%2hhx", (bytes+i));
}

void byte2base64(const char * bytes, int size_bytes, char * base64_str) {
	const char * base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	char byte;
	char index;
	char carry;
	int i;
	int base64_count = 0;
	for (i = 0; i < size_bytes; ++i) {
		if (i % 3 == 0) {
			sscanf((bytes+i), "%c", &byte);
			index = byte >> 2;
			base64_str[base64_count++] = *(base64_table+index);
			carry = byte & 0x03;
		} else if ((i + 2) % 3 == 0) {
			sscanf((bytes+i), "%c", &byte);
			index = (carry << 4) | (byte >> 4);
			base64_str[base64_count++] = *(base64_table+index);
			carry = byte & 0x0F;
		} else {
			sscanf((bytes+i), "%c", &byte);
			index = (carry << 2) | (byte >> 6);
			base64_str[base64_count++] = *(base64_table+index);
			carry = byte & 0x3F;
			base64_str[base64_count++] = *(base64_table+carry);
		}
	}
	if ((i + 1) % 3 == 0) base64_str[base64_count++] = '=';
	else if ((i + 2) % 3 == 0) base64_str[base64_count] = '=';
}
