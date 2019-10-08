#include <iostream> 
#include <omp.h>

int main() {
	#pragma omp parallel 
	{
		std::cout << "Hello World\n";
		std::cout << "THREAD ID:" << omp_get_thread_num() << "\n";
		std::cout << "NUMBER OF THREADS: " <<omp_get_num_threads() << "\n"; 
	}
	return 0; 
}
