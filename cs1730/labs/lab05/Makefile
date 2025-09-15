labName=lab05
compileCmd=gcc -Wall $(labName).c -g -o $(labName).out

compile: $(labName).out

$(labName).out: $(labName).c
	$(compileCmd)

run: $(labName).out
	./$(labName).out -decimal -16 -bits 12
	./$(labName).out -bits 15 -decimal -119
	./$(labName).out -binary 110101

clean:
	rm $(labName).out

