#include <vector>
#include <algorithm>
using namespace std;

// ascii [0, 99] - numbers [0, 99]
// ascii [100-109] - number of hundreds [1, 10]
// ascii 110 - delimeter

// max possible integer in array
const int MAX_VALUE = 300;

// max number of elements in array 
const int MAX_SIZE = 1000;

const char DELIMETER = char(110);

/*
Integer to string conversion
char(100) is 1 hundred
...
char(109) is 10 hundreds

So each number is converted to at most two ascii symbols
*/
string numToAscii(int num) {
	string res = "";
	if (num >= 100) res += char(99 + num / 100);
	res += char(num % 100);
	return res;
}

/*
Given:
	deserializable string s,
	start index i for current integer

index is passed by reference to update it at once
*/
int asciiToNum(string& s, int& i) {
	int res = 0;
	if (int(s[i]) >= 100) {
		res += (int(s[i++]) - 99) * 100;
	}
	res += int(s[i++]);
	return res;
}

/*
1. Count the number of occurences of each unique integer in array
2. Make a set of unique array members for each unique number of occurences
3. Put the number of occurences in resulting string first, 
	followed by the unique array members from its set
4. Repeat the 3rd step, putting delimeter between the parts
*/
string serialize(vector<int> a) {
	vector<int> mapik(MAX_VALUE + 1, 0);
	vector<vector<int> > mapik2(MAX_SIZE + 1, vector<int>());
	for (int i = 0; i < a.size(); i++) {
		mapik[a[i]]++;
	}
	for (int i = 1; i <= MAX_VALUE; i++) {
		mapik2[mapik[i]].push_back(i);
	}
	string res = "";
	for (int i = 1; i <= MAX_SIZE; i++) {
		if (mapik2[i].size() == 0) continue;
		res += numToAscii(i);
		for (int j = 0; j < mapik2[i].size(); j++) {
			res += numToAscii(mapik2[i][j]);
		}
		res += DELIMETER;
	}
	res.pop_back();
	return res;
}

/*
Repeat the following while string is not deserialized fully:
1. Deserialize the first integer - it is number of occurences "count"
2. Repeat the following while current index is not out-of-string and points to non-delimeter char:
	a) Parse the next integer "num" - array member with "count" number of occurences
	b) If current char is delimeter, shift index by one to the right and go to the 1st step
*/
vector<int> deserialize(string s) {
	vector<int> res;
	int i = 0;
	while (i < s.size()) {
		int count = asciiToNum(s, i);
		while (i < s.size() && s[i] != DELIMETER) {
			int num = asciiToNum(s, i);
			for (int j = 0; j < count; j++) {
				res.push_back(num);
			}
		}
		if (i < s.size() && s[i] == DELIMETER) {
			i++;
		}
	}
	return res;
}