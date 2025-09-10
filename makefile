# Rosa Knowles
# 9/10/2025
# makefile for the record collection organizer

# compiles and then runs the program
run: main.exe
	./main.exe

# compiles the library into an object file
# packs it into a static library using the archiver command
# removes the object file
librecord_release.a: record_release.c record_release.h
	gcc -c record_release.c -o record_release.o
	ar rcs librecord_release.a record_release.o
	rm record_release.o

# compiles the program using the library and main.c
main.exe: main.c librecord_release.a
	gcc -Wall -o main.exe main.c -L . -lrecord_release

# removes all compiled executables and libraries
clean:
	rm main.exe
	rm librecord_release.a