#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int compute_score(string word);

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 2, 3};
int LETTERS[] = {'a', 'b', 'c'};

int main(void)
{
    // Assigning Letters to Numbers
    for (int i = 0; i < 3; i++)
    {
        LETTERS[i] = POINTS[i];
    }
    printf("a = %i\n",LETTERS[0]);
    printf("b = %i\n",LETTERS[1]);
    printf("c = %i\n",LETTERS[2]);
    printf("\n");

    // Prompt User
    string prompt = get_string("word: ");
    printf("Word: %i\n", compute_score(prompt));
}

//function
int compute_score(string word)
{
    int value = 0;
    for (int j = 0; j < strlen(word); j++)
    {
        value += word[j];
    }
    return value;
}
