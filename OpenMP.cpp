#include <iostream>
#include <stdio.h>
#include <math.h>
#include <omp.h>
using namespace std;

double Calcs(long long n, double h, int nThreads);
double f(double x);

int main()
{
	long long n = 200000000;
	double h = 1.0 / n, start, res, duration;
	int threadNum = omp_get_max_threads();

	printf("\nLeft rectangles openMP method.\n\nNumber of iterations: %u\n", n);

	start = omp_get_wtime();
	res = Calcs(n, h, threadNum);
	duration = omp_get_wtime() - start;

	printf("\nNumber of threads: %d\n", threadNum);
	printf("\nTime of execution: %f\n\nThe result: %f\n", duration, res);
}

double Calcs(long long n, double h, int nThreads)
{
	double sum = 0.0, xi = 0.0;

#pragma omp parallel for num_threads(nThreads) reduction(+: sum)

	for (int i = 0; i < n; i++)
	{
		sum += f(i * h);
	}
	sum *= h;

	return sum;
}

double f(double x)
{
	return sin(x + x * x * x);
}
