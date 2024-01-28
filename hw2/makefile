all: clear clean compile run

compile: main.c util.c util.h
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -o test main.c util.c -lm

run:
	@echo "-------------------------------------------"
	@echo "Running the test...."
	@echo "============================================"
	@./test
	@echo "============================================"
	@echo "Completed the test...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
clear:
	@clear	