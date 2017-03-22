//1：按用户的时间排序
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
using namespace std;

#define ifilename "E:\\train4_1.txt"
#define ofilename "E:\\train5.txt"

time_t StringToDatetime(char *str)
{
	tm tm_;
	int year, month, day, hour, minute, second;
	sscanf(str, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	tm_.tm_year = year - 1900;
	tm_.tm_mon = month - 1;
	tm_.tm_mday = day;
	tm_.tm_hour = hour;
	tm_.tm_min = minute;
	tm_.tm_sec = second;
	tm_.tm_isdst = 0;

	time_t t_ = mktime(&tm_); //已经减了8个时区  
	return t_; //秒时间  
}
int calTime(string s1){
	tm tm_1;
	time_t t1;
	char buf[128] = { 0 };
	const char *temp1 = s1.data();
	strcpy(buf, temp1);
	t1 = StringToDatetime(buf);
	int result = t1 / 3600;
	return result;
}
//自定义结构体，用于存储每行数据
struct Data{
	int userid;	string poiid;	string lat;
	string lon;	string date;		string time;
	int zzw;		int weekday;	int category;
};
typedef pair<int, Data> PAIR;

bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {

	if (lhs.first == rhs.first){
		if (lhs.second.weekday == rhs.second.weekday){
			return calTime(lhs.second.date + " " + lhs.second.time) < calTime(rhs.second.date + " " + rhs.second.time);
		}
		else
			return lhs.second.weekday < rhs.second.weekday;
	}
	else return lhs.first < rhs.first;

}

//定义的vector的pushback函数
Data getData_value(const int &uid, const string &pid, const string &la, const string &lo,
	const string &da, const string &ti, const int& zz, const int &we, const int &cat){
	Data data;
	data.userid = uid; data.poiid = pid; data.lat = la; data.lon = lo;
	data.date = da; data.time = ti; data.zzw = zz; data.weekday = we; data.category = cat;
	return data;
}

//按用户userid重新排序
void reSeat(){
	ifstream fin(ifilename);
	ofstream fout(ofilename);
	if (!fin.good()){
		cerr << "wrong open!" << endl;
		exit(1);
	}
	//vector<Data> vecStr;
	multimap<int, Data, greater<int>>a;
	string s;
	int i = 0;
	while (!fin.eof()){
		int uid, zzw, weekday, category;
		string str[5];
		fin >> uid >> str[0] >> str[1] >> str[2] >> str[3] >> str[4] >> zzw >> weekday >> category;
		getline(fin, s);
		Data d = getData_value(uid, str[0], str[1], str[2], str[3], str[4], zzw, weekday, category);
		a.insert(make_pair(d.userid, d));
	}

	//根据单个用户的早中晚分组或工作日周末分组组内按时间先后进行排序
	vector<PAIR> name_score_vec(a.begin(), a.end());
	sort(name_score_vec.begin(), name_score_vec.end(), cmp_by_value);
	for (int i = 0; i != name_score_vec.size(); ++i) {
		fout << name_score_vec[i].first << "\t" << name_score_vec[i].second.poiid << "\t" << name_score_vec[i].second.lat <<
			"\t" << name_score_vec[i].second.lon << "\t" << name_score_vec[i].second.date << " " << name_score_vec[i].second.time << "\t"
			<< name_score_vec[i].second.zzw << "\t" << name_score_vec[i].second.weekday << "\t" << name_score_vec[i].second.category << endl;
	}

	fin.close();
	fout.close();
}

int main(){
	reSeat();
	return 0;
}