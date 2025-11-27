#include "main.h"

int main() {
    char password[14]; 
    int order[4] = {0, 0, 0, 0};
    int index = 0;
    unsigned char ascii[8];
    char numbers[4] = {0};
    char special[3] = {0};
    FILE *fp = fopen("/dev/urandom", "r");
    
    
    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)GETPID() ^ (unsigned int)clock();
    srand(seed); 
    
    int rumor = get_file_noise(fp);
    srand(seed + rumor);

    d4(order, fp);
    d8(special, fp);
    d10(numbers, fp);
    d20_d12_d6(ascii, fp);
    
    for (int i = 0; i < 4; i++) {
        switch (order[i]) {
            case 1: 
                for (int j = 0; j < 7; j++) {
                    password[index + j] = ascii[j];
                }
                index += 7;
                break;
            case 2: 
                for (int j = 0; j < 3; j++) {
                    password[index + j] = numbers[j];
                }
                index += 3;
                break;
            case 3: 
                for (int j = 0; j < 2; j++) {
                    password[index + j] = special[j];
                }
                index += 2;
                break;
            case 4: 
                password[index] = '@';
                index++;
                break;
        }
    }

    password[index] = '\0';
    printf("Generated password: %s\n", password);
    fclose(fp);
    return 0;
}

int get_file_noise(FILE *fp) {
    unsigned int number = 0;
    
    if (fp == NULL) {
        return rand(); 
    }

    fread(&number, sizeof(number), 1, fp);
    
    return number;
}

void d20_d12_d6(unsigned char *ascii, FILE *fp) {
    for (int i = 0; i < 7; i++) {
        int noise = get_file_noise(fp);
        int upper = (rand() + noise) % 2;

        if (upper)
            ascii[i] = 65 + (rand() + noise) % 26;
        else
            ascii[i] = 97 + (rand() + noise) % 26;
    }
    ascii[7] = '\0';
}

void d10(char *numbers, FILE *fp) {
    for (int i = 0; i < 3; i++) {
        int noise = get_file_noise(fp);
        numbers[i] = 48 + (rand() + noise) % 10;
    }
    numbers[3] = '\0';
}

void d8(char *special, FILE *fp) {
    for (int i = 0; i < 2; i++) {
        int noise = get_file_noise(fp);
        special[i] = 33 + (rand() + noise) % 8;
    }
    special[2] = '\0';
}

void d4(int *order, FILE *fp) {
    int index = 0;
    
    while (index < 4) {
        int noise = get_file_noise(fp);
        
        int tmp = 1 + (rand() + noise) % 4; 
        
        int exists = 0;
        for (int i = 0; i < index; i++) {
            if (order[i] == tmp) {
                exists = 1;
                break;
            }
        }
        if (!exists) {
            order[index] = tmp;
            index++;
        }
    }
}