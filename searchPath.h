#pragma once
#include<vector>
#include<string>
#include<iostream>
using namespace std;
class searchPath
{
	
public:
	searchPath();
	~searchPath();
	int  SearchNearestPath(string, string, vector<vector<int>>, vector<string>, vector<vector<string>>, int);
	void print(vector<vector<string>>, vector<string>, int, int);
	int record[10][330], loc_red;
private:
	int check_station(string t, vector<string>station, int len);//��ѯÿ������վ�ڵ�������ͬ��λ��
	int bfs(vector<string>name, vector<vector<int>>adjace, int begin, int end);
	void dfs(int *a, int *que, vector<string>name, vector<vector<int>>adjace, int len, int loc);
};

