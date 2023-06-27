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
	const int n = 10e7;
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
	const int n2 = 2;
	float** Bsgl = new float* [n];
	for (int i = 0; i < n; ++i)
		Bsgl[i] = new float[n2];
	float** Csgl = new float* [10];
	for (int i = 0; i < 10; ++i)
		Csgl[i] = new float[n2];
	double** Bdbl = new double* [n];
	for (int i = 0; i < n; ++i)
		Bdbl[i] = new double[n2];
	double** Cdbl = new double* [10];
	for (int i = 0; i < 10; ++i)
		Cdbl[i] = new double[n2];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n2; ++j)
		{
			Bsgl[i][j] = rand();
			Bdbl[i][j] = rand();
		}
	s1 = 0;
	t1 = clock();
#pragma omp parallel
	{
#pragma omp for reduction(+:s1)
		for (int i = 0; i < n2; ++i) {
			for (int j = 0; j < n; ++j) {
				s1 += Asgl[j] * Bsgl[j][i]; cout << "";
			}
			Csgl[0][i] = s1;
			s1 = 0;
		}
	}
	t2 = clock();
	cout << "Время умножения матриц float: " << t2 - t1 << "\n";
	s2 = 0;
	t3 = clock();
#pragma omp parallel
	{
#pragma omp for reduction(+:s2)
		for (int i = 0; i < n2; ++i) {
			for (int j = 0; j < n; ++j) {
				s2 += Adbl[j] * Bdbl[j][i]; std::cout << "";
			}
			Cdbl[0][i] = s2;
			s2 = 0;
		}
	}
	t4 = clock();
	cout << "Время умножения матриц double: " << t4 - t3 << "\n\n";
}