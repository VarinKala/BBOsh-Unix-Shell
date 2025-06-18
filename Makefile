all: dir_compile date_compile main_compile main_run clean


main_run:
	@./Q2_main

main_compile:
	@gcc main.c -o Q2_main

dir_compile:
	@gcc dir.c -o DIR

date_compile:
	@gcc date.c -o DATE


clean:
	@rm Q2_main
	@rm DIR
	@rm DATE