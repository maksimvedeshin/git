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
}