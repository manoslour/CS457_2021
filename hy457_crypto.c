/*************************************************************
 * @file   hy457_crypto.c                                    *
 * @author Lourakis Manos <csd3153@csd.uoc.gr>  	         *
 *                                                    	     *
 * @brief  Source file for the needs of CS457 Assignment 1   *
 ************************************************************/

#include "hy457_crypto.h"

uint8_t* generateKey(long int size){
    int fd;
    uint8_t *buffer = (uint8_t*)malloc(size * sizeof(uint8_t));
    fd = open("/dev/urandom", O_RDONLY);
    read(fd, buffer, size);
    close(fd);
    return buffer;
}

uint8_t* removeIllegal(uint8_t *plaintext){
    int i, j;
    // Remove illegal characters fron plaintext
    for(i = 0; plaintext[i] != '\0'; i++){
        while(!((plaintext[i] >= 48 && plaintext[i] <= 57) || (plaintext[i] >= 65 && plaintext[i] <= 90) || (plaintext[i] >= 97 && plaintext[i] <= 122) || plaintext[i] == '\0')) {
            for(j = i; plaintext[j] != '\0'; j++){
                plaintext[j] = plaintext[j+1];
            }
            plaintext[j] = '\0';
        }
    }
    return plaintext;
}

uint8_t* removeAffineIllegal(uint8_t* plaintext){
    int i, j;
    // Remove illegal characters fron plaintext
    for(i = 0; plaintext[i] != '\0'; i++){
        while(!((plaintext[i] >= 65 && plaintext[i] <= 90) || (plaintext[i] >= 97 && plaintext[i] <= 122) || plaintext[i] == '\0')) {
            for(j = i; plaintext[j] != '\0'; j++){
                plaintext[j] = plaintext[j+1];
            }
            plaintext[j] = '\0';
        }
        plaintext[i] = toupper(plaintext[i]);
    }
    return plaintext;
}

uint8_t* otp_encrypt(uint8_t *plaintext, uint8_t *key){
    int i;
    long int textSize;
    uint8_t *encryptedText;
    
    textSize = strlen(plaintext);
    encryptedText = (uint8_t*)malloc(textSize * sizeof(uint8_t));

    printf("\n-------------------- "GREEN"OTP ENCRYPTION"RESET" --------------------\n");
    for(i = 0; i < textSize; i++){
        printf("Key: [%d|%c]\tText: [%d|%c]", key[i], key[i], plaintext[i], plaintext[i]);
        encryptedText[i] = plaintext[i] ^ key[i];
        printf("\tencryptedText: [%d|%c]\n", encryptedText[i], encryptedText[i]);
    }
    return encryptedText;
}

uint8_t* otp_decrypt(uint8_t *ciphertext, uint8_t *key){
    int i;
    long int textSize;
    uint8_t *decryptedText;

    textSize = strlen(ciphertext);
    decryptedText = (uint8_t*)malloc(textSize * sizeof(uint8_t));

    printf("\n-------------------- "YEL"OTP DECRYPTION"RESET" --------------------\n");
    for(i = 0; i < textSize; i++){
        printf("Key: [%d|%c]\tText: [%d|%c]", key[i], key[i], ciphertext[i], ciphertext[i]);
        decryptedText[i] = ciphertext[i] ^ key[i];
        printf("\tdecryptedText: [%d|%c]\n", decryptedText[i], decryptedText[i]);
    }
    return decryptedText;
}

uint8_t* caesar_encrypt(uint8_t *plaintext, unsigned short N){
    int i;
    long int textSize;
    uint8_t *encryptedtext;

    textSize = strlen(plaintext);
    encryptedtext = (uint8_t*)malloc(textSize * sizeof(uint8_t));

    printf("\n------------------ "GREEN"CAESARS ENCRYPTION"RESET" ------------------\n");
    for(i = 0; i < textSize; i++){
        if(plaintext[i] >= 48 && plaintext[i] <= 57){
            encryptedtext[i] = (plaintext[i] + N - 48) % 10 + 48;
            printf("plaintext[%d] = %c \t|\t encryptedtext[%d] = %c\n", i, plaintext[i], i, encryptedtext[i]);
        }
        else if(plaintext[i] >= 65 && plaintext[i] <= 90){
            encryptedtext[i] = (plaintext[i] + N - 65) % 26 + 65;
            printf("plaintext[%d] = %c \t|\t encryptedtext[%d] = %c\n", i, plaintext[i], i, encryptedtext[i]);
        }
        else{
            encryptedtext[i] = (plaintext[i] + N - 97) % 26 + 97;
            printf("plaintext[%d] = %c \t|\t encryptedtext[%d] = %c\n", i, plaintext[i], i, encryptedtext[i]);
        }
    }
    return encryptedtext;
}

uint8_t* caesar_decrypt(uint8_t *ciphertext, unsigned short N){
    int i;
    long int textSize;
    uint8_t *decryptedtext;

    textSize = strlen(ciphertext);
    decryptedtext = (uint8_t*)malloc(textSize * sizeof(uint8_t));

    printf("\n------------------ "YEL"CAESARS DECRYPTION"RESET" ------------------\n");
    for(i = 0; i < textSize; i++){
        if(ciphertext[i] >= 48 && ciphertext[i] <= 57){
            decryptedtext[i] = (ciphertext[i] + (10 - N) - 48) % 10 + 48;
            printf("ciphertext[%d] = %c \t|\t decryptedtext[%d] = %c\n", i, ciphertext[i], i, decryptedtext[i]);
        }
        else if(ciphertext[i] >= 65 && ciphertext[i] <= 90){
            decryptedtext[i] = (ciphertext[i] + (26 - N) - 65) % 26 + 65;
            printf("ciphertext[%d] = %c \t|\t decryptedtext[%d] = %c\n", i, ciphertext[i], i, decryptedtext[i]);
        }
        else{
            decryptedtext[i] = (ciphertext[i] + (26 - N) - 97) % 26 + 97;
            printf("ciphertext[%d] = %c \t|\t decryptedtext[%d] = %c\n", i, ciphertext[i], i, decryptedtext[i]);
        }
    }
    return decryptedtext;
}

