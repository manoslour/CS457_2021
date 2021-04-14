/*************************************************************
 * @file   main.c                                            *
 * @author Lourakis Manos <csd3153@csd.uoc.gr>  	         *
 *                                                    	     *
 * @brief  Main file for the needs of CS457 Assignment 1     *
 ************************************************************/

#include "hy457_crypto.h"

int main(int argc, char **argv){

    FILE *fin;
    int N, circ, len;
    long int textSize;
    char *mode;
    uint8_t *buff, *key, *keyword, *encryptedText, *decryptedText;
    uint8_t* keys[8];
    char *p_key = "HELLOWORLD";

    buff = (uint8_t*)malloc(BUFFER_SIZE * sizeof(uint8_t));
    keyword = (uint8_t*)malloc(BUFFER_SIZE * sizeof(uint8_t));

    if(argc != 3){
        printf("Error, Wrong input\n");
        return EXIT_FAILURE;
    }

    if( (fin = fopen(argv[2], "r")) == NULL){
        printf("Cant open file: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    mode = argv[1];
    fgets(buff, BUFFER_SIZE, fin);
    buff[strcspn(buff, "\n")] = 0; //Removes trailing newline char from fgets() input
    textSize = strlen(buff);

    
    
    switch (*mode)
    {
        case 'O':
            buff = strdup(removeIllegal(buff));
            key = strdup(generateKey(textSize));
            encryptedText = strdup(otp_encrypt(buff, key));
            decryptedText = strdup(otp_decrypt(encryptedText, key));
            break;
        case 'C':
            printf("Enter N: ");
            scanf("%d", &N);
            buff = strdup(removeIllegal(buff));
            encryptedText = strdup(caesar_encrypt(buff, N));
            decryptedText = strdup(caesar_decrypt(encryptedText, N));
            break;
        case 'A':
            buff = strdup(removeAffineIllegal(buff));
            encryptedText = strdup(affine_encrypt(buff));
            decryptedText = strdup(affine_decrypt(encryptedText));
            break;
        case 'F':
            for(int i = 0; i < ROUNDS; i++){
                keys[i] = strdup(generateKey(32));
            }
            encryptedText = feistel_encrypt(buff, keys);
            //decryptedText = feistel_decrypt(encryptedText, keys);
            break;
        case 'P':
            playfair_keymatrix(p_key);
            break;
        default:
            printf("Invalid Mode\n");
            break;
    }

    fclose(fin);
    return 0;
}