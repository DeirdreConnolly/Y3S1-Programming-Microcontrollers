
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

//--------------------------------------//
//	split_a_string_into_words			//
//--------------------------------------//
char** split_a_string_into_words(char str[], int* num_words) {
    //0. The variable we are going to return
    char** words = NULL;

    //1. At the beginning we have not processed any word, thus:
    //current_word = 0 and current_char = 0 (at the beginning of str).
    unsigned int current_char = 0;
    (*num_words) = 0;

    //2. While we have not processed the entire str
    while (current_char < strlen(str)) {
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
        char* q = (char*)malloc((dist + 1) * sizeof(char));
        strncpy(q, &str[current_char], dist);
        q[dist] = '\0';

        //2.4. We increase the number of words in our array of words
        char** new_words = (char**)realloc(words, ((*num_words) + 1) * sizeof(char*));
        if (new_words != NULL) {
            words = new_words;
            words[(*num_words)] = q; //We make words[(*num_words)] to point to q.
        }

        //2.5. We update the number of words processed and the next_char we are pointing at in str.
        (*num_words) = (*num_words) + 1;
        current_char = current_char + (dist + 1);

    }

    return words;

}

//--------------------------------------//
//	main								//
//--------------------------------------//
int main() {

    //Get the string
    char a[] = "This is my first text";
    //char a[] = "This is  my first text ";

    //1. We create the array for the words.
    char** words = NULL;
    int num_words = 0;

    words = split_a_string_into_words(a, &num_words);

    //3. Print each word.
    printf("Number of words in --%s-- = %d\n", a, num_words);
    for (int i = 0; i < num_words; i++) {
        printf("words[%d] = %s\n", i, words[i]);
    }

    //4. Free the memory.
    for (int i = 0; i < num_words; i++)
        free(words[i]);
    free(words);

    return 0;

}





