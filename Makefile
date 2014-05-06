CC=clang
NUM_HASHES=100
ROCKYOU=rockyou2000.txt

all: crack hashpass

md5crypt.o: md5crypt.c crypt.h
	$(CC) -c md5crypt.c

crack: crack.c md5crypt.o 
	$(CC) crack.c md5crypt.o -o crack -l ssl

hashpass: hashpass.c md5crypt.o
	$(CC) hashpass.c md5crypt.o -o hashpass -l ssl -l readline

clean:
	rm -f *.o crack hashpass

hashes: hashpass
	shuf -n $(NUM_HASHES) $(ROCKYOU) > passwords.txt
	echo $(NUM_HASHES) > md5.txt
	for i in `cat passwords.txt`; do ./hashpass $$i >> md5.txt ; done

test:
	./crack md5.txt $(ROCKYOU)
