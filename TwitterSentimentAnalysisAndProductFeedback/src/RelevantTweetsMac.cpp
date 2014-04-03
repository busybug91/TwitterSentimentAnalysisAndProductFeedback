
#include "stdafx.h";
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<cassert>
#include<utility>
#include "string";
#include "sstream";
#include <unordered_map>
using namespace std;

const long MOD = 1000003;

typedef unsigned long long bigi;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
#define LOP(i, from, to) for (int i = (from); i < (to); ++i)
#define FOR(i, n) LOP(i, 0, (n))
#define ALL(x) x.begin(), x.end()
#define SIZE(x) (int)x.size()
#define PB push_back
//vector<vector<long long int> >  comb(21, vector<long long int>(21, 0));


int main()
{


	freopen("/Users/rbh/Desktop/SMM/Part2/Dataset/trainingtestdata1.csv", "rb", stdin);
	freopen("/Users/rbh/Desktop/SMM/Part2/Dataset/trainingtestdataoutputmac.csv", "wb", stdout);

	while (getline(cin, tweet, '\n')){
		string unused;
		string date;
		string tw;
		string user;
		string status;
		string unused2;
		//while (getline(cin, tweet, ',')){
		istringstream line_contents(tweet);
		getline(line_contents, unused, ',');
		getline(line_contents, status, ',');
		getline(line_contents, date, ',');
		getline(line_contents, unused2, ',');
		getline(line_contents, user, ',');
		getline(line_contents, tw, '\0');
		//tweets.push_back(tweet);
		tweets.push_back(unused);
		tweets.push_back(status);
		tweets.push_back(date);
		tweets.push_back(unused2);
		tweets.push_back(user);
		tweets.push_back(tw);
		//if (count == 6){
		//int found = tweet.find("love");

		int found1 = tw.find(" mac ");
		int found = tw.find(" Mac ");
		if (found1 >= 0 || found >= 0){
			for (std::vector<string>::iterator it = tweets.begin(); it != tweets.end(); ++it){
				std::cout << *it << ',';
			}
			//std::cout << '\n';

			//cout << tweets;
		}
		count = 0;
		tweets.clear();
		//}
		count++;

		//}


	}

	return 0;

}