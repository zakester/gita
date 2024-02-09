@echo off
zig cc -std=c11 -D_CRT_SECURE_NO_WARNINGS src/gita.c -o gita.exe
gita.exe zakester
