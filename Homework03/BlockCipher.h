#pragma once

#include <stdio.h>  
#include <stdlib.h>

//	16 bytes for key
void BC_ECB_encrypt(unsigned char *buffer, int length, unsigned char *key);

void BC_ECB_decrypt(unsigned char *buffer, int length, unsigned char *key);