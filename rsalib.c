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