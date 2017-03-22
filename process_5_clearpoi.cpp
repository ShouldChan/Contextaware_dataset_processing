//5:去除poi中因源数据集原因的重复和不存在的编号
#include<iostream>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<string.h>
#include<stdio.h>
#include<vector>
#include<map>
#include<cstdlib>
#include<time.h>
#include <functional> 
#include<stdlib.h>
#include <malloc.h>
using namespace std;

#define ifilename "E:\\context_t+d\\poi_t+d.txt"
#define ofilename "E:\\context_t+d\\poi2_t+d.txt"

//自定义结构体，用于存储每行数据
struct Data{
	int poiid; string lat; string lon;
};

//自定义的vector的pushback函数
void myPushback(vector<Data> & vecData, const int &pid, const string &la, const string &lo){
	Data data;
	data.poiid = pid; data.lat = la; data.lon = lo;
	vecData.push_back(data);
}
bool sortBy(const int &s1, const int &s2){
	return s1 < s2;
}

void getTest(){
	ifstream fin(ifilename);
	ofstream fout(ofilename);
	if (!fin){
		cout << "error!" << endl;
	}
	//一路将行记录存入vector
	vector<Data> vecStr;
	string s;
	while (!fin.eof()){
		int pid;
		string str[2];
		fin >> pid >> str[0] >> str[1];
		getline(fin, s);
		myPushback(vecStr, pid, str[0], str[1]);
	}

	for (int i = 0; i != vecStr.size(); ++i){
		fout << vecStr[i].poiid << "\t" << vecStr[i].lat << "\t" << vecStr[i].lon << endl;
		if (vecStr[i].poiid == vecStr[i + 1].poiid){
			i = i + 1;
		}
	}

	/*for (vector<Data>::iterator iter = vecStr.begin(); iter != vecStr.end();){
	if ((*iter).poiid == (*iter+1).poiid)
	iter = vecStr.erase(iter);
	else
	++iter;
	}*/
	//写入
	/*for (vector<Data>::iterator it = vecStr.begin(); it != vecStr.end(); it++){
	fout << it->poiid << "\t" << it->lat << "\t" << it->lon << endl;
	}*/

	fin.close();
	fout.close();
}

int main(){
	getTest();
	return 0;
}
