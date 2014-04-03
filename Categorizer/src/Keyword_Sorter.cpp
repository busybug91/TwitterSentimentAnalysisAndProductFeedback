#include "stdafx.h"
#include "iostream"
#include "sstream"
#include "fstream"
#include "string"
#include "unordered_map"
#include "unordered_set"
#include "algorithm"
#include "cctype"

using namespace std;

class Keyword_Sorter
{
public:
	int get_keywords(string file_path,int threshold)
	{

		string read_string,line,word;
		ifstream stop_words_file ("C:\\users\\sai bros\\desktop\\stop_words.txt");

		unordered_set<string> stop_words;
		while(getline(stop_words_file,read_string,'\n'))
		{
			word=read_string;
			stop_words.insert(word);
		}
	
		stop_words_file.close();

		ifstream tweets_file(file_path);

		unordered_map<string,int> keywords;
		int max_occurrence=1;
		while(getline(tweets_file,line,'\n'))
		{
			istringstream words(line);
			while(getline(words,word,' '))
			{
				if(word!="")
					word[0]=tolower(word[0]);
				if(stop_words.count(word)<=0 && word!="")
				{
					if(keywords.count(word)>0)
					{
						keywords[word]++;
						int count=keywords[word];
						if(count>max_occurrence)
						{
							max_occurrence=count;
						}
					}
					else
					{
						pair<string,int> keyword(word,1);
						keywords.insert(keyword);
					}
				}
			}
		}

		tweets_file.close();

		unordered_multimap<int,string> features;
		for(auto keyword=keywords.begin();keyword!=keywords.end();keyword++)
		{
			if(keyword->second>threshold)
			{
				//cout<<keyword->first<<":\t"<<keyword->second<<"\n";
				pair<int,string> feature(keyword->second,keyword->first);
				features.insert(feature);
			}
		}

		for(int i=max_occurrence;i>0;i--)
		{
			auto range = features.equal_range(i);
			for(auto element=range.first;element!=range.second;element++)
			{
				cout<<element->first<<":\t"<<element->second<<"\n";
			}
		}

		return 0;
	}
};

//int main()
//{
//	//in threshold=1;
//	//Date_Splitter split(threshold);
//	//split.date_split();
//	Keyword_Sorter keywords;
//	keywords.get_keywords("C:\\users\\sai bros\\desktop\\sentimentAprbad.txt",1);
//	getchar();
//}