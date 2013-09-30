#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gmp.h>
#include <time.h>
#define true 1
#define false 0

typedef char bool;

unsigned long int encrypt(unsigned long long in, unsigned long long n, unsigned long long d);
unsigned long int decrypt(unsigned long long in, unsigned long long n, unsigned long long d);
int rsa_encrypt_file(char * keyfilename, char * filename, char * filename2);
int rsa_decrypt_file(char * keyfilename, char * filename, char * filename2);
