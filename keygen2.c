#include "rsalib.h"

unsigned long modInverse(unsigned long a, unsigned long m)
{
	int x;
	a %= m;
	for(x = 1; x < m; x++)
	{
		if((a*x) % m == 1)
			return x;
	}
	return 0;
}
unsigned long totient(unsigned long p, unsigned long q)
{
	return (p - 1)*(q - 1);
}

bool isprime(unsigned long n)
{
	unsigned long i;
	for (i = 2; i < n; i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}


int main(int argc, char * * argv)
{
	unsigned long p, q;
	unsigned long x, n, d, e;
	unsigned long i;
	FILE *pub = fopen("rsa.pub", "wb");
	FILE *pri = fopen("rsa.pri", "wb");
	bool found = false;
	bool random = true;
	bool debug = false;

	random = argc > 1 ? false : true;

	srand(time(0));
	if (random)
	{
		p = rand() % 16383;
		printf("Using p=%lu\n", p);
		while (!isprime(p))
		{
			p++;
		}
		while (q < p)
		{
			q = rand() % 16383 + 16380;
		}
		printf("Using q=%lu\n", q);
		while (!isprime(q))
		{
			q++;
		}
	}
	else
	{
		printf("P (prime): ");
		scanf("%lu", &p);
		printf("Q (prime): ");
		scanf("%lu", &q);
	}

	n = p*q;
	x = totient(p, q);

	srand(time(0));

	for (i = rand() % x; i < x && !found; i++)
	{
		if (isprime(i) && x % i != 0)
		{
			e = i;
			found = true;
		}
	}

	//printf("E (coprime): ");
	//scanf("%lu", &e);

	d = modInverse(e, x);

	printf("Public:  n=%lu\te=%lu\n", n, e);
	printf("Private: n=%lu\td=%lu\n", n, d);
	fwrite(&n, sizeof(unsigned long), 1, pub);
	fwrite(&n, sizeof(unsigned long), 1, pri);
	fwrite(&e, sizeof(unsigned long), 1, pub);
	fwrite(&d, sizeof(unsigned long), 1, pri);
	fflush(pub);
	fflush(pri);
	fclose(pub);
	fclose(pri);
	if (debug)
	{
		printf("p=%lu\tq=%lu\tn=%lu\n"
	       		"x=%lu\td=%lu\n\n",
			p, q, n, x, d);
	}
	printf("Testing with value '15'\n");
	unsigned long int enc = 0;
	enc = encrypt(15, n, e);
	printf("Encrypted: %lu\t", enc);
	enc = decrypt(enc, n, d);
	printf("Decrypted: %lu\n", enc);

	return 0;
}
