#include "stdafx.h"
#include "iostream"
#include "sstream"
#include "fstream"
#include "string"
#include "unordered_map"
#include "unordered_set"
#include "algorithm"
#include "cctype"
#include "Sentiment_Analyzer.h"

using namespace std;

class Date_Splitter
{
public:
	int threshold;
	Date_Splitter(int val)
	{
		threshold=val;
	}
	struct non_english_remove {
		bool operator()(char c) const {
			return (((int)c<0) || ((int)c>255));
	    }
	};
	int date_split(string file_path,string keyword)
	{
		Sentiment_Analyzer sentiment(threshold);
		//ifstream infile ("C:\\users\\sai bros\\desktop\\tweet_reduce.csv");
		ifstream infile (file_path);
		string line;
		string unused,user,date,tweet;
		//string apr_path="C:\\users\\sai bros\\desktop\\tweetsApr.txt",may_path="C:\\users\\sai bros\\desktop\\tweetsMay.txt",jun_path="C:\\users\\sai bros\\desktop\\tweetsJun.txt";
		string apr_path="C:\\users\\sai bros\\desktop\\" + keyword + "tweetsApr.txt",may_path="C:\\users\\sai bros\\desktop\\" + keyword + "tweetsMay.txt",jun_path="C:\\users\\sai bros\\desktop\\" + keyword + "tweetsJun.txt";

		unordered_set<string> users;
		ifstream user_file("C:\\users\\sai bros\\desktop\\users.txt");
		while(getline(user_file,user,'\n'))
		{
			users.insert(user);
		}


		ofstream tweet_file[3];
		tweet_file[0].open(apr_path);
		tweet_file[1].open(may_path);
		tweet_file[2].open(jun_path);

		unordered_map<string,int> month_map;
		string months[]={"Apr","May","Jun"};
		for(int i=0;i<3;i++)
		{
			pair<string,int> index(months[i],i);
			month_map.insert(index);
		}

		string month;
		int tweet_number=0;
		while(getline(infile,line,'\n'))
		{
			istringstream line_contents(line);
			getline(line_contents,unused,',');
			getline(line_contents,unused,',');
			getline(line_contents,date,',');
			istringstream date_contents(date);

			getline(date_contents,unused,' ');
			getline(date_contents,month,' ');

			getline(line_contents,unused,',');
			getline(line_contents,user,',');
			getline(line_contents,tweet,'\0');
			if(users.count(user)>0)
			{
				tweet.erase(remove_if(tweet.begin(), tweet.end(), non_english_remove()), tweet.end());
				tweet.erase (remove_if (tweet.begin (), tweet.end (), ispunct), tweet.end ());
				tweet_file[month_map.at(month)]<<tweet<<"\n";
			}
		}
		infile.close();

		for(int i=0;i<3;i++)
		{
			tweet_file[i].close();
		}

		cout<<"Analyzing sentiments of April"<<"\n";
		sentiment.get_sentiments(apr_path,"Apr",keyword);

		cout<<"Analyzing sentiments of May"<<"\n";
		sentiment.get_sentiments(may_path,"May",keyword);

		cout<<"Analyzing sentiments of June"<<"\n";
		sentiment.get_sentiments(jun_path,"Jun",keyword);

		return 0;
	}
};

