
// works..but doesn't run
int letters = strlen(text);


// Coding Section that doesn't fucking work...



// Count Number of Letters, Sentences & Words
    int i = 0, letters = 0;
    while (text[i] != '\n')
    {
         if ((islower(text[i])) || (isupper(text[i])))
        {
            letters++;
        }
        ++i;
    }

    // examine problem
    printf("letters: %i\n", letters);
    printf("words: %i\n", words);
    printf("sentences: %i\n", sentences);
    printf("Letters per 100 words: %f\n", L);
    printf("Sentences per 100 words: %f\n", S);
