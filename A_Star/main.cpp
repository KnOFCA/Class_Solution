#include <iostream>
#include "A_Star.h"

int main()
{
	int p[9];
	std::cout << "input init_state:" << std::endl;
	for (int i = 0; i < MAX_MAP_SIZE; i++)
		std::cin >> p[i];
	int p2[9];
	std::cout << "input dst_state:" << std::endl;
	for (int i = 0; i < MAX_MAP_SIZE; i++)
		std::cin >> p2[i];
	AStar_node a1(p);
	AStar_node a2(p2);
	a1.cul_value(a2,0);
	AStar_runner runner(a1, a2, 1000);
	runner.run();
	std::cout << runner.check();
}
