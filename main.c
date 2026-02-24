#include <openssl/evp.h>
#include <openssl/err.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int decrypt(unsigned char* ciphertext, int ciphertext_len, unsigned char* key, unsigned char* plaintext){
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;

    ctx = EVP_CIPHER_CTX_new();
    if(!ctx)return -1;

    if(EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(),NULL,key,NULL) != 1) return -1;

    if(EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len) != 1) return -1;

    plaintext_len = len;

    if(EVP_DecryptFinal_ex(ctx, plaintext + len, &len) != 1) return -1;

    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}
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