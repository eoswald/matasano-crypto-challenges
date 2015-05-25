#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRING_LENGTH 60
#define SIZE_BYTES 30

struct message {
	char hex_str[STRING_LENGTH+1];
	char bytes[SIZE_BYTES+1];
	char decryption_char;
	char decrypted_message[SIZE_BYTES+1];
	int score;
};

void hex2byte(const char * hex_str, int len_hex, char * bytes);
void xor_cipher(struct message *msg);

int main() {
	char input_buf[STRING_LENGTH];
	int highest_score = 0;
	struct message best_fit;

	FILE *fp = fopen("challenge4-data.txt", "r");

	while (fscanf(fp, "%s", input_buf) != EOF) {
		struct message msg;
		strncpy(msg.hex_str, input_buf, STRING_LENGTH);
		msg.hex_str[STRING_LENGTH] = '\x00';
		hex2byte(msg.hex_str, STRING_LENGTH, msg.bytes);
		msg.bytes[SIZE_BYTES] = '\x00';
		msg.score = 0;
		xor_cipher(&msg);
		msg.decrypted_message[SIZE_BYTES] = '\x00';
		if (msg.score > highest_score) {
			best_fit = msg;
			highest_score = msg.score;
		}
	}
	printf("Original: %s\n", best_fit.hex_str);
	printf("Decryption Character: %c\n", best_fit.decryption_char);
	printf("Decrypted Message: %s\n", best_fit.decrypted_message);

	return 0;
}

void hex2byte(const char * hex_str, int len_hex, char * bytes) {
	int i;
	for (i = 0; i < len_hex/2; ++i)
		sscanf((hex_str+i*2), "%2hhx", (bytes+i));
}

void xor_cipher(struct message *msg) {
	int scores[128];
	int num_uppercase;
	int num_lowercase;
	char byte_xored;

	int i;
	int j;
	for (i = 0; i < 128; ++i) {
		scores[i] = 0;
		num_uppercase = 0;
		num_lowercase = 0;
		for (j = 0; j < SIZE_BYTES; ++j) {
			byte_xored = msg->bytes[j] ^ i;
			if (byte_xored > 64 && byte_xored < 91) {
				num_uppercase++;
				scores[i]++;
			} else if (byte_xored > 96 && byte_xored < 123) {
				num_lowercase++;
				scores[i]++;
			} else if (byte_xored == 32)
				scores[i]++;
		}
		if ((scores[i] > msg->score) || (scores[i] == msg->score && num_lowercase > num_uppercase)) {
			msg->score = scores[i];
			msg->decryption_char = (char) i;
		}
	}

	for (i = 0; i < SIZE_BYTES; ++i)
		msg->decrypted_message[i] = msg->bytes[i] ^ msg->decryption_char;
	
}
