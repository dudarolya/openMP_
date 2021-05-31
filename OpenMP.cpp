#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <list>
#include <exception>

using namespace std;

struct Result
{
	double timestamp, area;
};

double f(const double x);
const Result rectangleMethod(const double, const double, const int, const int);

int main()
{
	const short threads = 12;
	double leftBound = 0.0, rightBound = 1.0; 
	int rectanglesNum, toContinue = 1;

	cout << fixed << setprecision(8) << endl;

	try
	{
		while (toContinue == true)
		{
			cout << "Enter number of rectangles: "; 
			cin >> rectanglesNum;

			list<pair<short, Result>> results;

			int i = 12;
			//for (int i = 1; i < 13;)
			{
				Result result = rectangleMethod(leftBound, rightBound, rectanglesNum, i);

				pair<short, Result> s_result(i, result);
				results.push_back(s_result);
				i += 11;
			}

			cout << endl << "Results:" << endl;

			for (auto& result : results)
			{
				cout << "Number of threads: " << result.first << endl;
				cout << "Time of execution: " << result.second.timestamp << endl;
				cout << "Calculated area: " << result.second.area << endl << endl;
			}
			cout << endl;
			cout << "Enter: \n1 to continue\n0 to exit\n";
			cin >> toContinue;
		}
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	cin.get();
	return 0;
}

const Result rectangleMethod(const double a, const double b, const int rectanglesNum, const int nThreads)
{
	double h = (b - a) / rectanglesNum;
	double startTime = omp_get_wtime();
	double s = 0;

#pragma omp parallel for num_threads(nThreads) reduction(+: s)

	for (int i = 0; i < rectanglesNum; i++) 
		s += f(a + i * h);

	s *= h;

	return { omp_get_wtime() - startTime, s };
}

double f(const double x)
{
	return sin(x + x * x * x);
}