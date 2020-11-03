#include "hash.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Error in argument count\n");
		return 1;
	}
	uint8_t data[DATA_BYTE_SIZE];
	size_t data_size;
	FILE *file = fopen(argv[1], "rb");
	if (!file) {
		fprintf(stderr, "Open file error\n");
		return 1;
	}
	struct context ctx;
	uint8_t digest[DIGEST_512_BYTE_SIZE];
	init(&ctx, data, DIGEST_512_BIT_SIZE);
	while ((data_size = fread(data, 1, sizeof(data), file)))
		update(&ctx, data, data_size);
	finish(&ctx, digest);
	for (int i = DIGEST_512_BYTE_SIZE - 1; i >= 0; --i)
		printf("%02" PRIx8, digest[i]);
	printf("\n");
	fclose(file);
	return 0;
}
