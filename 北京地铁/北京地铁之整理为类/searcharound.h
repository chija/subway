#pragma once
#include<string>
#include<vector>
#include<cstdlib>
#include<string.h>
#include<iostream>
#include<stack>
using namespace std;

class searcharound
{
public:
	searcharound();
	~searcharound();
	bool StationSign[330];
	void search(string, vector<vector<int>>adjace, vector<string>station_name);
private:
	int checkStationSign(bool *, int, vector<string>);
	int check_station(string t, vector<string>station, int len);//��ѯÿ������վ�ڵ�������ͬ��λ��
};