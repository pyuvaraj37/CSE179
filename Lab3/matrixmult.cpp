#include <omp.h>
#include <stdlib.h> 
#include <cstdlib>
#include <sys/time.h>
#include <iostream>
 
using namespace std;

int main() {

 	int n;
 	int m; 
	int i, j;
	
	struct timeval start, end;
	
	cout << "Enter m: " << endl;
	cin >> m;

	cout << "Enter n: " << endl; 
	cin >> n; 

	int mat[m][n];
	int arr[n];
	int prod[n];
	
	cout << "Populating.." << endl;
	#pragma omp for schedule(dynamic, 5)
	for (i = 0; i < m; i++) {
	  for (j = 0; j < n; j++) {
	    mat[i][j] = rand() % 100;
	  }
	}
	
	#pragma omp for schedule(dynamic, 5)
	for (j = 0; j < n; j++) {
		arr[j] = rand() % 100;
	}
	
	gettimeofday(&start, NULL);
	cout << "Calculating.." << endl;
	#pragma omp for 
	for(i = 0; i < m; i++) {

	  for (j = 0; j < n; j++) {

	    prod[i] += mat[i][j] * arr[j];

	  }

	}
	gettimeofday(&end, NULL);

	cout << "ms = " << (end.tv_usec - start.tv_usec) << endl;


}
 
