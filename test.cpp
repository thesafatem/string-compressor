#include "serializer.cpp"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

void createTestFile(vector<int> &res, string name) {
	string s = "";
	for (int i = 0; i < res.size(); i++) {
		s += to_string(res[i]) + ",";
	}
	s.pop_back();
	string serialized = serialize(res);
	double compression = (s.size() - serialized.size()) * 100.0 / s.size();
	ofstream test(name);
	test << compression << endl << s << endl << serialized;
	test.close();
}

void genRandomTest(int sz, string name) {
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	vector<int> res;
	for (int i = 0; i < sz; i++) {
		int num = uniform_int_distribution<int>(1, 300)(rng);
		res.push_back(num);
	}
	createTestFile(res, name);
}

void genEdgeTest(int sz, int digits, string name) {
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	vector<int> res;
	int l, r;
	if (digits == 1) {
		l = 1;
		r = 9;
	} else if (digits == 2) {
		l = 10;
		r = 99;
	} else {
		l = 100;
		r = 300;
	}
	for (int i = 0; i < sz; i++) {
		int num = uniform_int_distribution<int>(l, r)(rng);
		res.push_back(num);
	}
	createTestFile(res, name);
}

void genThreeOccurencesTest(string name) {
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	vector<int> res;
	int sz = 300;
	vector<int> setik(301, 0);
	for (int i = 0; i < sz; i++) {
		int num = uniform_int_distribution<int>(1, 300)(rng);
		while (setik[num]) {
			num = uniform_int_distribution<int>(1, 300)(rng);
		}
		setik[num] = 1;
		for (int j = 0; j < 3; j++) {
			res.push_back(num);
		}
	}
	shuffle(res.begin(), res.end(), rng);
	createTestFile(res, name);
}

void genSmallTest(int sz, int l, int r, string name) {
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	vector<int> res;
	for (int i = 0; i < sz; i++) {
		int num = uniform_int_distribution<int>(l, r)(rng);
		res.push_back(num);
	}
	createTestFile(res, name);
}	

int main() {
	// how to check seriazizer and deserializer
	vector<int> a = {1, 2, 2, 3, 3, 3, 4, 5};
	string s = serialize(a);
	vector<int> d = deserialize(s);
	cout << s << endl;
	for (int i = 0; i < d.size(); i++) {
		if (i > 0) cout << ",";
		cout << d[i];
	}
	cout << endl;
}