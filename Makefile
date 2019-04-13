#
# File: Makefile
#
# Date: Wed Mar 13 17:06:00 EST 2019
#
# Use of this software is subject to the terms of an end user license agreement.
#

PROGRAM = bio-sample

CC        = g++
CFLAGS    = -g -std=c++11 -Wall -Wextra -Werror
LIBS      = -L.  -lgdiplus -mwindows
INCLUDING = -I./include/Bio

all: bio-sample

bio-sample: main.o  Display.o
	$(CC) -o bio-sample main.o Display.o $(LIBS)

main.o: main.cpp 
	$(CC) $(CFLAGS) $(INCLUDING) -c main.cpp

Display.o: src/Display/Display.cpp
	$(CC) $(CFLAGS) $(INCLUDING) -c src/Display/Display.cpp

clean:
	rm -f *.o $(PROGRAM)
