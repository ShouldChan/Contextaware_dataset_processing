//3：获取每个用户的后30%的记录 作为测试集
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

#define ifilename "E:\\train_fused.txt"
#define test "E:\\test.txt"
#define train "E:\\train.txt"

//自定义结构体，用于存储每行数据
struct Data{
	int userid; int poiid; string lat; string lon; string date;//5
	string time; int zzw; int week; int category;//4
	int npoiid; string nlat; string nlon; string ndate;//4
	string ntime; int nzzw; int nweek; int ncategory;//4
	bool is_test;
};

//自定义结构体用于记录每个用户的checkin个数，以便用于随机函数的调用
struct Usercount{
	int uid;
	int ucount;
};

//自定义的vector的pushback函数
void myPushback(vector<Data> & vecData, const int &uid, const int &pid, const string &la,
	const string &lo, const string &da, const string &ti, const int &z, const int& we, const int& cate,
	const int &npid, const string &nla, const string &nlo, const string &nda, const string &nti,
	const int& nz, const int& nwe, const int&ncate, const bool &istest){
	Data data;
	data.userid = uid; data.poiid = pid; data.lat = la; data.lon = lo; data.date = da; data.time = ti;//6
	data.zzw = z; data.week = we; data.category = cate;//3
	data.npoiid = npid; data.nlat = nla; data.nlon = nlo; data.ndate = nda; data.ntime = nti; //5
	data.nzzw = nz; data.nweek = nwe; data.ncategory = ncate;//3
	data.is_test = istest;
	vecData.push_back(data);
}
void countPushback(vector<Usercount>& vecUc, const int& uid, const int& ucount){
	Usercount userc;
	userc.uid = uid;		userc.ucount = ucount;
	vecUc.push_back(userc);
}

bool sortBy(const int &s1, const int &s2){
	return s1 < s2;
}

void getTest(){
	ifstream fin(ifilename);
	ofstream testout(test);
	ofstream trainout(train);
	if (!fin){
		cout << "error!" << endl;
		exit(1);
	}
	//一路将行记录存入vector
	vector<Data> vecStr;
	string s;
	while (!fin.eof()){
		int uid, pid, zzw, week, cate, npid, nzzw, nweek, ncate;
		string str[8];
		fin >> uid >> pid >> str[0] >> str[1] >> str[2] >> str[3] >> zzw >> week >> cate >> npid >> str[4] >> str[5] >> str[6] >> str[7] >> nzzw >> nweek >> ncate;
		getline(fin, s);
		myPushback(vecStr, uid, pid, str[0], str[1], str[2], str[3], zzw, week, cate, npid, str[4], str[5], str[6], str[7], nzzw, nweek, ncate, 0);
	}
	cout << "pushback ok..." << endl;

	//统计遍历vecStr计算每用户的checkin个数
	int count = 1, j = 0;
	vector<Usercount> vecucount;
	for (int i = 0; i < vecStr.size() - 1; ++i){
		if (vecStr[i].userid == vecStr[i + 1].userid){
			//cout << "* ";
			++count;
		}
		else{
			countPushback(vecucount, vecStr[i].userid, count);
			++j;
			count = 0;
		}
	}
	countPushback(vecucount, 1083, 275);//唉 以后再优化吧1083	275
	cout << "each user checkin nums save ok...." << endl;
	//抽取test集
	vector<Data> vecTest;
	int N = 0.7*vecucount[0].ucount;
	int M = vecucount[0].ucount;
	int jj = 0;
	for (int i = 0; i < vecStr.size() - 1; ++i){
		if (i >= N&&i <= M){
			vecStr[i].is_test = 1;
		}
		if (vecStr[i].userid != vecStr[i + 1].userid){
			N = i + 1 + 0.7*vecucount[++jj].ucount;
			M = i + 1 + vecucount[jj].ucount;
		}
	}
	cout << "set test ok..." << endl;
	//若发现被标记为是test的记录则放入vecTest
	for (int i = 0; i != vecStr.size(); i++){
		if (vecStr[i].is_test == 1){
			vecTest.push_back(vecStr[i]);
		}
	}
	for (vector<Data>::iterator iter = vecStr.begin(); iter != vecStr.end();){
		if (1 == (*iter).is_test)
			iter = vecStr.erase(iter);
		else
			++iter;
	}
	//写入
	for (vector<Data>::iterator it = vecStr.begin(); it != vecStr.end(); it++){
		trainout << it->userid << "\t" << it->poiid << "\t" << it->lat << "\t" << it->lon << "\t" << it->date << " " << it->time << "\t"
			<< it->zzw << "\t" << it->week << "\t" << it->category << "\t" << it->npoiid << "\t" << it->nlat << "\t" << it->nlon << "\t"
			<< it->ndate << " " << it->ntime << "\t" << it->nzzw << "\t" << it->nweek << "\t" << it->ncategory << endl;
	}
	for (vector<Data>::iterator it = vecTest.begin(); it != vecTest.end(); it++){
		testout << it->userid << "\t" << it->poiid << "\t" << it->lat << "\t" << it->lon << "\t" << it->date << " " << it->time << "\t"
			<< it->zzw << "\t" << it->week << "\t" << it->category << "\t" << it->npoiid << "\t" << it->nlat << "\t" << it->nlon << "\t"
			<< it->ndate << " " << it->ntime << "\t" << it->nzzw << "\t" << it->nweek << "\t" << it->ncategory << endl;
	}

	fin.close();
	trainout.close();
	testout.close();
}

int main(){
	getTest();
	return 0;
}