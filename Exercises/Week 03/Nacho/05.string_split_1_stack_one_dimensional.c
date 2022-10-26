
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_STR 100
#define NUM_WORDS 10

//--------------------------------------//
//	split_a_string_into_words			//
//--------------------------------------//
int split_a_string_into_words(char str[], char* words[]) {
    //1. At the beginning we have not processed any word, thus:
    //current_word = 0 and current_char = 0 (at the beginning of str).
    unsigned int current_char = 0;
    int num_words = 0;

    //2. While we have not processed the entire str
    while ((current_char < strlen(str)) && (num_words < NUM_WORDS)) {
        //2.1. We look for the next blank space
        char* p = strchr(&str[current_char], ' ');

        //2.2. We check for the next blank space, to measure the length of the next word of str
        int dist;
        if (p != NULL) {
            //If there is such a blank space, we measure the distance to the start of the string to measure the length of the word.
            dist = p - &str[current_char];
        }
        else {
            //If there is not such a blank space, we take the length of the string as the length of the word.
            dist = strlen(&str[current_char]);
        }

        //2.3. We asign the word to our array of words
        char* q = words[num_words];
        strncpy(q, &str[current_char], dist);
        q[dist] = '\0';

        //2.4. We update the number of words processed and the next_char we are pointing at in str.
        num_words = num_words + 1;
        current_char = current_char + (dist + 1);
    }

    return num_words;

}

//--------------------------------------//
//	main				//
//--------------------------------------//
int main() {

    //Get the string
    char a[] = "This is my first text";

    //If the string is smaller than SIZE_STR we process it
    if (strlen(a) < SIZE_STR) {
        //1. We create the array for the words.
        char* words[NUM_WORDS];
        for (int i = 0; i < NUM_WORDS; i++) {
            char w[SIZE_STR];
            words[i] = &w[0];
        }
        int num_words = 0;

        /*
        //Why does it not work?
        for (int i = 0; i < NUM_WORDS; i++) {
            printf("Address of word[%d] = %p\n", i, words[i]);
            char* p = words[i];
        }
        */

        //2. Split the words of a and put them into words.
        num_words = split_a_string_into_words(a, words);

        //3. Print each word.
        printf("Number of words in --%s-- = %d\n", a, num_words);
        for (int i = 0; i < num_words; i++)
            printf("words[%d] = %s\n", i, words[i]);
    }

    return 0;

}

