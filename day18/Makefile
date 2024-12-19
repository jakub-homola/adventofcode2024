
.PHONY: compile clean run

compile: task1.x task2.x task2.1.x task2.2.x task2.3.x

run: compile
	./task1.x < input.txt
	./task2.x < input.txt
	./task2.1.x < input.txt
	./task2.2.x < input.txt
	./task2.3.x < input.txt
	./task1.x 213 < input2.txt
#	./task2.x 213 < input2.txt
	./task2.1.x 213 < input2.txt
	./task2.2.x 213 < input2.txt
	./task2.3.x 213 < input2.txt

clean:
	rm -f *.x

%.x: %.cpp Makefile ../helpers/helpers.hpp
	g++ -g -O2 $< -o $@

