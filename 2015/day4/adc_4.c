#include<stdio.h>
#include <string.h>
#include <openssl/md5.h>

void create_hash(char* input, char output[33]) {
  unsigned char digest[16];
  const char* string = input;
  MD5_CTX ctx;
  MD5_Init(&ctx);
  MD5_Update(&ctx, string, strlen(string));
  MD5_Final(digest, &ctx);

  for(int i = 0; i < 16; ++i)
    sprintf(&output[i*2], "%02x", (unsigned int)digest[i]);

  output[32] = '\0';
}


int main() {
  char input[64] = "yzbqklnj";

  for ( int i = 0; i < 10000000; i++ ) {
    snprintf(input, sizeof(input), "yzbqklnj%d", i);

    char output[33];
    create_hash(input, output);

    unsigned char part[7];
    memcpy(part, output, 6);
    part[6] = '\0';

    int is_valid = strcmp(part, "000000");

    if ( is_valid == 0 ) {
      printf("%d -> %s\n", i, output);
      return 0;
    }
  }

  printf("invalid");
  return 1;
}
