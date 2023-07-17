// Задание 2
// Параллельные вычисления

// Распараллелить данную программу на 2, 4, 8 и 16 потоков.

// Сравнить результаты выполнения для массивов из 1000, 10 000, 100 000 и 1 000 000 элементов.

#include <iostream>
#include <thread>
#include <chrono>
#include <execution>
#include <algorithm>
#include <vector>
#include <random>
#include <iomanip>

using namespace std::chrono_literals;

double calculate(const std::vector<int>& vec1, const std::vector<int>& vec2, int threads, int size);

void sum_vectors(const std::vector<int>& vec1, const std::vector<int>& vec2, int start, int end);

void run_calcs(const std::vector<int>& vec1, const std::vector<int>& vec2, int size);


int main(int argc, char** argv)
{
	// VARS

	std::vector<int> vector1;
	std::vector<int> vector2;
	int current_size = 0;

	// BODY

	std::mt19937 generator;
	std::uniform_int_distribution<int> dist(1, 100);	

	std::cout << "CORES AVAILABLE IN SYSTEM: " << std::thread::hardware_concurrency() << "\n\n";

	std::cout << "  THREADS USED |\t01 thread\t02 threads\t04 threads\t08 threads\t16 threads\n";
	std::cout << "  VECTOR SIZE  |\n";	
	
	// fill the vectors with 1 000 elements

	for (; current_size < 1000;)
	{
		++current_size;
		vector1.push_back(dist(generator));
		vector2.push_back(dist(generator));
	}

	std::cout << "  1'000        |";

	run_calcs(vector1, vector2, current_size);

	std::cout << '\n';

	// fill the vectors with 10 000 elements

	for (; current_size < 10000;)
	{
		++current_size;
		vector1.push_back(dist(generator));
		vector2.push_back(dist(generator));
	}

	std::cout << "  10'000       |";

	run_calcs(vector1, vector2, current_size);

	std::cout << '\n';

	// fill the vectors with 100 000 elements

	for (; current_size < 100000;)
	{
		++current_size;
		vector1.push_back(dist(generator));
		vector2.push_back(dist(generator));
	}

	std::cout << "  100'000      |";

	run_calcs(vector1, vector2, current_size);

	std::cout << '\n';

	// fill the vectors with 1 000 000 elements

	for (; current_size < 1000000;)
	{
		++current_size;
		vector1.push_back(dist(generator));
		vector2.push_back(dist(generator));
	}

	std::cout << "  1'000'000    |";

	run_calcs(vector1, vector2, current_size);

	std::cout << '\n';

	// EXIT
	std::cout << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}

double calculate(const std::vector<int>& vec1, const std::vector<int>& vec2, int threads, int size)
{
	typedef std::chrono::duration<double, std::milli> duration;

	auto start = std::chrono::steady_clock::now();

	int elem_start = 0;
	int elem_end = size;
	int elem_tmp = 0;
	int elem_pack = size / threads;

	std::vector<std::thread> runner;

	for (int i = 0; i < threads; ++i)
	{
		elem_start = elem_tmp;
		elem_tmp = elem_end + 1;
		elem_end = elem_start + elem_pack;

		if (elem_end > size)
		{
			elem_end = size;
		}

		runner.push_back(std::thread(sum_vectors, std::ref(vec1), std::ref(vec2), elem_start, elem_end));
	}

	for (auto & thr : runner)
	{
		if (thr.joinable())
			thr.join();
	}

	auto end = std::chrono::steady_clock::now();
	duration delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	return delta.count();
}

void sum_vectors(const std::vector<int>& vec1, const std::vector<int>& vec2, int start, int end)
{
	// just for results, not returning
	std::vector<int> result;

	// Vectors summing here

	for (int i = start; i < end; ++i)
	{
		result.push_back(vec1[i] + vec2[i]);
	}
}

void run_calcs(const std::vector<int>& vec1, const std::vector<int>& vec2, int size)
{
	double t = 0;
	std::cout << std::setprecision(8);
	std::cout << "\t";

	std::cout << (t + (calculate(vec1, vec2, 1, size) / 1000)) << "sec"; t = 0;
	
	std::cout << "\t";

	std::cout << (t + (calculate(vec1, vec2, 2, size) / 1000)) << "sec"; t = 0;

	std::cout << "\t";

	std::cout << (t + (calculate(vec1, vec2, 4, size) / 1000)) << "sec"; t = 0;

	std::cout << "\t";

	std::cout << (t + (calculate(vec1, vec2, 8, size) / 1000)) << "sec"; t = 0;

	std::cout << "\t";

	std::cout << (t + (calculate(vec1, vec2, 16, size) / 1000)) << "sec"; t = 0;
}