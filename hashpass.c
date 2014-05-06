#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "crypt.h"

// Compile with: clang mkpasswd.c md5crypt.c -o mkpasswd -l readline -l ssl

char *mksalt()
{
    static char s[9];
    for (int i = 0; i < 8; i++)
    {
        int r = random() % 64;
        s[i] = base64chars[r];
    }
    return s;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
	{
	    fprintf(stderr, "Usage: %s password [salt]\n", argv[0]);
		exit(1);
	}

    char *pass = argv[1];
    char *salt = argv[2];
    char *hash;

    // Seed the random number generator
    srandom(getpid());

    if (!salt) salt = mksalt();

    hash = md5crypt(pass, salt);

    printf("%s\n", hash);
}
