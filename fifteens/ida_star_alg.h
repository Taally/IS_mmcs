#ifndef IDA_STAR_ALG
#define IDA_STAR_ALG
#include "a_star_alg.h"
#include <deque>

bool find_in_path(Node* n, std::deque<Node*> path)
{
	node_ptr_compare cmp;
	for (auto el : path)
		if (cmp.operator()(el, n))
			return true;
	return false;
}

// recursive search
int ida_search(std::deque<Node*> path, int bound, Node** res)	// returns bound
{
	Node* n = path.back();
	int f = n->f();
	if (f > bound) 
		return f;
	if (is_solved(n->field))
	{
		*res = n;
		return -1;
	}
	int min = INT_MAX;

	for (auto new_node : next_nodes(n))
	{
		if (!find_in_path(new_node, path))
		{
			path.push_back(new_node);
			int t = ida_search(path, bound, res);
			if (t == -1)
				return -1;

			if (t < min)
				min = t;
			path.pop_back();

			new_node->parent = nullptr;
			delete new_node;
		}
	}
	return min;
}

void ida_star(const vector<int> & f_start)
{
	if (!solvable(f_start))
		cout << "It is unsolvable.\n";
	else
	{
		std::deque<Node*> path;

		Node * start = new Node(nullptr, f_start);
		path.push_back(start);

		int bound = h(f_start);

		while (true)
		{
			Node* res = nullptr;
			int t = ida_search(path, bound, &res);
			if (t == -1)	// FOUND
			{
				if (res != nullptr)
					print_answer(start, res);
				return;
			}
			if (t == INT_MAX)
			{
				cout << "NOT_FOUND\n";
				return;
			}
			bound = t;
		}
	}
}

#endif // !IDA_STAR_ALG
