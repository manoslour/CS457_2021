/*************************************************************
 * @file   hy457_crypto.h                                    *
 * @author Lourakis Manos <csd3153@csd.uoc.gr>  	         *
 *                                                    	     *
 * @brief  Library file for the needs of CS457 Assignment 1  *
 ************************************************************/

#ifndef _CS457_CRYPTO_H_
#define _CS457_CRYPTO_H_

#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define GREEN "\x1B[32m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"
#define ROUNDS 8
#define BUFFER_SIZE 1024

uint8_t* generateKey(long int size);
uint8_t* removeIllegal(uint8_t *plaintext);
uint8_t* removeAffineIllegal(uint8_t* plaintext);

// One-Time Pad (OTP)
uint8_t* otp_encrypt(uint8_t *plaintext, uint8_t *key);
uint8_t* otp_decrypt(uint8_t *ciphertext, uint8_t *key);

// Caesar's cipher
uint8_t* caesar_encrypt(uint8_t *plaintext, unsigned short N);
uint8_t* caesar_decrypt(uint8_t *ciphertext, unsigned short N);

// Affine cipher
uint8_t* affine_encrypt(uint8_t* plaintext);
uint8_t* affine_decrypt(uint8_t* ciphertext);

// Feistel cipher
uint8_t feistel_round(uint8_t* block, uint8_t* key);
uint8_t* feistel_encrypt(uint8_t* plaintext, uint8_t* keys[]);
uint8_t* feistel_decrypt(uint8_t* ciphertext, uint8_t* keys[]);

// Playfair cipher
char* removeDup(char* key);
unsigned char* playfair_encrypt(unsigned char *plaintext, unsigned char** key);
unsigned char* playfair_decrypt(unsigned char *ciphertext, unsigned char** key);
unsigned char** playfair_keymatrix(unsigned char *key);

#endif