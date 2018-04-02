#include <iostream>
#include <ctime>
#include "Genetic.h"

extern Individual Population[GROUP_SCALE + 1];

int main()
{
	srand((unsigned)time(NULL));

	showTime();
	initGroup();
	evaluate();
	selectBest();

	for (int i = 0; i < MAX_GENS; i++)
	{
		selector();
		crossover();
		mutate();
		report(i);
		evaluate();
		elitist();
	}
	cout << "\n";
	cout << "Best member after" << MAX_GENS << "Xnrations:\n";
	
	for (int i = 0; i < N_VAR; i++)
	{
		cout << " X(" << i + 1 << ")=" << Population[GROUP_SCALE].Xn[i] << "\n";
	}
	
	cout << "\n";
	cout << "  Best Fitness = " << Population[GROUP_SCALE].Fitness << "\n";

	showTime();
	int a;
	cin >> a;
	return 0;
}