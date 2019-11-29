#pragma once

#include <stdio.h>  
#include <stdlib.h>

//	16 bytes for key
void BC_ECB_encrypt(unsigned char *buffer, int length, unsigned char *key);

void BC_ECB_decrypt(unsigned char *buffer, int length, unsigned char *key);

void BC_CBC_encrypt(unsigned char *buffer, int length, unsigned char *key, unsigned char *IV);

void BC_CBC_decrypt(unsigned char *buffer, int length, unsigned char *key, unsigned char *IV);

void BC_PPM_encrypt(unsigned char *buffer, int length, unsigned char *key, int keyLength);

void BC_PPM_decrypt(unsigned char *buffer, int length, unsigned char *key, int keyLength);