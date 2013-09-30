#include "rsalib.h"

unsigned long int encrypt(unsigned long long in, unsigned long long n, unsigned long long d) //encryption
{
	mpz_t tmp;
	mpz_t out;
	mpz_t exp;
	mpz_t mod;
    
	mpz_init(tmp);
	mpz_init(out);
	mpz_init(exp);
	mpz_init(mod);
    
	mpz_set_ui(tmp, in);
	mpz_set_ui(exp, d);
	mpz_set_ui(mod, n);
    
	mpz_powm(out, tmp, exp, mod);
    
	//gmp_printf("Returning %Zd\n", out);
	return mpz_get_ui(out);
}

unsigned long int decrypt(unsigned long long in, unsigned long long n, unsigned long long d)
{
	return encrypt(in, n, d);
}

int rsa_encrypt_file(char * keyfilename, char * filename, char * filename2)
{
	unsigned long n, e;
	unsigned long i;
	FILE * f;
	FILE * f2;
	FILE * key;
    
	if ((key = fopen(keyfilename, "rb")) == NULL)
	{
		printf("Cannot open key\n");
		return 2;
	}
    
	fread(&n, sizeof(unsigned long), 1, key);
	fread(&e, sizeof(unsigned long), 1, key);
    
	fclose(key);
    
	if ( (f = fopen(filename, "r")) == NULL || (f2 = fopen(filename2, "wb")) == NULL)
	{
		printf("Error, file cannot be found or opened\n");
		return 1;
	}
    
	unsigned int enc = 0;
	enc = encrypt(15, n, e);
    
	while ( (i = fgetc(f)) != EOF )
	{
		enc = decrypt(i, n, e);
		fwrite(&enc, sizeof(unsigned int), 1, f2);
		//fprintf(f2, "%lu ", enc);
	}
	fflush(f2);
    
	fclose(f);
	fclose(f2);
    
	return 0;
}

int rsa_decrypt_file(char * keyfilename, char * filename, char * filename2)
{
	unsigned long n, e;
	unsigned int i;
	FILE * f;
	FILE * f2;
	FILE * key;
	bool found = false;
    
	if ((key = fopen(keyfilename, "rb")) == NULL)
	{
		printf("Cannot open key\n");
		return 2;
	}
    
	fread(&n, sizeof(unsigned long), 1, key);
	fread(&e, sizeof(unsigned long), 1, key);
    
	fclose(key);
    
	if ( (f = fopen(filename, "r")) == NULL || (f2 = fopen(filename2, "wb")) == NULL)
	{
		printf("Error, file cannot be found or opened\n");
		return 1;
	}
    
	unsigned char enc = 0;
	enc = encrypt(15, n, e);
    
	//while (fscanf(f, "%lu", &i) > 0)
	while (fread(&i, sizeof(unsigned int), 1, f) > 0)
	{
		enc = decrypt(i, n, e);
		fwrite(&enc, sizeof(unsigned char), 1, f2);
		//fprintf(f2, "%c", enc);
	}
	fflush(f2);
    
	fclose(f);
	fclose(f2);
    
	return 0;
}
