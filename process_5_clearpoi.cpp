//5:ȥ��poi����Դ���ݼ�ԭ����ظ��Ͳ����ڵı��
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

//�Զ���ṹ�壬���ڴ洢ÿ������
struct Data{
	int poiid; string lat; string lon;
};

//�Զ����vector��pushback����
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
	//һ·���м�¼����vector
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
	//д��
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
