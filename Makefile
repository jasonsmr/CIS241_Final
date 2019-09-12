#
#############################################################################
#Final Assignmant C Program "forker_lib" & "forker"
#
#Author: Jason M Rupright
#School GVSU
#Class 241
#
#############################################################################
#
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = clang
CFLAGS  = -g -Wall


# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: forker.bin

# To create the object file forker_lib.o, we need the source
# files forker_lib.c, and forker_lib.h.
#
forker_lib.o:  forker_lib.c forker_lib.h
	$(CC) $(CFLAGS) -c forker_lib.c
	
# To create the object file forker.o we need the code file
# forker.c
#
forker.o: forker.c
	$(CC) $(CFLAGS) -c forker.c

# To create the executable file forker.bin we need the object files
# forker.o, and forker_lib.o:
#
forker.bin: forker_lib.o forker.o
	$(CC) $(CFLAGS) -o forker.bin forker_lib.o forker.o

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) forker *.o *~ *.bin