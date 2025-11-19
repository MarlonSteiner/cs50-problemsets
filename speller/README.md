# Speller

CS50 Week 5 - C (Data Structures)

## What it does

A spell checker that identifies misspelled words in a text file using a hash table.

## How it works

1. Loads a dictionary of words into a hash table
2. Reads a text file and checks each word against the dictionary
3. Reports misspelled words and performance statistics

## Implementation

Uses a hash table data structure with:
- `hash()` - Hash function to determine bucket
- `load()` - Loads dictionary into hash table
- `check()` - Checks if a word is in the dictionary
- `size()` - Returns number of words in dictionary
- `unload()` - Frees all allocated memory

## Usage
```bash
./speller texts/lalaland.txt
```

Or with a custom dictionary:
```bash
./speller dictionaries/small texts/cat.txt
```

## Performance

Reports:
- Words misspelled
- Words in dictionary
- Words in text
- Time to load, check, size, and unload

## Files

- `dictionary.c` - Hash table implementation
- `dictionary.h` - Header file
- `speller.c` - Main program (provided by CS50)
- `dictionaries/` - Dictionary files
- `texts/` - Sample text files

## Problem Description

[CS50 Speller Problem](https://cs50.harvard.edu/x/2024/psets/5/speller/)