uint8_t* affine_encrypt(uint8_t* plaintext){
    int a, b, m, x, i;
    long int textSize;
    uint8_t *encryptedtext;

    a = 11;
    b = 19;
    m = 26;

    textSize = strlen(plaintext);
    encryptedtext = (uint8_t*)malloc(textSize * sizeof(uint8_t));
    
    printf("\n------------------ "YEL"AFFINE ENCRYPTION"RESET" ------------------\n");
    for(i = 0; i < textSize; i++){
        x = (int) plaintext[i] - 65;
        encryptedtext[i] = ((a*x + b) % m) + 65;
        printf("plaintext[%d] = %c \t|\t encryptedtext[%d] = %c\n", i, plaintext[i], i, encryptedtext[i]);
    }

    return encryptedtext;
}

uint8_t* affine_decrypt(uint8_t* ciphertext){
    int a, b, m, x, i;
    long int textSize;
    int flag, a_inverse;
    uint8_t *decryptedtext;

    a = 11;
    b = 19;
    m = 26;
    flag = a_inverse = 0;

    textSize = strlen(ciphertext);
    decryptedtext = (uint8_t*)malloc(textSize * sizeof(uint8_t));

    //find a^-1(multiplicative inverse of a) in the group of integers mod m
    for(i = 0; i < 26; i++){
        flag = (a * i) % 26;
        if(flag == 1){
            a_inverse = i;
        } 
    }

    printf("\n------------------ "GREEN"AFFINE DECRYPTION"RESET" ------------------\n");
    for(i = 0; i < textSize; i++){
        decryptedtext[i] = ((a_inverse * (ciphertext[i] + 65 - b) ) % m) + 65;
        printf("ciphertext[%d] = %c \t|\t decryptedtext[%d] = %c\n", i, ciphertext[i], i, decryptedtext[i]);
    }

    return decryptedtext;
}

uint8_t feistel_round(uint8_t* block, uint8_t* key){
    printf("KEY = %X\n", *key);
    uint8_t result = (uint8_t) (*block * *key) % (uint8_t)pow(2,32);
    return result;
}

uint8_t* feistel_encrypt(uint8_t* plaintext, uint8_t* keys[]){
    int i, textSize;
    uint8_t tmp;
    uint8_t *L_BLOCK, *R_BLOCK, *nextL_BLOCK, *nextR_BLOCK;
    L_BLOCK = (uint8_t*)malloc(32 * sizeof(uint8_t));
    R_BLOCK = (uint8_t*)malloc(32 * sizeof(uint8_t));

    textSize = strlen(plaintext);

    for(i = 0; i < 30; i++){
        L_BLOCK[i] = plaintext[i];
    }
    printf("L_BLOCK = %s\n", L_BLOCK);
    for(i = 0; i < 30; i++){
        R_BLOCK[i] = plaintext[i+30];
    }
    printf("R_BLOCK = %s\n", R_BLOCK);

    printf("\n------------------ "YEL"FEISTEL ENCRYPTION"RESET" ------------------\n");
    
    for(int i = 0; i < ROUNDS; i++){
        nextL_BLOCK = R_BLOCK;
        tmp = *L_BLOCK ^ feistel_round(R_BLOCK, keys[i]);
        nextR_BLOCK = &tmp;

        L_BLOCK = nextL_BLOCK;
        R_BLOCK = nextR_BLOCK;
    }
    
    uint8_t *final = strcat(nextL_BLOCK, nextR_BLOCK);
    printf("final = %X\n", *final);
    return final;
}

unsigned char** playfair_keymatrix(unsigned char *key){

    int x = 65;
    int size, k, w, letter;
    int grid[5][5];
    int charMap[25][2];

    // Create charMap
    // [A][0], [B][0], [C][0]...
    // I = J
    for(int i = 0; i < 25; i++){
        if(x == 74){
            x++;
        }        
        charMap[i][0] = x;
        charMap[i][1] = 0;
        x++;
    }

    k = 0;
    w = 0;
    key = removeDup(key);
    size = strlen(key);
    printf("Key = %s\n", key);

    //Create 5x5 Grid
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(k < size){
                letter = (int) key[k];
                if(letter > 73)
                    letter--;
                grid[i][j] = charMap[letter-65][0];
                charMap[letter-65][1] = 1;
                k++;
            }
            else{
                while(charMap[w][1] != 0){
                    w++;
                }
                grid[i][j] = charMap[w][0];
                charMap[w][1] = 1;
                w++;
            }
        }
    }

    for(int i = 0; i < 5; i++){
        printf("|");
        for(int j = 0; j < 5; j++){
            printf("%c|", grid[i][j]);
        }
        printf("\n");
    }

}

char* removeDup(char* key){
    int i,j, index, flag, size;

    index = 0;
    size = strlen(key);
    char* arr = (char*)malloc(size);
    for(i = 0; i < size; i++){
        flag = 0;
        for(j = 0; j < size; j++){
            if(key[i] == arr[j]){
                flag = 1;
                break;
            }
        }
        if(flag == 0)
            arr[index++] = key[i];
    }
    return arr;
}