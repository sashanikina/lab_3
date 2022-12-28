#include <windows.h>
#include <iostream>
#include <bitset>
#include <cmath>

using namespace std;

const int Nst = 308020;
const int N = 100000000;
atomic<int> iter(-1);
atomic<double> c(0);

DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter) {
    bool finish = true;
    int  a, b;
    double x, res = 0;

    while (finish) {
        ++iter;
        a = iter * Nst;
        b = (iter + 1) * Nst;
        if (b > N) {
            b = N;
            finish = false;
        }
        for (int i = a; i < b; i++) {
            x = (i + 0.5) * (1.0 / N);
            res += 4.0 / (1.0 + x * x);
        }
    }
    c = c + res;
    return 0;
}

int main() {
    setlocale(LC_ALL, "RU");
    int *id;
    int numThreads;
    HANDLE *Threads;
    DWORD *lpThreadId;
    DWORD startTime, endTime;

    double Pi;

    printf("Введите количество потоков: ");
    cin >> numThreads;

    id = new int[numThreads];
    Threads = new HANDLE[numThreads];
    lpThreadId = new DWORD[numThreads];

    for (int i = 0; i < numThreads; i++) {
        id[i] = i;
        Threads[i] = CreateThread(nullptr, 0, ThreadProc, &id[i], CREATE_SUSPENDED, &lpThreadId[i]);
    }

    startTime = (DWORD)GetTickCount64();

    for (int i = 0; i < numThreads; i++) {
        ResumeThread(Threads[i]);
    }

    WaitForMultipleObjects(numThreads, Threads, true, INFINITE);

    Pi = c * (1.0 / N);

    endTime = (DWORD)GetTickCount64();

    printf("Найденное число пи: %3.11f\n", Pi);
    printf("Время: %3.3f\n", (float)(endTime - startTime));
    system("pause");
    return 0;
}
