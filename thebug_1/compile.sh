#!/bin/sh
gcc -o captcha01 captcha01.c -O3 -funroll-all-loops -march=native -Wall -ljpeg -lm
