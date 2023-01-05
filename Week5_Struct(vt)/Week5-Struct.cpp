#include <iostream>
#define MAX_SIZE 10

struct stVector {
	int size;
	double v[MAX_SIZE];
};

void stVector_Print(stVector vec) {
	printf("[ ");
	for (int i = 0; i < vec.size; i++)
		printf("%7.3f", vec.v[i]);
	printf(" ]\n");
}

int main()
{
	stVector Myvector;
	Myvector.size = 3;
	Myvector.v[0] = 1.0;
	Myvector.v[1] = 2.0;
	Myvector.v[2] = 3.0;

	stVector_Print(Myvector);
}