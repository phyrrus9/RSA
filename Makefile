all: encrypt decrypt keygen
encrypt: encrypt.o rsalib.o
	cc -o encrypt encrypt.o rsalib.o -lgmp
decrypt: decrypt.o rsalib.o
	cc -o decrypt decrypt.o rsalib.o -lgmp
keygen: keygen.o rsalib.o
	cc -o keygen  keygen.o rsalib.o -lgmp
encrypt.o: encrypt.c
	cc -c -o encrypt.o encrypt.c
decrypt.o: decrypt.c
	cc -c -o decrypt.o decrypt.c
keygen.o: keygen2.c
	cc -c -o keygen.o keygen2.c
rsalib.o: rsalib.c rsalib.h
	cc -c -o rsalib.o rsalib.c
clean:
	rm -f keygen.o decrypt.o encrypt.o rsalib.o
	rm -f keygen decrypt encrypt
install: encrypt decrypt keygen
	cp encrypt /usr/bin/rsa_encrypt
	cp decrypt /usr/bin/rsa_decrypt
	cp keygen /usr/bin/rsa_keygen
uninstall: /usr/bin/rsa_encrypt /usr/bin/rsa_decrypt /usr/bin/rsa_keygen
	rm /usr/bin/rsa_encrypt
	rm /usr/bin/rsa_decrypt
	rm /usr/bin/rsa_keygen
