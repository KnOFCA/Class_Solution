#include <iostream>
#include "A_Star.h"

int main()
{
	int p[9]{ 2,1,3,8,0,4,7,6,5 };
	int p2[9]{ 0,1,3,2,6,4,8,7,5 };
	AStar_node a1(p);
	AStar_node a2(p2);
	a1.cul_value(a2,0);
	AStar_runner runner(a1, a2, 1000);
	runner.run();
	std::cout << runner.check();
}
