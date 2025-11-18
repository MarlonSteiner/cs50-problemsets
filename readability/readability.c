#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);

int main(void)
{
    // Prompt user for Word
    string text = get_string("Text: ");

    // Count Number of Letters
    int letters = count_letters(text);

    // Count Number of Words
    int words = count_words(text);

    // Count Number of Sentences
    int sentences = 0;
    for (int k = 0; k < strlen(text); k++)
    {
        if (text[k] == '.' || text[k] == '!' || text[k] == '?')
        {
            sentences++;
        }
    }

    // Average Letters per Words
    float L = ((float) letters / words) * 100;

    // Average Sentences per Words
    float S = ((float) sentences / words) * 100;

    // Coleman-Liau index
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print Grade
    if (index >= 16)
    {
        index = 16;
        printf("Grade %i+\n", index);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// function to count letters
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = tolower(text[i]);
        if (islower(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

// function to count words
int count_words(string text)
{
    int words = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    if (words == 1)
    {
        words = 0;
    }
    return words;
}
