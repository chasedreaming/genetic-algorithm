#ifndef _GENETIC_H_
#define _GENETIC_H_

using namespace std;

#define PI 3.14159265358979323846

#define GROUP_SCALE 50     //种群规模
#define MAX_GENS    500    //繁殖代数
#define N_VAR       2      //函数变量个数
#define P_MATING    0.8    //交叉概率
#define P_MUTATION  0.15   //变异概率

struct Individual
{
	double Xn[N_VAR];      //存放变量值
	double Fitness;        //适应值
	double ReFitness;      //适应值概率密度
	double SumFitness;     //累加分布，为轮盘转
};

struct X_Range
{  
	double Upper;          //变量上届
	double Lower;		   //变量下届
};

template<typename T> 
T randT(T Lower, T Upper);

void crossover();
void elitist();				//基因保留
void evaluate();

void initGroup();

void selectBest();
void mutate();

void report(int Xnration);
void selector();
void showTime();
void Xover(int one, int two);
#endif //!_GENETIC_H_

