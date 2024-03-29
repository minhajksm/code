#include	"includes.h"


typedef struct	_tBest
{
	int		ID;
	double	Health;
	double	Gene[NUM];
}tBest;


tBest	Best = {0,0,0,0,0,0};						//最优染色体编号,适应值及其基因
double	Species[N][NUM];							//N个染色体,每个染色体NUM个基因
double	GenSpecies[N][NUM];							//保存进化后的种群
double	Health[N];									//N个染色体的适应值, 之后保存每个染色体的适应值比例
int		Selection[N];								//保存选择出来的染色体ID,需要交配的染色体ID以及需要变异的染色体ID


//============================================================================//
//==							初始化种群		    						==//
//============================================================================//
//==入口参数: Spec[][NUM]		种群数组		                            ==//
//==出口参数: Spec[][NUM]		种群数组		                            ==//
//==返回值:	  无							                                ==//
//============================================================================//
void SpeciesInit(double	Spec[][NUM])				//二维数组的传递: 形参给出第二维的长度
{
	int	 i,j;

	for (i=0; i<N; i++)
	{
		for (j=0; j<NUM; j++)
		{
			Spec[i][j] = rand()/3276.7 - 5.0;		//rand()函数返回的最大随机数是0x7fff,产生(-5,5)的随机数(解空间)
		}
	}
}





//============================================================================//
//==						评估一个染色体的适应值		   					==//
//============================================================================//
//==入口参数: *Chro				染色体指针		                            ==//
//==出口参数: 无							                                ==//
//==返回值:	  Value				染色体的适应值								==//
//============================================================================//
double AdaptiveValue(double *Chro)
{
	double	Value;

	Value = 1/(1+Chro[0]*Chro[0]+Chro[1]*Chro[1]+Chro[2]*Chro[2]+Chro[3]*Chro[3]);		//不要直接return该值

	return	Value;
}





//============================================================================//
//==				计算每个染色体适应值占总体适应值的比例   				==//
//============================================================================//
//==入口参数: *Heal				适应值数组		                            ==//
//==出口参数: *Heal				适应值数组		                            ==//
//==返回值:	  无															==//
//============================================================================//
void Portion(double	*Heal)
{
	int		i;
	double	Sum = 0;

	for (i=0; i<N; i++)
	{
		Sum += Heal[i];
	}

	for (i=0; i<N; i++)
	{
		Heal[i] = Heal[i]/Sum;
	}
}





//============================================================================//
//==							轮盘赌转	        						==//
//============================================================================//
//==入口参数: *Portion			适应值比例数组								==//
//==出口参数: 无															==//
//==返回值:	  ID				选中的染色体								==//
//============================================================================//
int Roulette(double *Portion)
{
	int		i;
	double  r = 0;
	double	m = 0;

	r = rand()/32767.0;			//产生[0,1]随机数
	for (i=0; i<N; i++)
	{
		m += Portion[i];
		if (m>r)
		{
			return	i;
		}
	}
	return	i;					//避免警告, 不会出现该情况
}





//============================================================================//
//==							  交配算子  	    						==//
//============================================================================//
//==入口参数: Chro1		        父本染色体			                        ==//
//==		  Chro2				母本染色体				                    ==//
//==出口参数: 无							                                ==//
//==返回值:	  无															==//
//============================================================================//
void CrossOver(double *Chro1, double *Chro2)
{
	int		r;
	double	Temp;

	r = rand()%NUM;								//在NUM各基因中任选一个基因交配
	Temp = *(Chro1+r);
	*(Chro1+r) = *(Chro2+r);
	*(Chro2+r) = Temp;
}





//============================================================================//
//==							对基因进行变异	    						==//
//============================================================================//
//==入口参数: Chromosome        需要变异的染色体                            ==//
//==出口参数: 无							                                ==//
//==返回值:	  Ret				变异后的染色体								==//
//============================================================================//
void Mutation(double *Chro)
{
	int	 r;

	r = rand()%NUM;								//在NUM各基因中任选一个基因变异
	*(Chro+r) = rand()/3276.7 - 5.0;			//变异
}





//============================================================================//
//==							  遗传算法	        						==//
//============================================================================//
//==入口参数: 无								                            ==//
//==出口参数: 无							                                ==//
//==返回值:	  无															==//
//============================================================================//
double GA(void)
{
	int		i;
	int		j;
	int		k;
	double  r;
	double	sum=0;


	SpeciesInit(Species);							//初始化群体

 for(k=0; k<GEN; k++)
 {
	for (i=0; i<N; i++)								//计算群体的适应值,并保存最优染色体
	{
		Health[i] = AdaptiveValue(Species[i]);		//Species[i]表示i行0列元素的地址
		if (Health[i] > Best.Health)
		{
			Best.ID = i;
			Best.Health = Health[i];
			for (j=0; j<NUM; j++)
			{
				Best.Gene[j] = Species[i][j];
			}
		}
	}


	Portion(Health);								//计算每个染色体适应值的比例

	for (i=0; i<N; i++)
		sum += Health[i];

	for (i=0; i<N; i++)								//得到优胜劣汰后的染色体ID,更新种群
	{
		Selection[i] = Roulette(Health);			//此时Health表示适应值比例
		for (j=0; j<NUM; j++)
		{
			GenSpecies[i][j] = Species[Selection[i]][j];
		}
	}


	for (i=0,j=0; i<N; i++)
	{
		r = rand()/32767.0;
		if (r<PC)									//需要参与交配
		{
			Selection[j++] = i;						//记录需要交配的染色体ID
		}
	}
	for (i=0; i<j; i+=2)							//传递两个染色体ID进行交配,奇数个染色体舍弃最后一个
	{
		CrossOver(GenSpecies[Selection[i]],GenSpecies[Selection[i+1]]);
	}


	for (i=0; i<N; i++)
	{
		r = rand()/32767.0;
		if (r<PM)									//需要变异
		{
			Mutation(GenSpecies[i]);				//变异染色体
		}
	}

	for (i=0; i<N; i++)
		for(j=0; j<NUM; j++)
			Species[i][j] = GenSpecies[i][j];		//更新种群
 }

 return Best.Health;
}
