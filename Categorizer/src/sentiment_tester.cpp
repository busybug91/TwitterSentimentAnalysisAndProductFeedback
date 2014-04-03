// categorizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "sstream"
#include "fstream"
#include "string"
#include "unordered_map"
#include "unordered_set"
using namespace std;

class Sentiment_Analyzer
{
	public:
	Sentiment_Analyzer()
	{
	}
	// this class contains function for analyzing the sentiments of a file
	double get_closest_word(unordered_map<string,double> valence_map,string read_string)
	{
		for(auto element=valence_map.begin();element!=valence_map.end();element++)
		{
			if(read_string.find(element->first) != string::npos)
			{
				return element->second;
			}
		}
		return 0;
	}

	int get_sentiments(){
		cout<<"Sentiment";
		ifstream infile ("C:\\users\\sai bros\\desktop\\valence.csv");
		string word,read_string;

		double valence;
		bool read=true;
		unordered_map<string,double> valence_map;
		while(getline(infile,read_string,','))
		{
			word=read_string;
			getline(infile,read_string,'\n');
			valence=stof(read_string);
			pair<string,double> valence_pair(word,valence);
			valence_map.insert(valence_pair);
		}
	
		infile.close();

		ifstream stop_words_file ("C:\\users\\sai bros\\desktop\\stop_words.txt");

		unordered_set<string> stop_words;
		while(getline(stop_words_file,read_string,'\n'))
		{
			word=read_string;
			stop_words.insert(word);
		}
	
		stop_words_file.close();

		ifstream sentence_file ("C:\\users\\sai bros\\desktop\\test.txt");
		string sentence;

		while(getline(sentence_file,sentence,'\n'))
		{
			double sentence_val=0.0,num_words=0.0;
			bool not_operator=false;

			istringstream test_string(sentence);

			while(getline(test_string,read_string,' '))
			{
				//tolower(read_string[0]);
				if(read_string=="not")
				{
					not_operator=true;
				}
				double val=0.0;int word_presence=valence_map.count(read_string);

				if((stop_words.count(read_string)<=0) || (word_presence>0))
				{
					if(word_presence>0)
					{					
						val=valence_map.at(read_string);
					}
					else
					{
						val=get_closest_word(valence_map,read_string);
					}
				
					if(not_operator)
					{
		/*					if(val>5)
						{
							sentence_val+=(val-5);
						}
						else
						{
							sentence_val+=5;
						}*/
						sentence_val-=val;
						not_operator=false;
					}
					else
					{
						sentence_val+=val;
					}
				}
				num_words++;
			}
			sentence_val/=num_words;
			cout<<sentence<<"\t"<<sentence_val<<endl;
		}

		sentence_file.close();
		return 0;
	}
};
//int main()
//{
//	Sentiment_Analyzer sai;
//	sai.get_sentiments();
//	getchar();
//	return 0;
//}