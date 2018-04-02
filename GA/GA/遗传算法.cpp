#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstring>
#include "Genetic.h"

struct Individual Population[GROUP_SCALE + 1];

X_Range XnRange[N_VAR] = { { -3.0, 12.1 }, { 4.1, 5.8 } };

void crossover()
{
	const double a = 0.0;
	const double b = 1.0;
	int one;
	int first = 0;
	double x;

	for (int mem = 0; mem < GROUP_SCALE; ++mem)
	{
		x = randT(0.0,1.0);

		if (x < P_MATING)
		{
			++first;

			if (first % 2 == 0) //交配
			{
				Xover(one, mem);
			}
			else
			{
				one = mem;
			}
		}
	}
	return;
}

void Xover(int one, int two)
{
	int point;
	point = randT<int>(0, N_VAR - 1);

	for (int i = 0; i < point; i++)
	{
		double t;
		t = Population[one].Xn[i];
		Population[one].Xn[i] = Population[two].Xn[i];
		Population[two].Xn[i] = t;
	}
	return;
}

void evaluate()
{
	
	for (int mem = 0; mem < GROUP_SCALE; mem++)
	{
		Population[mem].Fitness = 21.5 + Population[mem].Xn[0] * sin(4 * PI * Population[mem].Xn[0]) + Population[mem].Xn[1] * sin(20 * PI * Population[mem].Xn[1]);

	}
	return;
}

void initGroup()
{
	
	for (int i = 0; i < N_VAR; i++)
	{
		for (int j = 0; j < GROUP_SCALE; j++)
		{
			Population[j].Fitness = 0;
			Population[j].ReFitness = 0;
			Population[j].SumFitness = 0;
			Population[j].Xn[i] = randT(XnRange[i].Lower, XnRange[i].Upper);
		}
	}
	return;
}

void selectBest()
{
	int cur_best = 0;

	for (int mem = 0; mem < GROUP_SCALE; mem++)
	{
		if (Population[GROUP_SCALE].Fitness < Population[mem].Fitness)
		{
			cur_best = mem;
			Population[GROUP_SCALE].Fitness = Population[mem].Fitness;
		}
	}

	for (int i = 0; i < N_VAR; i++)
	{
		Population[GROUP_SCALE].Xn[i] = Population[cur_best].Xn[i];
	}

	return;
}

void mutate() //变异
{
	const double a = 0.0;
	const double b = 1.0;

	double x;

	for (int i = 0; i < GROUP_SCALE; i++)
	{
		for (int j = 0; j < N_VAR; j++)
		{
			x = randT(a, b);
			if (x < P_MUTATION)
			{
				Population[i].Xn[j] = randT(XnRange[j].Lower, XnRange[j].Upper);
			}
		}
	}
	return;
}

template<typename T>
T randT(T Lower, T Upper)
{
	return rand() / (double)RAND_MAX * (Upper - Lower) + Lower;
}

void selector()
{
	struct Individual NewPoplulation[GROUP_SCALE + 1]; //临时存放挑选的后代个体

	const double a = 0;
	const double b = 1;
	double p;
	double sum = 0;
	for (int mem = 0; mem < GROUP_SCALE; mem++)
	{
		sum = sum + Population[mem].Fitness;
	}

	for (int mem = 0; mem < GROUP_SCALE; mem++)
	{
		Population[mem].ReFitness = Population[mem].Fitness / sum;
	}

	//计算累加分布，思想是轮盘法
	Population[0].SumFitness = Population[0].ReFitness;

	for (int mem = 1; mem < GROUP_SCALE; mem++)
	{
		Population[mem].SumFitness = Population[mem - 1].SumFitness + Population[mem].ReFitness;
	}

	for (int i = 0; i < GROUP_SCALE; i++)
	{
		p = randT(a, b);
		if (p < Population[0].SumFitness)
		{
			NewPoplulation[i] = Population[0];
		}
		else
		{
			for (int j = 0; j < GROUP_SCALE; j++)
			{
				if (Population[j].SumFitness <= p && p < Population[j + 1].SumFitness)
				{
					NewPoplulation[i] = Population[j + 1];
					break;
				}
			}
		}
	}

	for (int i = 0; i < GROUP_SCALE; i++)
	{
		Population[i] = NewPoplulation[i];
	}
	return;
}

void elitist()
{
	double best;
	int best_mem;
	double worst;
	int worst_mem;

	best = Population[0].Fitness, best_mem = 0;
	worst = Population[0].Fitness, worst_mem = 0;

	for (int i = 1; i < GROUP_SCALE; i++)
	{
		if (Population[i].Fitness > best)
			best = Population[i].Fitness, best_mem = i;
		if (Population[i].Fitness < worst)
			worst = Population[i].Fitness, worst_mem = i;
	}

	if (Population[GROUP_SCALE].Fitness < best)
	{
		for (int i = 0; i < N_VAR; i++)
			Population[GROUP_SCALE].Xn[i] = Population[best_mem].Xn[i];
		Population[GROUP_SCALE].Fitness = best;
	}
	else 
	{
		for (int i = 0; i < N_VAR; i++)
			Population[worst_mem].Xn[i] = Population[GROUP_SCALE].Xn[i];
		Population[worst_mem].Fitness = Population[GROUP_SCALE].Fitness;
	}

	return;

}

void report(int Xnration)
{
	double avg;
	double best_val;
	double square_sum;
	double stddev;
	double sum;
	double sum_square;

	if (Xnration == 0)
	{
		cout << "\n";
		cout << "Xnration Best Average Standard \n";
		cout << "number value fitness deviation\n";
		cout << "\n";
	}
	sum = 0;
	sum_square = 0;

	for (int i = 0; i < GROUP_SCALE; i++)
	{
		sum = sum + Population[i].Fitness;
		sum_square = sum_square + Population[i].Fitness * Population[i].Fitness;
	}

	avg = sum / (double)GROUP_SCALE;
	square_sum = avg * avg * GROUP_SCALE;
	stddev = sqrt((sum_square - square_sum) / (GROUP_SCALE - 1));
	best_val = Population[GROUP_SCALE].Fitness;

	cout << " " << setw(8) << Xnration
		<< " " << setw(14) << best_val
		<< " " << setw(14) << avg
		<< " " << setw(14) << stddev << "\n";

	return;
}

void showTime()
{
#define TIME_SIZE 40
	static char time_buffer[TIME_SIZE];
	struct tm tm;
	size_t len;
	time_t now;

	now = time(NULL);
	localtime_s(&tm, &now);

	len = strftime(time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", &tm);

	cout << time_buffer << "\n";
	return;
#undef TIME_SIZE
}