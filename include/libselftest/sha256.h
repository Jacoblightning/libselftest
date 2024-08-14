#pragma once

void sha256_string(const char *string, char outputBuffer[65]);
int sha256_file(const char *path, char outputBuffer[65]);