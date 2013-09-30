#include "rsalib.h"

int main(int argc, char * * argv)
{
    char * filename  = malloc(30); //29-char max
	char * filename2 = malloc(30);
	char * keyfilename = malloc(30);
    
    if (argc > 3)
    {
        strcpy(keyfilename, argv[1]);
        strcpy(filename, argv[2]);
        strcpy(filename2, argv[3]);
    }
    else
    {
        printf("Key: ");
        scanf("%s", keyfilename);
        printf("File: ");
        scanf("%s", filename);
        printf("Output: ");
        scanf("%s", filename2);
    }
    
    rsa_encrypt_file(keyfilename, filename, filename2);
}