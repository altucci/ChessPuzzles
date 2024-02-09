#include <cstdlib>
#include "ccc_time.cpp"

void randseed()
{
	Time now;
	int seed = now.seconds_from(Time(0,0,0));
	srand(seed);
}

void randseed(int a)
{
	srand(a);
}

int rand_int(int a, int b)
{
	return a + rand() % (b - a + 1);
}
