# DNA

CS50 Week 6 - Python

## What it does

Identifies a person from a DNA sequence by analyzing Short Tandem Repeats (STRs).

## How it works

1. Reads a CSV database of people and their STR counts
2. Reads a DNA sequence from a text file
3. Counts the longest consecutive repeats of each STR
4. Matches the counts against the database
5. Prints the matching person or "No match"

## Usage
```bash
python dna.py databases/large.csv sequences/5.txt
```

## Example
```bash
$ python dna.py databases/small.csv sequences/1.txt
Bob
```

## Files

- `dna.py` - Main program
- `databases/` - CSV files with STR counts per person
- `sequences/` - Text files with DNA sequences

## Problem Description

[CS50 DNA Problem](https://cs50.harvard.edu/x/2024/psets/6/dna/)
