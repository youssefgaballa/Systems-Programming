labName=lab08
compileCmd=gcc -Wall -pedantic-errors $(labName).c -g -o $(labName).out

compile: $(labName).out

$(labName).out: $(labName).c
	$(compileCmd)

run: $(labName).out
	./$(labName).out 8 1 2

clean:
	rm $(labName).out

