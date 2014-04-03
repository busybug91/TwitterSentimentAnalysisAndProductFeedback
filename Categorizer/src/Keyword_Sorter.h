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
	string month,product;
	Keyword_Sorter(string val,string pro)
	{
		month=val;
		product=pro;
	}
	int get_keywords(string file_path,int threshold,string qualifier)
	{

		string read_string,line,word;

		ifstream valence_file("C:\\users\\sai bros\\desktop\\valence.csv");
		
		double valence;
		unordered_map<string,double> valence_map;
		while(getline(valence_file,read_string,','))
		{
			word=read_string;
			getline(valence_file,read_string,'\n');
			valence=stof(read_string);
			pair<string,double> valence_pair(word,valence);
			valence_map.insert(valence_pair);
		}

		valence_file.close();

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

				int word_presence=(valence_map.count(word)>0)?1:0;
				if(!word_presence)
				{
					string stem_last = read_string.substr(0, read_string.size()-1);
					string stem_lasttwo = read_string.substr(0, read_string.size()-2);
					string stem_lastthree = read_string.substr(0, read_string.size()-3);
					if(!word_presence)
						word_presence=(valence_map.count(stem_last)>0)?1:0;
					else if(!word_presence)
						word_presence=(valence_map.count(stem_lasttwo)>0)?1:0;
					else if(!word_presence)
						word_presence=(valence_map.count(stem_lastthree)>0)?1:0;
				}

				if(stop_words.count(word)<=0 && word!="" && word_presence<=0)
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

		ofstream keywords_file("C:\\users\\sai bros\\desktop\\"+product+qualifier+month+".txt");

		for(int i=max_occurrence;i>0;i--)
		{
			auto range = features.equal_range(i);
			for(auto element=range.first;element!=range.second;element++)
			{
				keywords_file<<element->first<<":\t"<<element->second<<"\n";
			}
		}

		keywords_file.close();

		return 0;
	}
};