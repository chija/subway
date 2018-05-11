#include<iostream>
#include<queue>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;
int record[10][330]; int loc_red = 0;
int check_station(string t, vector<string>station, int len)
{
	int i = -1;
	for (i = 0; i < len; i++)
		if (t == station[i])
			return i;
	return i;
}
void dfs(int *a, int *que, vector<string>name, vector<vector<int>>adjace, int len, int loc)
{
	int t = que[len];
	a[loc] = t;
	if (len == 0)
	{
		record[loc_red][0] = loc + 2;
		for (int i = 0; i <= loc; i++)
			record[loc_red][i + 1] = a[loc - i];
		loc_red++;
	}
	int i, j, k;
	for (i = len - 1; i >= 0; i--)
	{
		for (j = 0; j < adjace[t].size(); j++)
		{
			if (que[i] == adjace[t][j])
				dfs(a, que, name, adjace, i, loc + 1);
		}
	}
}
int bfs(vector<string>name, vector<vector<int>>adjace, int begin, int end)
{
	int i, j, k;
	int que[10000];
	int sign[330];
	memset(sign, 0, sizeof(sign));
	memset(que, 0, sizeof(que));
	int end_num = end;
	int head = 0, tail = 0;
	int flag = 1;
	que[tail++] = begin;
	while (tail > head)
	{
		for (i = 0; i < adjace[que[head]].size(); i++)
		{
			int t = adjace[que[head]][i];
			if (!sign[t])
			{
				que[tail++] = t;
				sign[t] = 1;
				if (t == end_num)
				{
					flag = 0;
					goto outloop;
				}
			}
		}
		head++;
	}
outloop:
	int a[330];
	if (!flag)
		dfs(a, que, name, adjace, tail - 1, 0);
	else return 0;
	return 1;
}
int main()
{
	int station_nums = 0;
	ifstream input;
	int i, j, k;
	int loc = -1;
	input.open("北京地铁.txt");
	vector<vector<string>>name(30);
	while (!input.eof())//读取信息
	{
		string t;
		input >> t;
		if (t.find("地铁") != string::npos)
			loc++;
		name[loc].push_back(t);
	}
	input.close();
	
	vector<vector<int>>adjace(330);
	vector<string>station_name;
	for (i = 0; i < loc; i++)//找到不同地名
	{
		for (j = 1; j < name[i].size(); j++)
		{
			string t = name[i][j];
			if (t == "*")
				continue;
			int flag = 1;
			int len = station_name.size();
			t = name[i][j];
			for (k = 0; k < len; k++)
			{
				if (t == station_name[k])
					flag = 0;
			}
			if (flag)
				station_name.push_back(t);
		}
	}
	/*for (i = 0; i < loc; i++)
	{
		cout << name[i].size() << endl;
	}*/
	int len_station_name = station_name.size();
	for (i = 0; i < loc; i++)//创建邻接表
	{
		//cout << name[i].size() << endl;
		for (j = 1; j < name[i].size(); j++)
		{
			string t = name[i][j];
			if (t == "*")
				continue;
			int location1 = check_station(t, station_name, len_station_name);
			if (j > 1)
				adjace[location1].push_back(check_station(name[i][j - 1], station_name, len_station_name));
			if (j < name[i].size() - 1)
				adjace[location1].push_back(check_station(name[i][j + 1], station_name, len_station_name));
			if (j == 1 && name[i][name[i].size() - 1] == "*")
				adjace[location1].push_back(check_station(name[i][name[i].size() - 1], station_name, len_station_name));
			if(j==name[i].size()-1&& name[i][name[i].size() - 1] == "*")
				adjace[location1].push_back(check_station(name[i][0], station_name, len_station_name));
		}
	}
	
	/*for (i = 0; i < adjace.size(); i++)
		cout << adjace[i].size() << station_name[i] << endl;*/
	


	/*for (i = 0; i < loc; i++)
	{
		for (j = 0; j < name[i].size(); j++)
		{
			if (name[i][j].find("公主坟") != string::npos)
				cout << name[i][0] << endl;
		}
	}*/

	string begin;
	string end;
	while (1)
	{
		cin >> begin >> end;
		int begin_num = check_station(begin, station_name, len_station_name);
		int end_num = check_station(end, station_name, len_station_name);
		if (begin == end)
		{
			cout << "1" << endl << begin << endl;
			continue;
		}
		if (begin_num == -1 || end_num == -1)
		{
			cout << "输入错误" << endl;
			continue;
		}
		loc_red = 0;
		if (bfs(station_name, adjace, begin_num, end_num))
		{
			for (i = 0; i < loc_red; i++)
			{
				int loc_a = record[i][0];//0保存的是该一维数组的下的数组个数
				cout << loc_a - 1 << endl;
				for (j = 1; j < loc_a; j++)
				{
					cout << station_name[record[i][j]];
					if (j >= 1 && j < loc_a - 1)
					{
						int t1 = record[i][j - 1];
						int t2 = record[i][j];
						int t3 = record[i][j + 1];
						int flag = 1;
						int t = 0;
						for (k = 0; k < loc; k++)
						{
							int flag1 = 1, flag2 = 1, flag3 = 1;
							for (int m = 1; m < name[k].size(); m++)
							{
								if (name[k][m] == station_name[t1])
									flag1 = 0;
								if (name[k][m] == station_name[t2])
									flag2 = 0;
								if (name[k][m] == station_name[t3])
									flag3 = 0;
							}
							if (flag1 == 0 && flag2 == 0 && flag3 == 1)
								flag = 0;
							else if (flag1 == 1 && flag2 == 0 && flag3 == 0)
								t = k;
							//cout << endl << flag1 << " " << flag2 << " " << flag3 << endl;
						}
						if (!flag)
							cout << " " << "换乘" << name[t][0];
					}
					cout << endl;
				}
				cout << endl;
			}
		}
		else { cout << "此路不通" << endl; }
	}
}
