#
#   Copyright (c) 2023 Mihai Zegheru
#   All rights reserved.
#

CC=gcc
CFLAGS=-Wall -Wextra -std=c99

SOURCES=main.c

build:
	$(CC) $(CFLAGS) $(SOURCES) -o SimpleMachineLearning.exe
