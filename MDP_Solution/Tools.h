#pragma once
#include <iostream>
class MDP_map
{
	float* _fp;
	std::size_t _sz,_row;
	bool _usable;


public:
	MDP_map() :_fp(nullptr),_sz(),_row(),_usable(false) {};
	
	template<std::size_t N>
	constexpr MDP_map(float(&p)[N]):_sz(N),_row(),_usable(false)
	{
		_fp = new float[N];
		std::memcpy(_fp, p, sizeof(float) * N);
	}

	template<std::size_t N>
	MDP_map(float(&p)[N],int row) :_sz(N), _row(row), _usable(true)
	{
		_fp = new float[N];
		std::memcpy(_fp, p, sizeof(float) * N);
		shape(row);
	}

	template<std::size_t N>
	void reload(float(&p)[N])
	{
		_sz = N;
		delete[]_fp;
		_fp = new float[N];
		std::memcpy(_fp, p, sizeof(float) * N);
	}

	void reshape(int row)
	{
		_row = row;
	}
};

class MDP_runner
{

};
