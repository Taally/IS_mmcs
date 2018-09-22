#include "a_star_alg.h"
#include "ida_star_alg.h"




int main()
{
	
//	vector<int> f_start = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 };	// initial field
//	vector<int> f_start = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15 };

//	vector<int> f_start = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 12, 13, 14, 11, 15 };	//+ 2 steps
//	vector<int> f_start = { 1, 0, 2, 4, 5, 7, 3, 8, 9, 6, 10, 12, 13, 14, 11, 15 };	//+ 7 steps
//	vector<int> f_start = { 5, 1, 3, 4, 9, 2, 7, 8, 13, 6, 10, 12, 14, 0, 11, 15 }; //+ 10 steps
//	vector<int> f_start = { 2, 5, 3, 4, 1, 7, 10, 8, 9, 0, 6, 12, 13, 14, 11, 15 };	//+ 11 steps
//	vector<int> f_start = { 2, 10, 4, 8, 1, 6, 3, 11, 5, 9, 7, 0, 13, 14, 15, 12 };	//+ 15 steps
//  vector<int> f_start = { 1, 0, 2, 3, 5, 7, 10, 4, 9, 8, 6, 12, 13, 14, 11, 15 };	//+ 15 steps
//	vector<int> f_start = { 5, 1, 0, 3, 7, 10, 2, 4, 9, 8, 6, 12, 13, 14, 11, 15 };	//+ 20 steps

//	vector<int> f_start = { 10, 6, 4, 13, 8, 11, 3, 9, 1, 5, 14, 12, 0, 2, 15, 7 }; //+ 51 steps
//	vector<int> f_start = { 15, 4, 12, 9, 3, 11, 1, 14, 13, 7, 5, 8, 0, 6, 10, 2 }; //+ 53
//	vector<int> f_start = { 3, 12, 6, 10, 14, 13, 5, 1, 15, 2, 11, 9, 0, 7, 8, 4 }; //+ 57

//	vector<int> f_start = { 5, 1, 7, 4, 0, 13, 6, 12, 9, 3, 10, 2, 14, 8, 11, 15 }; //+ 33 - 31
//	vector<int> f_start = { 0, 2, 4, 8, 1, 10, 6, 3, 5, 14, 7, 11, 9, 13, 15, 12 }; //+ 14

//	vector<int> f_start = { 1, 4, 3, 2, 5, 6, 12, 8, 9, 10, 11, 7, 13, 14, 15, 0 }; // + 24

//	vector<int> f_start = { 1, 2, 3, 4, 9, 5, 6, 0, 14, 13, 10, 7, 15, 12, 8, 11 }; // 20 - 12349560EDA7FC8B
//	vector<int> f_start = { 1, 2, 3, 4, 5, 6, 7, 8, 10, 9, 0, 11, 12, 15, 13, 14 };	// 26 - 12345678A90BCFDE

	vector<int> f_start = read_field();

//	cout << h(f_start) << endl;

	time_t time_start;
	double dur;

	time_start = clock();
	A_star(f_start);
	dur = double(clock() - time_start) / CLOCKS_PER_SEC;
	cout << "Time for a*: " << dur << endl;
	
	time_start = clock();
	ida_star(f_start);
	dur = double(clock() - time_start) / CLOCKS_PER_SEC;
	cout << "Time for ida*: " << dur << endl;
	
	
	system("pause");
}

/*


Solved in 57 steps
Time for a*: 58.457

Solved in 57 steps
Time for ida*: 51.194

---
Solved in 57 steps
Time for a*: 54.819

Solved in 57 steps
Time for ida*: 51.586
--

Solved in 51 steps
Time for a*: 17.799

Solved in 51 steps
Time for ida*: 23.854
---

*/