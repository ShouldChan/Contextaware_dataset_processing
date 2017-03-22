//3�������ȡ���ݼ�����м�¼��Ϊ���Լ�
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

#define Randmod(x) rand()%x
#define ifilename "E:\\train7_timeofday.txt"
#define ofilename "E:\\train8_timeofday.txt"
#define ofilename2 "E:\\test_timeofday.txt"

//�Զ���ṹ�壬���ڴ洢ÿ������
struct Data{
	int userid; int poiid; string lat; string lon; string date;//4
	string time; int zzw; int week; int category;//4
	int npoiid; string nlat; string nlon; string ndate;//4
	string ntime; int nzzw; int nweek; int ncategory;//4
	bool is_test;
};

//�Զ����vector��pushback����
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

bool sortBy(const int &s1, const int &s2){
	return s1 < s2;
}
//ʹ����4��ʦд��ϴ���㷨��������� ��ΪҪ��ȡ���������Ϊtest��
vector<int> storeRand;
void createRand(int n, int m) {
	int *d;
	int  i, a, b, t;
	srand(time(NULL));
	d = (int *)malloc((n + 1)*sizeof(int));

	for (i = 0; i <= n; i++) d[i] = i;/* ��д0��n */
	for (i = n + 1; i > 0; i--) {/* ����0��n */
		a = i - 1; b = rand() % i;
		if (a != b) { t = d[a]; d[a] = d[b]; d[b] = t; }
	}
	for (i = 0; i < m; i++){
		//printf("%2d ", d[i]);
		storeRand.push_back(d[i]);
	}
	sort(storeRand.begin(), storeRand.end());
	free(d);
}
void getTest(){
	ifstream fin(ifilename);
	ofstream fout(ofilename);
	ofstream ffout(ofilename2);
	if (!fin){
		cout << "error!" << endl;
		exit(1);
	}
	//һ·���м�¼����vector
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
	createRand(vecStr.size(), 56343);
	vector<Data> vecTest;
	for (int i = 0; i != storeRand.size(); ++i){
		//cout << storeRand[i] << endl;
		vecTest.push_back(vecStr[storeRand[i]]);
		vecStr[storeRand[i]].is_test = 1;
		//Data d = vecStr[storeRand[i]];
		//vector<Data>::iterator it = find(vecStr.begin(), vecStr.end(), d);
		//vector<Data>::iterator it = vecStr[storeRand[i]];
		//vecStr.erase(it);
	}

	cout << "set test ok..." << endl;
	for (vector<Data>::iterator iter = vecStr.begin(); iter != vecStr.end();){
		if (1 == (*iter).is_test)
			iter = vecStr.erase(iter);
		else
			++iter;
	}
	//д��
	for (vector<Data>::iterator it = vecStr.begin(); it != vecStr.end(); it++){
		fout << it->userid << "\t" << it->poiid << "\t" << it->lat << "\t" << it->lon << "\t" << it->date << " " << it->time << "\t"
			<< it->zzw << "\t" << it->week << "\t" << it->category << "\t" << it->npoiid << "\t" << it->nlat << "\t" << it->nlon << "\t"
			<< it->ndate << " " << it->ntime << "\t" << it->nzzw << "\t" << it->nweek << "\t" << it->ncategory << endl;
	}
	for (vector<Data>::iterator it = vecTest.begin(); it != vecTest.end(); it++){
		ffout << it->userid << "\t" << it->poiid << "\t" << it->lat << "\t" << it->lon << "\t" << it->date << " " << it->time << "\t"
			<< it->zzw << "\t" << it->week << "\t" << it->category << "\t" << it->npoiid << "\t" << it->nlat << "\t" << it->nlon << "\t"
			<< it->ndate << " " << it->ntime << "\t" << it->nzzw << "\t" << it->nweek << "\t" << it->ncategory << endl;
	}
	cout << "write ok..." << endl;
	fin.close();
	fout.close();
	ffout.close();
}

int main(){
	getTest();
	return 0;
}