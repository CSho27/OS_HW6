all: global_omp_shubert.o local_omp_shubert.o shared_message_server.o  shared_message_client.o
	gcc -o global_omp_shubert global_omp_shubert.o -lm -fopenmp
	gcc -o local_omp_shubert local_omp_shubert.o -lm -fopenmp
	gcc -o shared_message_server shared_message_server.o -lrt -pthread
	gcc -o shared_message_client shared_message_client.o -lrt -pthread

global_omp_shubert.o: global_omp_shubert.c
	gcc -Wall -Werror -g -c global_omp_shubert.c -fopenmp
	
local_omp_shubert.o: local_omp_shubert.c
	gcc -Wall -Werror -g -c local_omp_shubert.c -fopenmp
	
shared_message_server.o: shared_message_server.c
	gcc -Wall -Werror -g -c shared_message_server.c -lrt
	
shared_message_client.o: shared_message_client.c
	gcc -Wall -Werror -g -c shared_message_client.c -lrt
	
clean:
	rm -f *.o
	rm -f global_omp_shubert
	rm -f local_omp_shubert
	rm -f shared_message_server
	rm -f shared_message_client