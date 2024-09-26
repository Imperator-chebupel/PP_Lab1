#include <iostream>
#include "pthread.h"
#include "Math.h"
#include "Stdio.h"
#pragma comment(lib,"pthreadVCE2.lib")
#include <chrono>
#include <iomanip>
#include <vector>
using namespace std;

class paramets
{
public:
    float X1, X2;
public:
    int N;
};

float Return_Func(float X);
void* Integrate(void* P1);
int pthread_create(pthread_t thread, pthread_attr_t* attr, void* (*start_routine)(void*), void* arg);

int count;
//int atoi(const char* nptr);
float summ = 0.0;


int main(int argc, char* argv[])
{


    int Count_of_threads;
    std::cin >> Count_of_threads;
    std::vector<pthread_t> threads(Count_of_threads);

    int Number_of_steps;
    std::cin >> Number_of_steps;
    float Border1, Border2;
    std::cin >> Border1;
    std::cin >> Border2;

    std::vector <paramets> ParametsOfParts(Count_of_threads);

    for (int i = 0; i < Count_of_threads; i++)
    {
        ParametsOfParts[i].N = Number_of_steps/Count_of_threads;
        ParametsOfParts[i].X1 = Border1 + (( Border2 - Border1) / Count_of_threads) * i;
        ParametsOfParts[i].X2 = Border1 + ((Border2 - Border1) / Count_of_threads) * (i+1);
    }

    for (int i = 0; i < Count_of_threads; i++)
    {
        pthread_create(&threads[i], NULL, Integrate, &ParametsOfParts[i]);
    }

    for (int i = 0; i < Count_of_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    cout << summ;
    exit(EXIT_SUCCESS);
    return 0;
}

void* Integrate(void* P)
{
    paramets* P1 = (paramets*)P;
    float sum = 0.0f;
    /*float X1 = 3.0f, X2 = 7.0f;
    int N = 1024; */
    float H = (P1->X2 - P1->X1) / P1->N;
    for (int i = 1; i <= P1->N; i++)
    {
        float x = (P1->X1) + i * H;
        sum += H * Return_Func((x + x + H) / 2.0);
    }
    summ += sum;
    return 0;
    pthread_exit(0);
}

float Return_Func(float X)
{
    return (float)(pow(X + 1, 2)) / (sqrt(log(X)));
}