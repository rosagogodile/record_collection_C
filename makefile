# Rosa Knowles
# 9/17/2025
# makefile for the record collection organizer

# compiles and then runs the program
run: main.exe
	./main.exe

# compiles the record release library into an object file
# packs it into a static library using the archiver command
# removes the object file
librecord_release.a: record_release.c record_release.h
	gcc -c record_release.c -o record_release.o
	ar rcs librecord_release.a record_release.o
	rm record_release.o

# compiles the save manager library
# does the same stuff that the block above does, except it also links this library with the record release library
libsavmgr.a: savmgr.c savmgr.h librecord_release.a
	gcc -c savmgr.c -L . -lrecord_release -o savmgr.o
	ar rcs libsavmgr.a savmgr.o
	rm savmgr.o

# compiles the program using the library and main.c
main.exe: main.c librecord_release.a libsavmgr.a
	gcc -Wall -Wformat=0 -o main.exe main.c -L . -lrecord_release -lsavmgr

# removes all compiled executables and libraries
# `rm -f *.a` : removes all files with the .a extension, -f forces this to happen 
clean:
	rm main.exe
	rm -f *.a