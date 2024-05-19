#pragma once
#include <iostream>
#include <queue>
#include <unordered_map>
#include <format>
#include <chrono>

#define MAX_MAP_SIZE 9
#define UP -3
#define DOWN 3
#define LEFT -1
#define RIGHT 1
class AStar_node
{
	int _cur, _value, _zero_pos, _h_value;

public:
	template<std::size_t N>
		requires (N == MAX_MAP_SIZE)
	AStar_node(int(&cur)[N]):_value(int()), _h_value(int())
	{
		_cur = 0;
		int pow = 1;
		for (int i = 0; i < N; i++) {
			if (cur[i] == 0)_zero_pos = i;
			_cur += cur[i] * pow;
			pow *= 10;
		}
	}

	AStar_node()
	{
		_cur = 0;
		_value = 0;
		_zero_pos = 0;
		_h_value = 0;
	}

	AStar_node(const AStar_node& other)
	{
		_cur = other._cur;
		_value = other._value;
		_zero_pos = other._zero_pos;
		_h_value = other._h_value;
	}

	template<std::size_t N>
		requires (N == MAX_MAP_SIZE)
	void load(int(&cur)[N])
	{
		_cur = 0;
		int pow = 1;
		for (int i = 0; i < N; i++) {
			if (cur[i] == 0)_zero_pos = i;
			_cur += cur[i] * pow;
			pow *= 10;
		}
	}

	int operator[](int pos) const
	{
		return (int)(_cur / std::pow(10, pos)) % 10;
	}

	bool operator==(const AStar_node& dst) const
	{
		return _cur == dst._cur;
	}

	bool operator>(const AStar_node& other) const
	{
		return _value > other._value;
	}

	int get_hash() const
	{
		return _cur;
	}

	int get_value() const
	{
		return _value;
	}

	friend std::ostream& operator<<(std::ostream& os, AStar_node t);

	void cul_value(const AStar_node& dst);
	AStar_node move(int mov);
};

class AStar_runner
{
	std::priority_queue<AStar_node,std::vector<AStar_node>,std::greater<AStar_node>> _open_set;
	std::unordered_map<int,int> _close_set,_trace_map;
	AStar_node _dst;
	int _max_step;
	bool _is_found;

	std::vector<int> trace(int hash);

public:
	AStar_runner(const AStar_node& init_state, const AStar_node& dst_state, int max_step):_max_step(max_step)
	{
		if (init_state == dst_state) _is_found = true;
		else _is_found = false;
		_open_set.push(init_state);
		_dst = dst_state;
		_trace_map.insert({ init_state.get_hash(),0 });
	}

	AStar_runner() = delete;
	AStar_runner(const AStar_runner&) = delete;
	~AStar_runner() = default;

	void run();


	bool check() const
	{
		return _is_found;
	}
};

struct time_count
{
	std::chrono::steady_clock::time_point start, end;
	std::chrono::duration<float> period;
	time_count()
	{
		start = std::chrono::high_resolution_clock::now();
		period = std::chrono::duration<float>();
	}
	~time_count()
	{
		end = std::chrono::high_resolution_clock::now();
		period = end - start;
		std::cout << period.count() << "s\n";
	}
};
