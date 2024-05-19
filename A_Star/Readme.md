### A-Star Algorithm for Eight Digital Problem
#### - consisting
This solution includes mainly 3 files:
- main.cpp:  
input and output part, easy to read :)
- A_Star.h:
	- AStar_node class
		- using one int to contain the whole map
		```
		_cur = 0;
		int pow = 1;
		for (int i = 0; i < N; i++) {
		if (cur[i] == 0)_zero_pos = i;
		_cur += cur[i] * pow;
		pow *= 10;		
		}
		```
	
		where _cur is hash value.
		- cul_value()
			calculate node's f-value, where g-value is current layer num and h_value is all "off-pos" number's Manhattan distance.
		- move()
			generate new node by current node's moving.
	- AStar_runner class
		- run()
			run the algorithm and output path(if exist).
		- check()
			return if there are ways to transform.
	- time_count class
		- count code's running time.
- A_Star.cpp
	implement A_Star.h