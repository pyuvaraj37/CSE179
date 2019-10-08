#include <iostream>
#include <sys/time.h>

using namespace std;

int main() {
    int n, firstTerm = 1, secondTerm = 1, nextTerm;
    struct timeval start, end;
    cout << "Enter number of terms: ";
    cin >> n;

    cout << "Fibonacci Series: " << firstTerm << " + " << secondTerm << " + ";
    
    gettimeofday(&start, NULL);
    //measure the execution time of the following loop
    for (int i = 1; i <= n-2; ++i) {
        nextTerm = firstTerm + secondTerm;
        cout << nextTerm << " + ";
        firstTerm = secondTerm;
        secondTerm = nextTerm;
    }
    gettimeofday(&end, NULL);
    cout << endl;
    
    cout << "Seconds: ";
    cout << (end.tv_sec - start.tv_sec) << endl;
    
    cout << "Micorseconds: ";
    cout << (end.tv_usec - start.tv_usec) << endl;
    return 0;
}
