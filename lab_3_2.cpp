#include <iostream>
#include <bitset>
#include <omp.h>
#include <windows.h>

using namespace std;

const int Nst = 308020;
const int N = 100000000;


int main() {
    setlocale(LC_ALL, "RU");
    int numThreads;
    double x, sum=0;
    DWORD startTime, endTime;

    printf("Введите количество потоков: ");
    cin >> numThreads;
    startTime = (DWORD)GetTickCount64();
    #pragma omp parallel for schedule(dynamic, Nst) private(x) num_threads(numThreads) reduction(+:sum)
    for(int i=0; i<N; i++){
        x=(i+0.5)*(1.0/N);
        sum=sum+4.0/(1.0+x*x);
    }

    sum =sum*(1.0/N);
    endTime = (DWORD)GetTickCount64();

    printf("Найденное число пи: %3.11f\n", sum);
    printf("Время: %3.3f\n", (float)(endTime - startTime));
system("pause");
    return 0;
}
