// categorizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "sstream"
#include "fstream"
#include "string"
#include "unordered_map"
#include "unordered_set"
#include "Keyword_Sorter.h"
using namespace std;

class Sentiment_Analyzer
{
public:
	int threshold;
	Sentiment_Analyzer(int val)
	{
		threshold=val;
	}
	// this class contains function for analyzing the sentiments of a file
	/*double get_closest_word(unordered_map<string,double> valence_map,string read_string)
	{
		string stem_last = read_string.substr(0, read_string.size()-1);
		string stem_lasttwo = read_string.substr(0, read_string.size()-2);
		string stem_lastthree = read_string.substr(0, read_string.size()-3);
		if(valence_map.count(stem_last)>0)
			return valence_map.at(stem_last);
		else if(valence_map.count(stem_lasttwo)>0)
			return valence_map.at(stem_lasttwo);
		else if(valence_map.count(stem_lastthree)>0)
			return valence_map.at(stem_lastthree);

		return 0;
	}*/

	int get_sentiments(string file_path,string month,string keyword)
	{
		Keyword_Sorter keywords(month,keyword);
		ifstream infile ("C:\\users\\sai bros\\desktop\\valence.csv");
		string word,read_string;

		string bad_senti_file = "C:\\users\\sai bros\\desktop\\" + keyword + "sentiment" + month + "bad.txt",good_senti_file = "C:\\users\\sai bros\\desktop\\" + keyword + "sentiment" + month + "good.txt";
		ofstream good_file(good_senti_file);
		ofstream bad_file(bad_senti_file);

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

		ifstream sentence_file (file_path);
		string sentence;

		while(getline(sentence_file,sentence,'\n'))
		{
			double sentence_val=0.0,num_words=0.0;
			bool not_operator=false;

			istringstream test_string(sentence);

			while(getline(test_string,read_string,' '))
			{
				if(read_string!="")
					read_string[0]=tolower(read_string[0]);
				if(read_string=="not")
				{
					not_operator=true;
				}
				double val=0.0;
				int word_presence=valence_map.count(read_string);

				if(((stop_words.count(read_string)<=0) && (read_string!="")) || (word_presence>0))
				{
					if(word_presence>0)
					{					
						val=valence_map.at(read_string);
					}
					else
					{
						string stem_last = read_string.substr(0, read_string.size()-1);
						string stem_lasttwo = read_string.substr(0, read_string.size()-2);
						string stem_lastthree = read_string.substr(0, read_string.size()-3);
						if(valence_map.count(stem_last)>0)
							val=valence_map.at(stem_last);
						else if(valence_map.count(stem_lasttwo)>0)
							val=valence_map.at(stem_lasttwo);
						else if(valence_map.count(stem_lastthree)>0)
							val=valence_map.at(stem_lastthree);
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
			if(sentence_val<0)
			{
				bad_file<<sentence<<"\n";
			}
			else if(sentence_val>0.2)
			{
				good_file<<sentence<<"\n";
			}
		}

		sentence_file.close();
		good_file.close();
		bad_file.close();

		cout<<"Extracting +ve features in "<<month<<"\n";
		keywords.get_keywords(good_senti_file,threshold,"Good");
		cout<<"Extracting -ve features in "<<month<<"\n";
		string qualifier="Bad";
		keywords.get_keywords(bad_senti_file,threshold,qualifier);

		return 0;
	}
};