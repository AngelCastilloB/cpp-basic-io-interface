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
INCLUDING = -I./include

all: bio-sample

bio-sample: main.o  Application.o
	$(CC) -o bio-sample main.o Application.o $(LIBS)

main.o: main.cpp 
	$(CC) $(CFLAGS) $(INCLUDING) -c main.cpp

Application.o: src/Application.cpp
	$(CC) $(CFLAGS) $(INCLUDING) -c src/Application.cpp

clean:
	rm -f *.o $(PROGRAM)
