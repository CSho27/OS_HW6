all: global_omp_shubert.o
	gcc -o global_omp_shubert global_omp_shubert.o -lm -fopenmp

global_omp_shubert.o: global_omp_shubert.c
	gcc -Wall -Werror -g -c global_omp_shubert.c -fopenmp
	
clean:
	rm -f *.o
	rm -f global_omp_shubert