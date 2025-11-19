# Filter

CS50 Week 4 - C (Memory)

## What it does

Applies filters to BMP images using pixel manipulation.

## Filters Implemented

- **Grayscale** - Converts image to black and white
- **Sepia** - Applies a reddish-brown tone
- **Reflect** - Mirrors image horizontally
- **Blur** - Applies a box blur effect

## How it works

Reads a BMP file, manipulates pixel values in memory, and writes the filtered image to a new file.

## Usage
```bash
./filter -g input.bmp output.bmp    # Grayscale
./filter -s input.bmp output.bmp    # Sepia
./filter -r input.bmp output.bmp    # Reflect
./filter -b input.bmp output.bmp    # Blur
```

## Example
```bash
$ ./filter -b images/yard.bmp out.bmp
```

## Files

- `helpers.c` - Filter implementation
- `helpers.h` - Header file
- `filter.c` - Main program (provided by CS50)
- `bmp.h` - BMP file format structures (provided by CS50)

## Problem Description

[CS50 Filter Problem](https://cs50.harvard.edu/x/2024/psets/4/filter/less/)
