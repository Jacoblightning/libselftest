// ReSharper disable CppDeprecatedEntity

#include <openssl/sha.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cerrno>

#include "sha256.h"

void sha256_hash_string (unsigned char hash[SHA256_DIGEST_LENGTH], char outputBuffer[65])
{
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }

    outputBuffer[64] = 0;
}


void sha256_string(const char *string, char outputBuffer[65])
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, string, strlen(string));
    SHA256_Final(hash, &sha256);
    sha256_hash_string(hash, outputBuffer);
}

int sha256_file(const char *path, char outputBuffer[65])
{
    FILE *file = fopen(path, "rb");
    if(!file) return -534;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    constexpr int bufSize = 32768;
    auto *buffer = static_cast<unsigned char *>(malloc(bufSize));
    int bytesRead = 0;
    if(!buffer) return ENOMEM;
    while((bytesRead = static_cast<int>(fread(buffer, 1, bufSize, file))))
    {
        SHA256_Update(&sha256, buffer, bytesRead);
    }
    SHA256_Final(hash, &sha256);

    sha256_hash_string(hash, outputBuffer);
    fclose(file);
    free(buffer);
    return 0;
}