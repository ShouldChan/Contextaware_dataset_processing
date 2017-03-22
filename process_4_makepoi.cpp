//4：提取poi
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

#define ifilename "E:\\train7_t+d.txt"
#define poiidlatlon "E:\\context_t+d\\poi_t+d.txt"

struct POI{
	string lat; string lon;
};

void getPOI(){
	ifstream fin(ifilename);
	ofstream fout(poiidlatlon);
	if (!fin){
		cout << "error!" << endl;
		exit(1);
	}
	//一路将行记录存入vector
	vector<POI> vecPOI;
	string s;
	multimap<int, POI> mappoi;
	multimap<int, POI>::iterator itpoi1;
	multimap<int, POI>::iterator itpoi2;
	while (!fin.eof()){
		int pid1, pid2;
		string str[15];
		fin >> str[0] >> pid1 >> str[1] >> str[2] >> str[3] >> str[4] >> str[5] >> str[6] >> str[7] >> pid2 >> str[8] >> str[9] >> str[10] >> str[11] >> str[12] >> str[13] >> str[14];
		getline(fin, s);
		itpoi1 = mappoi.find(pid1);
		itpoi2 = mappoi.find(pid2);
		POI p1, p2;
		p1.lat = str[1]; p1.lon = str[2];
		p2.lat = str[8]; p2.lon = str[9];
		if (itpoi1 != mappoi.end()){}//找到元素 就无需插入
		else{
			//未找到元素 就插入map
			mappoi.insert(pair<int, POI>(pid1, p1));
		}
		if (itpoi2 != mappoi.end()){}//找到元素 就无需插入
		else{
			//未找到元素 就插入map
			mappoi.insert(pair<int, POI>(pid2, p2));
		}
	}
	map<int, POI>::iterator it;
	for (it = mappoi.begin(); it != mappoi.end(); it++){
		fout << it->first << "\t" << it->second.lat << "\t" << it->second.lon << endl;
	}

	fin.close();
	fout.close();
}
int main(){
	getPOI();
	return 0;
}