#include <openssl/evp.h>
#include <openssl/err.h>

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