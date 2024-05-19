#include "A_Star.h"
void AStar_node::cul_value(const AStar_node& dst)
{
	_value = _h_value;
	for (int i = 0; i < MAX_MAP_SIZE; i++)
	{
		int cnt = 0;
		for (int j = 0; j < MAX_MAP_SIZE&&!cnt; j++) {
			int dst_cur = dst[j];
			if (this->operator[](i) == dst_cur) _UNLIKELY {
				this->_value += (std::abs(i % 3 - j % 3)) + (std::abs(i / 3 - j / 3));
				cnt++;
			}
		}
	}
}

AStar_node AStar_node::move(int mov)
{
	AStar_node cpy(*this);
	int zero_pos = cpy._zero_pos;
	int mov_pos = zero_pos + mov;
	if (mov_pos < 0 || mov_pos > 8 ||
		((mov == LEFT) ? ((int)mov_pos / 3 + 1 == (int)zero_pos / 3) : 0) ||
		((mov == RIGHT) ? ((int)mov_pos / 3 - 1 == (int)zero_pos / 3) : 0)
		) {
		cpy._cur = 0;
		return cpy;
	}
	cpy._cur = cpy._cur + cpy[mov_pos] * std::pow(10, zero_pos) - cpy[mov_pos] * std::pow(10, mov_pos);
	cpy._zero_pos = mov_pos;
	cpy._h_value = this->_h_value + 1;
	return cpy;
}

//TODO:find a way to trace back node
std::vector<int> AStar_runner::trace(int hash)
{
	std::vector<int> ret;
	int num = hash;
	do
	{
		ret.push_back(num);
		num = _trace_map[num];
	} while (num);
	return ret;
}

std::ostream& operator<<(std::ostream& os, AStar_node t)
{
	return os << t._cur;
}

void AStar_runner::run()
{
	for (int i = 0; i < _max_step && !_is_found && !_open_set.empty(); i++) {
		AStar_node min_node(_open_set.top());
		_open_set.pop();
		_close_set.insert({ min_node.get_hash(),1 });
		std::vector<AStar_node> mov_array{ 
			min_node.move(UP) ,
			min_node.move(DOWN) ,
			min_node.move(LEFT) ,
			min_node.move(RIGHT) };
		for (auto& node : mov_array) {
			if (node.get_hash() != 0)
			{
				if (!_close_set[node.get_hash()]) {
					//TODO:some
					if(!_trace_map[node.get_hash()])
					_trace_map[node.get_hash()] = min_node.get_hash();
					node.cul_value(_dst);
					_open_set.push(node);
				}
			}
		}
		if (min_node == _dst) {
			_is_found = true;
			std::vector<int> res = trace(min_node.get_hash());
			int round = 0;
			for (auto p = res.rbegin(); p != res.rend(); p++) {
				int num = *p;
				int cnt = 1, dgt_num = 9;
				std::cout << std::format("round {}: \n", round);
				while (dgt_num) {
					std::cout << (num % 10) << " ";
					num /= 10;
					cnt++;
					if (cnt == 4) {
						std::cout << std::endl;
						cnt = 1;
					}
					dgt_num--;
				}
				round++;
			}
		}
	}
	if (_open_set.empty())std::cout << "no solution";
}

