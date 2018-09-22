#ifndef A_STAR_ALG
#define A_STAR_ALG

#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <ctime>
#include <fstream>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

std::ofstream fout("output.txt");

int h(const vector<int> & f) // манхэттенское расстояние с линейным конфликтом
{
	int res = 0;
	for (int i = 0; i < f.size(); ++i)
	{
		// Manhattan distance
		if (f[i] && f[i] != i + 1)
		{
			// where it should be
			int fx = (f[i] - 1) % 4;
			int fy = (f[i] - 1) / 4;

			// where it is now
			int ix = i % 4;
			int iy = i / 4;
			res += std::abs(ix - fx) + std::abs(iy - fy);
		}

		int l_conflicts = 0;

		// Linear conflict
		if (f[i])
		{
			for (int j = i + 1; j % 4 > i % 4; ++j)
				if (f[j] && f[i] > f[j] && (f[i] - 1) / 4 == (f[j] - 1) / 4)
					++l_conflicts;
		}
		res += l_conflicts * 2;
	}
	return res;
}

struct Node
{
	Node* parent;
	int step;
	vector<int> field;

	int f()
	{
		return step + h(field);
	}

	Node(Node* p, const vector<int> & field) : parent(p), field(field) 
	{
		if (p == nullptr)
			step = 0;
		else step = p->step + 1;
	}
};

vector<int> read_field()
{
	std::string s;
	cout << "Enter fifteen's field\n";
	cin >> s;
	while (s.size() != 16)
	{
		cout << "Try again\n";
		cin >> s;
	}
	vector<int> res(16);

	for (int i = 0; i < res.size(); ++i) 
	{
		if (s[i] == 'A')
			res[i] = 10;
		else if (s[i] == 'B')
			res[i] = 11;
		else if (s[i] == 'C')
			res[i] = 12;
		else if (s[i] == 'D')
			res[i] = 13;
		else if (s[i] == 'E')
			res[i] = 14;
		else if (s[i] == 'F')
			res[i] = 15;
		else
			res[i] = s[i] - '0';
	}
	return res;
}

// cmp eq
struct node_ptr_compare {
	bool operator() (const Node * n1, const Node * n2) const
	{
		for (int i = 0; i < n1->field.size(); ++i)
			if (n1->field[i] != n2->field[i])
				return false;
		return true;
	}
};

// cmp greater - for priority queue
struct cmp_with_heuristic
{
	bool operator() (const Node * n1, const Node* n2) const
	{
		return (h(n1->field) + n1->step > h(n2->field) + n2->step);
	}
};

// for unordered set
auto nodeHash = [](Node *n)
{
	std::size_t seed = n->field.size();
	for (auto& i : n->field) {
		seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
};

// for unordered set
auto node_ptr_eq = [](Node* n1, Node* n2)
{
	for (int i = 0; i < 16; ++i)
		if (n1->field[i] != n2->field[i])
			return false;
	return true;
	//		return (std::equal(n1->field.begin(), n1->field.end(), n2->field.begin()));
};

// print to file
void print_field(const vector<int> & f)
{
	for (int i = 0; i < f.size(); ++i)
	{
		fout << f[i];
		if (f[i] > 9)
			fout << "  ";
		else fout << "   ";
		if ((i + 1) % 4 == 0)
			fout << endl;
	}
}

bool solvable(const vector<int> & f)
{
	int n = 0;
	for (int i = 0; i < f.size(); ++i)
	{
		if (f[i])
		{
			for (int j = i + 1; j < f.size(); ++j)
				if (f[j] && f[j] < f[i])
					++n;
		}
		if (f[i] == 0)
			n += i / 4 + 1;
	}

	return (n % 2 == 0);
}

bool is_solved(const vector<int> & f)
{
	for (int i = 0; i < f.size(); ++i)
		if (f[i] && f[i] != i + 1)
			return false;
	return true;
}

// find index of zero tile
inline int find_zero(const vector<int> & f)
{
	for (int i = 0; i < f.size(); ++i)
		if (f[i] == 0)
			return i;
	return -1;
}

void print_answer(Node* start, Node* res)
{
	int steps = res->step;
	while (res->parent != nullptr)
	{
		print_field(res->field);
		fout << "\n    ^\n    |\n\n";
		res = res->parent;
	}
	print_field(res->field);
	cout << "\nSolved in " << steps << " steps\n";
}

std::deque<Node*> next_nodes(Node* n)
{
	std::deque<Node*> result;
	node_ptr_compare eq;

	int zero_ind = find_zero(n->field);
	if (zero_ind - 4 >= 0)	// не самый верхний
	{
		Node * t = new Node(n, n->field);
		std::swap(t->field[zero_ind], t->field[zero_ind - 4]);
		if (n->parent == nullptr || !eq(t, n->parent))
			result.push_back(t);
		else delete t;
	}
	if (zero_ind + 4 <= 15)	// не самый нижний
	{
		Node * t = new Node(n, n->field);
		std::swap(t->field[zero_ind], t->field[zero_ind + 4]);
		if (n->parent == nullptr || !eq(t, n->parent))
			result.push_back(t);
		else delete t;
	}
	if (zero_ind % 4 != 0) // не самый левый
	{
		Node * t = new Node(n, n->field);
		std::swap(t->field[zero_ind], t->field[zero_ind - 1]);
		if (n->parent == nullptr || !eq(t, n->parent))
			result.push_back(t);
		else delete t;
	}
	if (zero_ind % 4 != 3) // не самый правый
	{
		Node * t = new Node(n, n->field);
		std::swap(t->field[zero_ind], t->field[zero_ind + 1]);
		if (n->parent == nullptr || !eq(t, n->parent))
			result.push_back(t);
		else delete t;
	}
	return result;
}


void A_star(const vector<int> & f_start)
{
	if (!solvable(f_start))
		cout << "It is unsolvable.\n";
	else
	{
		Node * start = new Node(nullptr, f_start);
		std::priority_queue<Node*, vector<Node*>, cmp_with_heuristic> q;
		std::unordered_set<Node*, decltype(nodeHash), decltype(node_ptr_eq)> used(2000, nodeHash, node_ptr_eq);

		Node* res = nullptr;

		q.push(start);

		while (!q.empty())
		{
			Node *n = q.top();
			q.pop();
			
			if (is_solved(n->field))
			{
				res = n;

				while (!q.empty())
				{
					Node* t = q.top();
					q.pop();
					delete t;
				}
				break;
			}

			used.insert(n);

			for (auto t : next_nodes(n))
			{
				if (used.find(t) == used.end())// || n->f() > t->f())
				{
					q.push(t);
				}
				else delete t;
			}
		}
		if (res != nullptr)
		{
			print_answer(start, res);
		}

		for (auto el : used)
		{
			el->parent = nullptr;
			delete el;
		}
	}
}



#endif // !A_STAR_ALG
