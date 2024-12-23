
.PHONY: compile clean run

compile: task1.x task2.x task2.1.x

run: compile
	./task1.x < input.txt
	./task2.x < input.txt
	./task2.1.x < input.txt

clean:
	rm -f *.x

%.x: %.cpp Makefile ../helpers/helpers.hpp
	g++ -std=c++20 -g -O2 $< -o $@ -fmax-errors=1

