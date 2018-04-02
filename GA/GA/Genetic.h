#ifndef _GENETIC_H_
#define _GENETIC_H_

using namespace std;

#define PI 3.14159265358979323846

#define GROUP_SCALE 50     //��Ⱥ��ģ
#define MAX_GENS    500    //��ֳ����
#define N_VAR       2      //������������
#define P_MATING    0.8    //�������
#define P_MUTATION  0.15   //�������

struct Individual
{
	double Xn[N_VAR];      //��ű���ֵ
	double Fitness;        //��Ӧֵ
	double ReFitness;      //��Ӧֵ�����ܶ�
	double SumFitness;     //�ۼӷֲ���Ϊ����ת
};

struct X_Range
{  
	double Upper;          //�����Ͻ�
	double Lower;		   //�����½�
};

template<typename T> 
T randT(T Lower, T Upper);

void crossover();
void elitist();				//������
void evaluate();

void initGroup();

void selectBest();
void mutate();

void report(int Xnration);
void selector();
void showTime();
void Xover(int one, int two);
#endif //!_GENETIC_H_

