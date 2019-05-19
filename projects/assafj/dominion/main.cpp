#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#include <omp.h>
#define _USE_MATH_DEFINES
#include <cmath> 
float
Ranf(unsigned int *seedp, float low, float high)
{
	float r = (float)rand_r(seedp);              // 0 - RAND_MAX

	//float r = rand();
	return(low + r * (high - low) / (float)RAND_MAX);


}

int
Ranf(unsigned int *seedp, int ilow, int ihigh)
{
	float low = (float)ilow;
	float high = (float)ihigh + 0.9999f;

	return (int)(Ranf(seedp, low, high));
}
float
SQR(float x)
{
	return x * x;
}

omp_lock_t	Lock;
int		NumInThreadTeam;
int		NumAtBarrier;
int		NumGone;

void	InitBarrier(int);
void	WaitBarrier();

// specify how many threads will be in the barrier:
//	(also init's the Lock)

void InitBarrier(int n)
{
	NumInThreadTeam = n;
	NumAtBarrier = 0;
	omp_init_lock(&Lock);
}


// have the calling thread wait here until all the other threads catch up:

void WaitBarrier()
{
	omp_set_lock(&Lock);
	{
		NumAtBarrier++;
		if (NumAtBarrier == NumInThreadTeam)
		{
			NumGone = 0;
			NumAtBarrier = 0;
			// let all other threads get back to what they were doing
			// before this one unlocks, knowing that they might immediately
			// call WaitBarrier( ) again:
			while (NumGone != NumInThreadTeam - 1);
			omp_unset_lock(&Lock);
			return;
		}
	}
	omp_unset_lock(&Lock);

	while (NumAtBarrier != 0);	// this waits for the nth thread to arrive

#pragma omp atomic
	NumGone++;			// this flags how many threads have returned
}

int	NowYear;		// 2019 - 2024
int	NowMonth;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int	NowNumDeer;		// number of deer in the current population
int santaSleighDeer;
unsigned int seed;
const float GRAIN_GROWS_PER_MONTH = 8.0;
const float ONE_DEER_EATS_PER_MONTH = 0.5;

const float AVG_PRECIP_PER_MONTH = 6.0;	// average
const float AMP_PRECIP_PER_MONTH = 6.0;	// plus or minus
const float RANDOM_PRECIP = 2.0;	// plus or minus noise

const float AVG_TEMP = 50.0;	// average
const float AMP_TEMP = 20.0;	// plus or minus
const float RANDOM_TEMP = 10.0;	// plus or minus noise

const float MIDTEMP = 40.0;
const float MIDPRECIP = 10.0;

void currentStatus(unsigned int seed)
{
	float ang = (30.*(float)NowMonth + 15.) * (M_PI / 180.);

	float temp = AVG_TEMP - AMP_TEMP * cos(ang);

	NowTemp = temp + Ranf(&seed, -RANDOM_TEMP, RANDOM_TEMP);



	float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
	NowPrecip = precip + Ranf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP);
	if (NowPrecip < 0.)
		NowPrecip = 0.;

}
void Watcher()
{
	while (NowYear < 2025)
	{
		WaitBarrier();
		WaitBarrier();
		printf("Current Status:\n");
		printf("Month: %d, Year: %d\n", NowMonth, NowYear);
		printf("Temperature: %f, Precipitation: %f\n", NowTemp, NowPrecip);
		printf("Grain Height: %f, Number of Deer: %d\n", NowHeight, NowNumDeer);
		printf("Number of GrainDeer on Santa's Sleigh: %d\n", santaSleighDeer);

		NowMonth++;
		if (NowMonth >= 12)
		{
			NowYear++;
			NowMonth = 0;
		}

		currentStatus(seed);
		WaitBarrier();
	}
}
void Grain()
{

	while (NowYear < 2025)
	{

		float tempFactor = exp(-SQR((NowTemp - MIDTEMP) / 10.));

		float precipFactor = exp(-SQR((NowPrecip - MIDPRECIP) / 10.));

		float temp = (tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH);

		temp -= float(NowNumDeer)*ONE_DEER_EATS_PER_MONTH;

		WaitBarrier();
		NowHeight += temp;
		if (NowHeight < 0)
		{
			NowHeight = 0;
		}
		WaitBarrier();

		WaitBarrier();
	}
}

void GrainDeer()
{
	while (NowYear < 2025)
	{

		int tempDeer = NowNumDeer;
		if (tempDeer > NowHeight)
		{
			tempDeer--;
		}

		else if (tempDeer < NowHeight)
		{

			tempDeer++;
		}
		if (tempDeer >= 5)
		{

			if (NowMonth < 12 && NowMonth > 8)
			{
				tempDeer--;
			}


		}
		if (santaSleighDeer > 9)
		{
			tempDeer++;
		}
		if (NowMonth >= 0 && NowMonth <= 8)
		{
			if (santaSleighDeer > 0)
			{
				tempDeer++;
			}
		}
		WaitBarrier();

		if (tempDeer < 0)
		{
			tempDeer = 0;
		}

		NowNumDeer = tempDeer;
		WaitBarrier();
		WaitBarrier();
	}

}
void santaSleigh()
{
	while (NowYear < 2025)
	{
		int temp = santaSleighDeer;
		if (NowMonth < 12 && NowMonth > 8)
		{
			if (NowNumDeer >= 5)
			{
				temp++;
			}
			if (temp > 9)
			{
				temp--;
			}

		}
		else
		{
			if (santaSleighDeer > 0)
			{
				temp--;
			}
		}
		WaitBarrier();

		santaSleighDeer = temp;

		WaitBarrier();
		WaitBarrier();
	}

}
int main(int argc, char *argv[])
{
	unsigned int seed = time(0);

#ifndef _OPENMP

	fprintf(stderr, "No OpenMP support!\n");
	return 1;
#endif


	// starting date and time:
	NowMonth = 0;
	NowYear = 2019;

	// starting state (feel free to change this if you want):
	NowNumDeer = 1;
	NowHeight = 1.;
	santaSleighDeer = 0;

	InitBarrier(4);
	currentStatus(seed);
	omp_set_num_threads(4);



#pragma omp parallel sections
	{
#pragma omp section
		{
			GrainDeer();
		}

#pragma omp section	
		{

			Grain();

		}

#pragma omp section
		{
			Watcher();
		}

#pragma omp section
		{
			santaSleigh();
		}
	}

	return 0;
}