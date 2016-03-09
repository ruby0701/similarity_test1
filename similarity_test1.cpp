// similarity_test1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctype.h>
using namespace std;

int KMP(string S, string K)
{
	vector<int> T(K.size() + 1, -1);
	vector<int> matches;

	if (K.size() == 0)
	{
		matches.push_back(0);
		return matches.size();
	}
	for (int i = 1; i <= K.size(); i++)
	{
		int pos = T[i - 1];
		while (pos != -1 && K[pos] != K[i - 1]) pos = T[pos];
		T[i] = pos + 1;
	}

	int sp = 0;
	int kp = 0;
	int k_stop = 0;
	while (sp < S.size())
	{
		while (kp != -1 && (kp == K.size() || K[kp] != S[sp])) kp = T[kp];
		kp++;
		sp++;
		if (kp == K.size())
		{
			//k_stop = kp;
			//matches.push_back((sp - K.size())-k_stop);
			matches.push_back(kp);
		}
	}

	int total = 0;
	for (int i = 0; i < matches.size(); i++)
	{	
		int temp = matches[i];
		total += temp;	
	}
	
	return total;
}

#define dataNum 51

int main()
{
	//open 2 files in 2 for loops
	for (int index_PTT = 1; index_PTT <= dataNum; index_PTT++)
	{
		for (int index_FB = 1; index_FB <= dataNum; index_FB++)
		{
			string fileName1 = to_string(index_PTT) + "_top_PTT.txt";//PTT
			string fileName2 = to_string(index_FB) + "test2.txt";//FB
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

			//function1, similarity for name, KMP
			if (data1[0] == "" || data2[0] == "")
			{
				similarity[0] = 0;

				logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
				logFile << "similarity of username is 0 :" << endl;
				logFile << "some data doesn't exist!" << endl;
				logFile << "1 : " << data1[0] << " vs. " << "2 : " << data2[0] << endl << endl;
			}
			else if (data1[0] != "" || data2[0] != "")
			{
				int i, j, x = 0;

				double result, max = 0;

				string sentence = data2[0];//FB,¡B
				string temp2[50];

				stringstream ss(sentence);//FB
				string item;
				int l = 0;
				while (getline(ss, item, ';'))
				{
					cout << "item " << l << " : " << item << endl;
					temp2[l] = item;
					l++;
				}

				string ptt, fb;
				double amount = 0;

				for (int t = l - 1; t >= 0; t--)
				{
					ptt = data1[0], fb = temp2[t];
					amount += KMP(data1[0], temp2[t]);
				}

				cout << amount << " : " << (ptt.size() - x);
				similarity[0] = amount / (ptt.size() - x);

				if (similarity[0] == 0 || similarity[0] > 1)
				{
					logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
					logFile << "similarity of username is 0 or larger than 1:" << endl;
					logFile << "needs double checking!" << endl;
					logFile << "1 : " << data1[0] << " vs. " << "2 : " << data2[0] << endl << endl;
				}

			}



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
			if (data1[2] != "" && data2[2] != "")
			{
				string sentence1 = data1[2];//PTT,;
				string sentence2 = data2[2];//FB,¡B

				string temp1[4];//at most 26 types
				string temp2[4];

				stringstream ss(sentence1);//PTT
				string item;
				int i = 0;
				int t1 = 0, t2 = 0;
				while (getline(ss, item, '/'))
				{
					temp1[i] = item;
					i++;
				}
				t1 = i;

				stringstream ss2(sentence2);//FB
				string item2;
				i = 0;
				while (getline(ss2, item2, '/'))
				{
					temp2[i] = item2;
					i++;
				}
				t2 = i;

				if (t1 == 2 && t2 == 2)//both MM/DD
				{
					if (temp1[0] == temp2[0] && temp1[1] == temp2[1])
					{
						similarity[2] = 0.8;
					}
				}

				if (t1 == 3 && t2 == 2)//YYYY/MM/DD and MM/DD
				{
					if (temp1[1] == temp2[0] && temp1[2] == temp2[1])
					{
						similarity[2] = 0.8;
					}
				}

				if (t1 == 2 && t2 == 3)//MM/DD and YYYY/MM/DD
				{
					if (temp1[0] == temp2[1] && temp1[1] == temp2[2])
					{
						similarity[2] = 0.8;
					}
				}

				if (t1 == 3 && t2 == 3)//YYYY/MM/DD and YYYY/MM/DD
				{
					if (temp1[1] == temp2[1] && temp1[2] == temp2[2])
					{
						similarity[2] = 0.8;
					}
					if (temp1[0] == temp2[0])
					{
						similarity[2] = 1;
					}
				}
				else if (t1 < 2 && t2 < 2)
				{
					similarity[2] = 0;

					logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
					logFile << "similarity of birthday is 0 :" << endl;
					logFile << "some data format is a bit off, needs double checking!" << endl;
					logFile << "1 : " << data1[2] << " vs. " << "2 : " << data2[2] << endl << endl;
				}

			}
			else if (data1[2] == "" || data2[2] == "")
			{
				similarity[2] = 0;

				logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
				logFile << "similarity of birthday is 0 :" << endl;
				logFile << "some data doesn't exist!" << endl;
				logFile << "1 : " << data1[2] << " vs. " << "2 : " << data2[2] << endl << endl;
			}

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
			if (data1[4] == "" || data2[4] == "")
			{
				similarity[4] = 0;

				logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
				logFile << "similarity of location is 0 :" << endl;
				logFile << "some data doesn't exist!" << endl;
				logFile << "1 : " << data1[4] << " vs. " << "2 : " << data2[4] << endl << endl;
			}
			else if (data1[4] != "" || data2[4] != "")
			{
				int i, j, x = 0;

				double result, max = 0;

				string sentence = data2[4];//FB,¡B
				string temp2[50];

				stringstream ss(sentence);//FB
				string item;
				int l = 0;
				while (getline(ss, item, ';'))
				{
					cout << "item " << l << " : " << item << endl;
					temp2[l] = item;
					l++;
				}

				string ptt, fb;
				double amount = 0;

				for (int t = l - 1; t >= 0; t--)
				{
					ptt = data1[4], fb = temp2[t];

					amount += KMP(data1[4], temp2[t]);
				}

				cout << amount << " : " << (ptt.size() - x);
				similarity[4] = amount / (ptt.size() - x);

				if (similarity[4] == 0 || similarity[4] > 1)
				{
					logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
					logFile << "similarity of location is 0 or larger than 1:" << endl;
					logFile << "needs double checking!" << endl;
					logFile << "1 : " << data1[4] << " vs. " << "2 : " << data2[4] << endl << endl;
				}
			}

			//function6, similarity for education, 0/1 and jacard
			if (data1[5] == "" || data2[5] == "")
			{
				similarity[5] = 0;

				logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
				logFile << "similarity of education is 0 :" << endl;
				logFile << "some data doesn't exist!" << endl;
				logFile << "1 : " << data1[5] << " vs. " << "2 : " << data2[5] << endl << endl;
			}
			else if (data1[5] != "" || data2[5] != "")
			{
				int i, j, x = 0;

				double result, max = 0;

				string sentence = data2[5];//FB,¡B
				string temp2[50];

				stringstream ss(sentence);//FB
				string item;
				int l = 0;
				while (getline(ss, item, ';'))
				{
					cout << "item " << l << " : " << item << endl;
					temp2[l] = item;
					l++;
				}

				string ptt, fb;
				double amount = 0;

				for (int t = l - 1; t >= 0; t--)
				{
					ptt = data1[5], fb = temp2[t];

					amount += KMP(data1[5], temp2[t]);
				}

				cout << amount << " : " << (ptt.size() - x);
				similarity[5] = amount / (ptt.size() - x);

				if (similarity[5] == 0 || similarity[5] > 1)
				{
					logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
					logFile << "similarity of education is 0 or larger than 1:" << endl;
					logFile << "needs double checking!" << endl;
					logFile << "1 : " << data1[5] << " vs. " << "2 : " << data2[5] << endl << endl;
				}
			}

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
				int i, j, x = 0;

				double result, max = 0;

				string sentence = data2[6];//FB,¡B
				string temp2[50];

				stringstream ss(sentence);//FB
				string item;
				int l = 0;
				while (getline(ss, item, ';'))
				{
					cout << "item " << l << " : " << item << endl;
					temp2[l] = item;
					l++;
				}

				string ptt, fb;
				double amount = 0;

				for (int t = l - 1; t >= 0; t--)
				{
					ptt = data1[6], fb = temp2[t];

					amount += KMP(data1[6], temp2[t]);
				}

				cout << amount << " : " << (ptt.size() - x);
				similarity[6] = amount / (ptt.size() - x);

				if (similarity[6] == 0 || similarity[6] > 1)
				{
					logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
					logFile << "similarity of career is 0 or larger than 1:" << endl;
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
				int i, j, x = 0;

				double result, max = 0;

				string sentence = data2[7];//FB,¡B
				string temp2[50];

				stringstream ss(sentence);//FB
				string item;
				int l = 0;
				while (getline(ss, item, ';'))
				{
					cout << "item " << l << " : " << item << endl;
					temp2[l] = item;
					l++;
				}

				string ptt, fb;
				double amount = 0;

				for (int t = l - 1; t >= 0; t--)
				{
					ptt = data1[7], fb = temp2[t];

					amount += KMP(data1[7], temp2[t]);
				}

				cout << amount << " : " << (ptt.size() - x);
				similarity[7] = amount / (ptt.size() - x);

				if (similarity[7] == 0 || similarity[7] > 1)
				{
					logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
					logFile << "similarity of company is 0 or larger than 1:" << endl;
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
			if (similarity[8] == 0)//report problems
			{
				logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
				logFile << "similarity of hobby is 0 :" << endl;
				logFile << "needs double checking!" << endl;
				logFile << "1 : " << data1[8] << " vs. " << "2 : " << data2[8] << endl << endl;
			}

			//function10, similarity for marital status, 0/1
			if (data1[9] == "" || data2[9] == "")
			{
				similarity[9] = 0;
			}
			else if (data1[9] != "" || data2[9] != "")
			{
				if (data1[9] == data2[9])//beware of different formatting
				{
					similarity[9] = 1;
				}

				if (data1[9] != data2[9])//report problems
				{
					similarity[9] = 0;

					logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
					logFile << "similarity of marital status is 0 :" << endl;
					logFile << "needs double checking!" << endl;
					logFile << "1 : " << data1[9] << " vs. " << "2 : " << data2[9] << endl << endl;
				}
			}
			if (similarity[9] == 0)//report problems
			{
				logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
				logFile << "similarity of marital status is 0 :" << endl;
				logFile << "needs double checking!" << endl;
				logFile << "1 : " << data1[9] << " vs. " << "2 : " << data2[9] << endl << endl;
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
			if (similarity[10] == 0)//report problems
			{
				logFile << "files : " + fileName1 + " vs. " + fileName2 << endl;
				logFile << "similarity of SNS is 0 :" << endl;
				logFile << "needs double checking!" << endl;
				logFile << "1 : " << data1[10] << " vs. " << "2 : " << data2[10] << endl << endl;
			}


			//output similarity for debug
			cout << endl << "Similarity : " << endl;

			for (int i = 0; i < 11; i++)
			{
				cout << similarity[i] << endl;
			}
		}
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