#include <iostream>
#include "A_Star.h"

int main()
{
	time_count tc;
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int p[9] = { 2,8,3,1,6,4,7,0,5 };
	//std::cout << "input init_state:" << std::endl;
	//for (int i = 0; i < MAX_MAP_SIZE; i++)
	//	std::cin >> p[i];
	int p2[9] = { 2,8,3,1,6,4,7,0,5 };
	//std::cout << "input dst_state:" << std::endl;
	//for (int i = 0; i < MAX_MAP_SIZE; i++)
	//	std::cin >> p2[i];
	AStar_node a1(p);
	AStar_node a2(p2);
	a1.cul_value(a2);
	AStar_runner runner(a1, a2, 10000000);
	runner.run();
	if(runner.check())
		std::cout << "Solution Found!" << std::endl;
}
