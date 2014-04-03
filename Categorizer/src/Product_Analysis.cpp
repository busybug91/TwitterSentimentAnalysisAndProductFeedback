#include "stdafx.h"
#include "Date_Splitter.h"

int main()
{
	int threshold=2;
	Date_Splitter split(threshold);
	string file_1="C:\\users\\sai bros\\desktop\\data_mac.csv";
	string file_2="C:\\users\\sai bros\\desktop\\data_windows.csv";
	cout<<"Analyzing Mac"<<endl;
	split.date_split(file_1,"Mac");
	cout<<"Analyzing Windows"<<endl;
	split.date_split(file_2,"Windows");
	getchar();
}