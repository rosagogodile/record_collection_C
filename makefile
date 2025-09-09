compile: main.c record_release.c
	gcc -Wall -o main.exe main.c record_release.c

# dependency of compile
run: compile
	./main.exe

clean:
	rm main.exe