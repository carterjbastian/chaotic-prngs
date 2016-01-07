#
#  A Makefile for the chaotic-prngs software.
#  Using the makefile you can clean, build, and test all of the available prngs
#

################################
# CONSTANTS:
# Directory paths for project
SRCDIR = ./src
OBJDIR = ./objs
OUTDIR = ./output
TRACEDIR = ./traces
TEST_DIR = ./testlogs

# Source Files, Object Files, Binary Files, and Includes
SRCS = $(SRCDIR)/utils.c $(SRCDIR)/maps.c $(SRCDIR)/generator.c
INCS = $(SRCDIR)/utils.h $(SRCDIR)/maps.h $(SRCDIR)/generator.h
OUT = RunPRNG

# C Compiler
CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -ggdb

################################
# TARGETS:
# all: 		Build all the prngs
# clean: 	Remove all output files
# test-short:	Generate small output files and run short tests on them
# test:		Build, generate output, and run the longer set of tests

all: $(SRCS) $(INCS)
	$(CC) $(CFLAGS) $(SRCS) $(SRCDIR)/run_prng.c -o $(OUT)

clean:
	rm -f ./traces/*.txt ./output/*.txt
	rm -f ./testlogs/*.log
	rm -f $(OUT)
	rm -rf *.dSYM
	rm -f ./performance.log

