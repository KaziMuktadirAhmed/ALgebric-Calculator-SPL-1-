#include <bits/stdc++.h>
using namespace std;

bool cmpfunc(pair<string, int> a, pair<string, int> b)
{
	char a1 = a.first[0];
	char b1 = b.first[0];

	if (a1 < b1)
		return true;
	else
		return false;
}

int main(void)
{
	vector <pair<string,int>> container;

	for (int i=0; i<4; ++i) {
		pair <string, int> pa;

		cin >> pa.first >> pa.second;

		container.push_back(pa);
	}

	sort(container.begin(), container.end(), cmpfunc);

	for (int i=0; i<4; ++i) {
		cout << container[i].first << " " << container[i].second << endl;	
	}

	return 0;
}