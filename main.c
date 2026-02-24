#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./decrypt.c"

int main(int argc,char *argv[]){
    unsigned char key[16] = "YELLOW SUBMARINE"; // 16 bytes

    FILE *f = fopen("encrypted.bin", "rb");
    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    rewind(f);

    unsigned char *ciphertext = malloc(filesize);
    fread(ciphertext, 1, filesize, f);
    fclose(f);

    unsigned char *plaintext = malloc(filesize);

    int decrypted_len = decrypt(ciphertext, filesize, key, plaintext);

    FILE *out = fopen("decrypted.txt", "wb");
    fwrite(plaintext, 1, decrypted_len, out);
    fclose(out);

    free(ciphertext);
    free(plaintext);
    return 0;
}