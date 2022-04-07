#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
void printHistogram(int *hist);

int main(int argc, char const *argv[])
{
	int samples[4] = {5000, 50000, 100000, 10000000};
    for (int k = 0; k < sizeof(samples)/sizeof(int); k++)
	{
		int sample = samples[k];

		printf("sample is %d\n", sample);

		srand(time(NULL));

		int hist[25] = {0};
		clock_t begin = clock();

		for (int i = 0; i < sample; i++)
		{
			int counter = 0;
			for (int j = 0; j < 12; j++)
			{
				int random = rand() % 101;
				if (random >= 49)
				{
					counter++;
				}
				else
				{
					counter--;
				}
			}
			hist[counter + 12]++;
		}

		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("execution time of %d sample: %f\n", sample, time_spent);

		// printHistogram(hist);
	}

	return 0;
}

void printHistogram(int *hist)
{
	int i, j;
	for (i = 0; i < 25; i++)
	{
		for (j = 0; j < hist[i]; j++)
		{
			printf("*");
		}
		printf("\n");
	}
}
