#include <iostream>
#include <omp.h>
#include <ppl.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	setlocale(LC_ALL, "rus");
	cout << "Количество доступных потоков: " << omp_get_num_procs() << "\n";
	const int n = 10e8;
	float* Asgl = new float[n];
	double* Adbl = new double[n];
	for (int i = 0; i < n; ++i)
	{
		Asgl[i] = rand();
		Adbl[i] = rand();
	}
	float s1 = 0;
	double s2 = 0;
	int threads = 32;
	omp_set_num_threads(threads);
	cout << "Количество потоков: " << threads << "\n";
	unsigned int t1, t2, t3, t4;
	t1 = clock();
#pragma omp parallel
	{
#pragma omp for reduction(+:s1)
		for (int i = 0; i < n; ++i)
			s1 += Asgl[i];
	}
	t2 = clock();
	cout << "Время суммирования массива float: " << t2 - t1 << "\n";
	t3 = clock();
#pragma omp parallel
	{
#pragma omp for reduction(+:s2)
		for (int i = 0; i < n; ++i)
			s2 += Asgl[i];
	}
	t4 = clock();
	cout << "Время суммирования массива double: " << t4 - t3 << "\n";
}