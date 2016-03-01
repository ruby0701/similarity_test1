// similarity_test1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


int main()
{
	//open 2 files in 2 for loops
	string fileName1 = "test1.txt";//PTT
	string fileName2 = "test2.txt";//FB
	ifstream file1;
	ifstream file2;

	file1.open(fileName1);
	file2.open(fileName2);

	while (!file1.is_open() || !file2.is_open())
	{
		cout << "fail to open file!" << endl;
		system("pause");
		return 0;
	}

	//store the datas from 2 files individually, use string array , do the rest of the processing in each function
	string data1[12];
	string data2[12];

	for (int i = 0; i < 12; i++)
	{
		data1[i] = "";
		data2[i] = "";
	}

	int count = 1;
	while (!file1.eof())
	{
		if (count < 10)
		{
			string temp = "";
			getline(file1, temp);
			temp = temp.substr(2, temp.length());
			data1[count - 1] = temp;
			cout << data1[count - 1] << endl;
			count++;
		}
		if (count >= 10)
		{
			string temp = "";
			getline(file1, temp);
			temp = temp.substr(3, temp.length());
			data1[count - 1] = temp;
			cout << data1[count - 1] << endl;
			count++;
		}
	}

	count = 1;
	while (!file2.eof())
	{	
		if (count < 10)
		{
			string temp = "";
			getline(file2, temp);
			temp = temp.substr(2, temp.length());
			data2[count - 1] = temp;
			cout << data2[count - 1] << endl;
			count++;
		}
		if (count >= 10)
		{
			string temp = "";
			getline(file2, temp);
			temp = temp.substr(3, temp.length());
			data2[count - 1] = temp;
			cout << data2[count - 1] << endl;
			count++;
		}
	}

	file1.close();
	file2.close();

	//use double array to record the results of comparing¡Acalaulate first, consider output format later
	double similarity[12];

	//open this file for recording all the situations that are out of control
	ofstream logFile;
	logFile.open("report.txt");

	//function1, similarity for name, LCS

	//function2, similarity for gender, 0/1
	if (data1[1] == data2[1])
	{
		similarity[1] = 1;
	}
	else
	{
		similarity[1] = 0;
	}

	//function3, similarity for birthday, 0/1 and jacard

	//function4, similarity for blood type, 0/1
	if (data1[3] == data2[3])
	{
		similarity[3] = 1;
	}
	else
	{
		similarity[3] = 0;
	}

	//function5, similarity for location, 0/1 and jacard

	//function6, similarity for education, 0/1 and jacard

	//function7, similarity for career, 0/1
	if (data1[6] == "" || data2[6] == "")
	{
		similarity[6] = 0;

		logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
		logFile << "similarity of career is 0 :" << endl;
		logFile << "some data doesn't exist!" << endl;
		logFile << "1 : " << data1[6] << " vs. " << "2 : " << data2[6] << endl << endl;
	}
	else if (data1[6] != "" || data2[6] != "")
	{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (data1[6] == data2[6])//have problems here!!!!!
		{
			similarity[6] = 1;
		}
		if (data1[6] != data2[6])//report problems
		{
			similarity[6] = 0;

			logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
			logFile << "similarity of career is 0 :" << endl;
			logFile << "needs double checking!" << endl;
			logFile << "1 : " << data1[6] << " vs. " << "2 : " << data2[6] << endl << endl;
		}
	}

	//function8, similarity for company, 0/1
	if (data1[7] == "" || data2[7] == "")
	{
		similarity[7] = 0;

		logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
		logFile << "similarity of company is 0 :" << endl;
		logFile << "some data doesn't exist!" << endl;
		logFile << "1 : " << data1[7] << " vs. " << "2 : " << data2[7] << endl << endl;
	}
	else if (data1[7] != "" || data2[7] != "")
	{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (data1[7] == data2[7])//have problems here!!!!!
		{
			similarity[7] = 1;
		}
		if (data1[7] != data2[7])//report problems
		{
			similarity[7] = 0;

			logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
			logFile << "similarity of company is 0 :" << endl;
			logFile << "needs double checking!" << endl;
			logFile << "1 : " << data1[7] << " vs. " << "2 : " << data2[7] << endl << endl;
		}
	}

	//function9, similarity for hobby, SMC
	if (data1[8] != "" && data2[8] != "")
	{
		string sentence1 = data1[8];//PTT,;
		string sentence2 = data2[8];//FB,¡B

		string temp1[26];//at most 26 types
		string temp2[26];

		stringstream ss(sentence1);//PTT
		string item;
		int i = 0;
		int deno = 0;
		while (getline(ss, item, ';')) 
		{
			temp1[i] = item;
			i++;
		}
		deno = i;

		stringstream ss2(sentence2);//FB
		string item2;
		i = 0;
		while (getline(ss2, item2, ';'))
		{
			temp2[i] = item2;
			i++;
		}

		int same = 0;
		for (int i = 0; i < deno; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				if (temp1[i] == temp2[j])
				{
					same++;
				}
			}
		}
		
		similarity[8] = (double)same / (double)deno;

	}
	else if (data1[8] == "" || data2[8] == "")
	{
		similarity[8] = 0;//equals to 0 or just blank?
	}

	//function10, similarity for marital status, 0/1
	if (data1[7] == "" || data2[7] == "")
	{
		similarity[7] = 0;
	}
	else if (data1[7] != "" || data2[7] != "")
	{
		if (data1[7] == data2[7])//beware of different formatting
		{
			similarity[7] = 1;
		}
	}

	//function11, similarity for other social network, 0/1
	if (data1[10] != "" && data2[10] != "")
	{
		string sentence1 = data1[10];//PTT,;
		string sentence2 = data2[10];//FB,¡B

		string temp1[5];//at most 26 types
		string temp2[5];

		stringstream ss(sentence1);//PTT
		string item;
		int i = 0;
		int deno = 0;
		while (getline(ss, item, ';'))
		{
			temp1[i] = item;
			i++;
		}
		deno = i;

		stringstream ss2(sentence2);//FB
		string item2;
		i = 0;
		while (getline(ss2, item2, ';'))
		{
			temp2[i] = item2;
			i++;
		}

		int same = 0;
		for (int i = 0; i < deno; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (temp1[i] == temp2[j])
				{
					same++;
				}
			}
		}

		similarity[10] = (double)same / (double)deno;

	}
	else if (data1[10] == "" || data2[10] == "")
	{
		similarity[10] = 0;//equals to 0 or just blank?
	}


	//output similarity for debug
	cout << "Similarity : " << endl;

	for (int i = 0; i < 11; i++)
	{
		cout << similarity[i] << endl;
	}

//========================================================================================================
	/*
	for each data that are absent of couldn't have a result for some reason, 
	output the file names and all the original data to another file for later 
	human comparison	
	*/
//========================================================================================================

	system("pause");
	return 0;
}