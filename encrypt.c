#include "rsalib.h"

int main(int argc, char * * argv)
{
	unsigned long n, e;
	unsigned long i;
	char * filename  = malloc(30); //29-char max
	char * filename2 = malloc(30);
	char * keyfilename = malloc(30);
	FILE * f;
	FILE * f2;
	FILE * key;
    bool argd = false;
    
    if (argc > 3)
    {
        strcpy(keyfilename, argv[1]);
        strcpy(filename, argv[2]);
        strcpy(filename2, argv[3]);
        argd = true;
    }
    else
    {
        printf("Key: ");
        scanf("%s", keyfilename);
    }
    
	if ((key = fopen(keyfilename, "rb")) == NULL)
	{
		printf("Cannot open key\n");
		return 2;
	}
    
	fread(&n, sizeof(unsigned long), 1, key);
	fread(&e, sizeof(unsigned long), 1, key);
    
	fclose(key);
    
    if (!argd)
    {
        printf("File: ");
        scanf("%s", filename);
        printf("Output: ");
        scanf("%s", filename2);
    }

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
