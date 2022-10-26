/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_STR 100
#define NUM_WORDS 10

// Input: string A
// Output: array of strings WORDS, size of array NUM_WORDS
// Local variable CURRENT_CHAR (represents char of a to which we are pointing)
// Loop to iterate through the string
// Attempt 1: without malloc, realloc, or free; 1D array

int
split_string_into_words (char str[], char *words[])
{

  // Starting position:
  // current_word = 0;
  // current_char = 0;

  unsigned int current_char = 0;
  int num_words = 0;

  // Processing the string
  while ((current_char < strlen (str)) && (num_words < NUM_WORDS))
    {

      // Look for next blank space
      char *p = strchr (&str[current_char], ' ');

      // Measure next word after blank space
      int dist = 0;

      // If there is a blank space, measure word by getting dist from start of string
      if (p != NULL)
	{
	  dist = (p - &str[current_char]);

	  // If there is no blank space, take length of string as length of word
	}
      else
	dist = strlen (&str[current_char]);
    }

  // Assign word to array of words
  char *q = words[num_words];
  strncpy (q, &str[current_char], dist);	// good practice to use strncopy, defensive programming against buffer overflows
  q[dist] = "/0";		// NULL

  // Update number of processed words, and next_char we are pointing to in string
  num_words = (num_words + 1);
  current_char = (current_char + (dist + 1));

}

return num_words;

}




int
main ()
{

  // Get string
  char a[] = "This is a test string.";

  // If str is smaller than SIZE_STR, we process it
  if (strlen (a) < SIZE_STR)
    {

      // Create array for words
      char *words[NUM_WORDS];

      for (int i = 0; i < NUM_WORDS, i++;)
	{
	  char w[SIZE_STR] words[i] = &w[0];
	}
      int num_words = 0;

      // Split words of a, put them into words array
      num_words = split_string_into_words (a, words);

      // Print each word
      printf ("Number of words in --%s--: %d\n", a, num_words);	// %s string, %d integer

      for (int i = 0; i < num_words, i++;)
	{
	  printf ("Words[%d]: %s\n", i, words[i]);

	}

      return 0;

    }

}
