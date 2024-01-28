all: clear clean compile run

compile: main.c 
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -o test main.c 

run:
	@echo "-------------------------------------------"
	@echo "Running the test...."
	@echo "======================================================================="
	@./test
	@echo "======================================================================="
	@echo "Completed the test...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
clear:
	@clear	