#include<iostream>
#include<queue>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<stack>
using namespace std;
int record[10][330]; int loc_red = 0;
int check_station(string t, vector<string>station, int len)//查询每个地铁站在地铁名不同的位置
{
	int i = -1;
	for (i = 0; i < len; i++)
		if (t == station[i])
			return i;
	return -1;
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
	int i;
	for (i = len - 1; i >= 0; i--)
	{
		for (size_t j = 0; j < adjace[t].size(); j++)
		{
			if (que[i] == adjace[t][j])
				dfs(a, que, name, adjace, i, loc + 1);
		}
	}
}
int bfs(vector<string>name, vector<vector<int>>adjace, int begin, int end)
{
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
		for (size_t i = 0; i < adjace[que[head]].size(); i++)
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
	loc++;
	vector<vector<int>>adjace(330);//邻接表
	vector<string>station_name;//不同地名的索引
	for (i = 0; i < loc; i++)//找到不同地名
	{
		for (size_t j = 1; j < name[i].size(); j++)
		{
			/*string t = name[i][j];
			if (name[i][j] == "(" || name[i][j] == ")")//这个判断条件一加就编译不过？？？？？
			continue;
			else
			{
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
			}*/
			string t;
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
		int record_a, record_b, flag = 1;
		for (size_t j = 1; j < name[i].size(); j++)
		{
			string t = name[i][j];
			/*if (t == "*")
			continue;*/
			if (t == "(")
				record_a = j + 1;
			if (t == ")")
				flag = 0, record_b = j - 1;
			int location1 = check_station(t, station_name, len_station_name);
			if (j > 1)
			{
				if ((name[i][j - 1] == "(" || name[i][j - 1] == ")") && j > 2)
					adjace[location1].push_back(check_station(name[i][j - 2], station_name, len_station_name));
				else
					adjace[location1].push_back(check_station(name[i][j - 1], station_name, len_station_name));
			}
			if (j < name[i].size() - 1)
			{
				if (j < name[i].size() - 2 && (name[i][j + 1] == "(" || name[i][j + 1] == ")"))
					adjace[location1].push_back(check_station(name[i][j + 2], station_name, len_station_name));
				else
					adjace[location1].push_back(check_station(name[i][j + 1], station_name, len_station_name));
			}
			/*if (j == 1 && name[i][name[i].size() - 1] == "*")
			adjace[location1].push_back(check_station(name[i][name[i].size() - 1], station_name, len_station_name));
			if(j==name[i].size()-1&& name[i][name[i].size() - 1] == "*")
			adjace[location1].push_back(check_station(name[i][0], station_name, len_station_name));*/
			if (!flag)
			{
				int location_a = check_station(name[i][record_a], station_name, len_station_name);
				int location_b = check_station(name[i][record_b], station_name, len_station_name);
				adjace[location_a].push_back(location_b);
				adjace[location_b].push_back(location_a);
				flag = 1;
			}
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

	int  SearchNearestPath(string, string, vector<vector<int>>, vector<string>, vector<vector<string>>, int);
	void print(vector<vector<string>>, vector<string>, int, int);

	string begin;
	string end;

	while (0)
	{
		cin >> begin >> end;
		int t;
		t = SearchNearestPath(begin, end, adjace, station_name, name, loc);

		if (t == -1)
			continue;
		else
			print(name, station_name, loc, t);

	}

	bool StationSign[330];
	memset(StationSign, 0, sizeof(StationSign));
	string StationAround;
	cin >> StationAround;
	int sign_location = check_station(StationAround, station_name, len_station_name);
	int checkStationSign(bool *, int, vector<string>);
	vector<int>RoadTrack;
	stack<int>stk;
	int loop = 0;
	//遍历路径
	while (1)//贪心总是向未标记的节点靠近
	{
		//loop++;

		int _t = sign_location;
		RoadTrack.push_back(_t);
		stk.push(_t);
		StationSign[sign_location] = 1;
		int flag = 1;
		for (i = 0; i < adjace[sign_location].size(); i++)
		{
			j = adjace[sign_location][i];
			if (!StationSign[j])
			{
				flag = 0;
				StationSign[j] = 1;
				break;
			}
		}
		if (!flag)
			sign_location = j;
		else
		{
			if (!checkStationSign(StationSign, len_station_name, station_name))
				break;
			else
			{
				stk.pop();
				while (1)
				{
					int t = stk.top();
					int flag = 1;
					for (i = 0; i < adjace[t].size(); i++)
					{
						k = adjace[t][i];
						if (!StationSign[k])
						{
							StationSign[k] = 1;
							flag = 0;
							break;
						}
					}
					RoadTrack.push_back(t);
					if (!flag)
					{
						sign_location = k;
						break;
					}
					stk.pop();
				}
			}
		}
		//cout << loop << endl;
	}
	for (i = 0; i < RoadTrack.size(); i++)
		cout << station_name[RoadTrack[i]] << endl;
}
int checkStationSign(bool *StationSign, int len, vector<string>station)
{
	for (int i = 0; i < len; i++)
		if (StationSign[i] == 0 && station[i] != "石厂"&&station[i] != "小园"&&station[i] != "栗园庄"&&station[i] != "上岸"
			&&station[i] != "桥户营"&&station[i] != "四道桥"&&station[i] != "金安桥")
			return 1;
	return 0;
}
int SearchNearestPath(string begin, string end, vector<vector<int>> adjace, vector<string> station_name, vector<vector<string>>name,
	int loc)
{
	int len_station_name = station_name.size();
	int i, j, k;
	int begin_num = check_station(begin, station_name, len_station_name);
	int end_num = check_station(end, station_name, len_station_name);
	if (begin == end)
	{
		cout << "1" << endl << begin << endl;
		return -1;
	}
	if (begin_num == -1 || end_num == -1)
	{
		cout << "输入错误" << endl;
		return -1;
	}
	loc_red = 0;//搜到符合路的条数
	if (bfs(station_name, adjace, begin_num, end_num))
	{
		int hc_num[330];
		memset(hc_num, 0, sizeof(hc_num));
		for (i = 0; i < loc_red; i++)//在符合的路中整理信息，便于下面程序输出
		{
			int loc_a = record[i][0];//0保存的是该一维数组的下的数组个数
									 //cout << loc_a - 1 << endl;

			for (j = 1; j < loc_a; j++)
			{
				//cout << station_name[record[i][j]];
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
						for (size_t m = 1; m < name[k].size(); m++)
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
						hc_num[i]++;//cout << " " << "换乘" << name[t][0];
				}
				//cout << endl;
			}
			//cout << endl;
		}
		int min_m = 99999999, min_num = 999999999;
		int red_i;
		for (i = 0; i < loc_red; i++)//筛选出路径最小的
		{
			if (min_num > record[i][0])
				min_num = record[i][0];
		}
		for (i = 0; i < loc_red; i++)//筛选出换乘最少的
		{
			if (min_m > hc_num[i] && record[i][0] <= min_num)
			{
				red_i = i;
				min_m = hc_num[i];
			}
		}
		return red_i;
	}
	else { cout << "此路不通" << endl; return -1; }
}
void print(vector<vector<string>>name, vector<string>station_name, int loc, int red_i)
{
	int j, k;
	cout << record[red_i][0] - 1 << endl;//record[][0]第一个数字不包含其中故减一
	for (j = 1; j < record[red_i][0]; j++)//找到并输出
	{
		cout << station_name[record[red_i][j]];
		if (j >= 1 && j < record[red_i][0] - 1)
		{
			int t1 = record[red_i][j - 1];
			int t2 = record[red_i][j];
			int t3 = record[red_i][j + 1];
			int flag = 1;
			int t = 0;
			for (k = 0; k < loc; k++)
			{
				int flag1 = 1, flag2 = 1, flag3 = 1;
				for (size_t m = 1; m < name[k].size(); m++)
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
}
