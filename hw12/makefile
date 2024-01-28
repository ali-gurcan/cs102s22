all:  clear clean compile run 

compile: main.c 
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -o test main.c -lm

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "-------------------------------------------"
	@./test
	@echo "Completed tests...."

clean:
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
clear:
	@clear	