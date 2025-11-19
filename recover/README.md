# Recover

CS50 Week 4 - C (Memory)

## What it does

Recovers deleted JPEG images from a forensic image of a memory card.

## How it works

1. Reads a raw binary file (memory card image) block by block
2. Identifies JPEG file signatures (headers)
3. Extracts and writes each JPEG to a separate file
4. Names files sequentially (000.jpg, 001.jpg, etc.)

## Usage
```bash
./recover card.raw
```

This generates recovered JPEG files: `000.jpg`, `001.jpg`, `002.jpg`, etc.

## How JPEGs are identified

JPEGs start with a specific byte pattern:
- `0xff 0xd8 0xff 0xe*` (where * is 0-15)

The program searches for this signature to detect the start of each image.

## Files

- `recover.c` - Main program
- `card.raw` - Forensic image (provided by CS50)

## Problem Description

[CS50 Recover Problem](https://cs50.harvard.edu/x/2024/psets/4/recover/)
