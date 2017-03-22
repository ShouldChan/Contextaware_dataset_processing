//2:筛选nextpoi	并对poi进行重新编号
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
using namespace std;

#define ifilename "E:\\TKY_train5_timeofday.txt"
#define ofilename "E:\\TKY_train6_timeofday.txt"
#define ofilename2 "E:\\TKY_train7_timeofday.txt"
#define poiname "E:\\TKY_poimap_timeofday.txt"

//自定义结构体，用于存储每行数据
struct Data{
	int userid;
	string poiid;
	string lat;
	string lon;
	string date;
	string time;
	int zzw;
	int week;
	int category;
};

//自定义的vector的pushback函数
void myPushback(vector<Data> & vecData, const int &uid, const string &pid, const string &la, const string &lo,
	const string &da, const string &ti, const int& z, const int &we, const int &cat){
	Data data;
	data.userid = uid; data.poiid = pid; data.lat = la; data.lon = lo;
	data.date = da; data.time = ti; 	data.zzw = z; data.week = we; data.category = cat;
	vecData.push_back(data);
}
void selectNextpoi(){
	ifstream fin(ifilename);
	ofstream fout(ofilename);
	if (!fin){
		cout << "error!" << endl;
		exit(1);
	}
	//一路将行记录存入vector
	vector<Data> vecStr;
	string s;
	while (!fin.eof()){
		int uid, zzw, week, cate;
		string str[5];
		fin >> uid >> str[0] >> str[1] >> str[2] >> str[3] >> str[4] >> zzw >> week >> cate;
		getline(fin, s);
		myPushback(vecStr, uid, str[0], str[1], str[2], str[3], str[4], zzw, week, cate);
	}
	cout << "vecStr ok..." << endl;
	//遍历vector来筛选nextpoi  将连续的两行记录作为nextpoi即可
	for (int i = 0; i != vecStr.size(); ++i){
		if (vecStr[i].userid == vecStr[i + 1].userid){
			fout << vecStr[i].userid << "\t" << vecStr[i].poiid << "\t" << vecStr[i].lat << "\t" << vecStr[i].lon << "\t" << vecStr[i].date << " "
				<< vecStr[i].time << "\t" << vecStr[i].zzw << "\t" << vecStr[i].week << "\t" << vecStr[i].category << "\t"
				<< vecStr[i + 1].poiid << "\t" << vecStr[i + 1].lat << "\t" << vecStr[i + 1].lon << "\t" << vecStr[i + 1].date
				<< " " << vecStr[i + 1].time << "\t" << vecStr[i + 1].zzw << "\t" << vecStr[i + 1].week << "\t" << vecStr[i + 1].category << endl;
		}
	}
	fin.close();
	fout.close();
}

//5：对poi重新编号
void reNumpoi(){
	ifstream fin(ofilename);
	ofstream fout(ofilename2);
	if (!fin){
		cout << "error!" << endl;
		exit(1);
	}
	map<string, int> mappoi;
	map<string, int>::iterator itpoi1;
	map<string, int>::iterator itpoi2;
	string s;
	int count = 0;
	while (!fin.eof()){
		string str[17];
		fin >> str[0] >> str[1] >> str[2] >> str[3] >> str[4] >> str[5] >> str[6] >> str[7] >> str[8] >> str[9] >> str[10] >> str[11] >> str[12] >> str[13] >> str[14] >> str[15] >> str[16];
		getline(fin, s);
		itpoi1 = mappoi.find(str[1]);
		itpoi2 = mappoi.find(str[9]);
		if (itpoi1 != mappoi.end()){}//找到元素 就无需插入
		else{
			//未找到元素 就插入map
			mappoi.insert(pair<string, int>(str[1], ++count));
		}
		if (itpoi2 != mappoi.end()){}//找到元素 就无需插入
		else{
			//未找到元素 就插入map
			mappoi.insert(pair<string, int>(str[9], ++count));
		}
	}
	fin.close();
	ofstream outpoi(poiname);
	map<string, int>::iterator it;
	for (it = mappoi.begin(); it != mappoi.end(); it++){
		outpoi << it->first << "\t" << it->second << endl;
	}
	outpoi << "poiNum:" << count << endl;
	//再次读取文件修改poi序号
	fin.open(ofilename);
	while (!fin.eof()){
		string str[17];
		fin >> str[0] >> str[1] >> str[2] >> str[3] >> str[4] >> str[5] >> str[6] >> str[7] >> str[8] >> str[9] >> str[10] >> str[11] >> str[12] >> str[13] >> str[14] >> str[15] >> str[16];
		getline(fin, s);
		fout << str[0] << "\t" << mappoi[str[1]] << "\t" << str[2] << "\t" << str[3] << "\t" << str[4] << " " << str[5] << "\t" <<
			str[6] << "\t" << str[7] << "\t" << str[8] << "\t" << mappoi[str[9]] << "\t" << str[10] << "\t" << str[11] << "\t" << str[12] <<
			" " << str[13] << "\t" << str[14] << "\t" << str[15] << "\t" << str[16] << endl;
	}
	fin.close();
	fout.close();
	outpoi.close();
}
int main(){
	selectNextpoi();
	//reNumpoi();

	return 0;
}