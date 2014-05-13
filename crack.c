#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crypt.h"

// Given a hash and a plaintext guess, return 1 if
// the hash of the guess matches the given hash.
// That is, return 1 if the guess is correct.
int tryguess(char *hash, char *guess)
{
    // Extract the salt from the hash
    char salt[9];
    strncpy(salt,(hash+3),8);
    salt[8]='\0';

    // Hash the guess using the salt
    char *trial = md5crypt(guess, salt);
    
    // Compare the two hashes
    
    return (!strcmp(trial,hash)); //will return 0 if they don't match, nonzero if match
}

// Given a hash and a dictionary of guesses,
// try all guesses and return the matching guess.
char *crack(char *hash, char *dict[])
{
    int i = 0;
    while (dict[i])
    {
        if (tryguess(hash, dict[i])) return dict[i];
        i++;
    }
    return NULL;
}

// Read in a file.
// The first line of the file is the number of lines in the file.
// Returns an array of strings, with the last element being a NULL
// indicating the end of the array.
char **read_file(char *fname)
{
    // Pointer to array of character pointers (strings)
    char **dict;

    printf("Reading %s\n", fname);
    FILE *d = fopen(fname, "r");
    if (! d) return NULL;

    // Get the number of lines in the file
    int numlines;
    fscanf(d, "%d", &numlines); //**am I going to need that extra space here?
    //fgets(numlines, sizeof(line), fname);
 
    // Allocate memory for the array of strings (character pointers)
    dict = (char **)malloc(((numlines+1)*sizeof(char *)));

    // Read in the rest of the file, allocting memory for each string
    // as we go. 
    //while(fscanf(d, "%s", ) != EOF) //***
    int i=0;
    dict[i] = (char *)malloc(30*sizeof(char));
    while(fgets(dict[i], 30, d) != NULL) //***that 30 needs to be fixed...
    {
	i++;
	dict[i] = (char *)malloc(30*sizeof(char));
    }
    // NULL termination. Last entry in the array should be NULL. *outside loop*
    dict[i]='\0';

    printf("Done\n");

    return dict;
}

int main(int argc, char *argv[])
{
    if (argc < 2) 
    {
        printf("Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    char **dictionary = read_file(argv[2]);
    char **hashes = read_file(argv[1]);

    int i = 0;

    // For each hash, try every entry in the dictionary.
    // Print the matching dictionary entry.
    while(i<4)
    {
	char *m=crack(hashes[i],&dictionary[i]);
	printf("%s", m[i]);
	i++;
    }
}
