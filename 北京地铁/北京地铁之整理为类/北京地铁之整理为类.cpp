#include"searchPath.h"
#include"searcharound.h"
#include<fstream>
using namespace std;
int loc = -1;
vector<vector<string>>name(30);
vector<string>station_name;
vector<vector<int>>adjace(330);
int check_station(string t, vector<string>station, int len)
{
	int i = -1;
	for (i = 0; i < len; i++)
		if (t == station[i])
			return i;
	cout << "wrong" << endl;
	return -1;
}
void readinText()
{
	ifstream input;
	input.open("北京地铁.txt");
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
}
void finddiffername()
{
	int i, j, k;
	for (i = 0; i < loc; i++)//找到不同地名
	{
		for (size_t j = 1; j < name[i].size(); j++)
		{
			string t = name[i][j];
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
					{
						flag = 0;
						break;
					}
				}
				if (flag)
					station_name.push_back(t);
			}
		}
	}
}
void creatadjace()
{
	int i, j, k;
	int len_station_name = station_name.size();
	for (i = 0; i < loc; i++)//创建邻接表
	{
		//cout << name[i].size() << endl;
		int record_a, record_b, flag = 1;
		for (size_t j = 1; j < name[i].size(); j++)
		{
			string t = name[i][j];
			if (t == "(")
			{
				record_a = j + 1;
				continue;
			}
			if (t == ")")
			{
				flag = 0, record_b = j - 1;
				continue;
			}
			int location1 = check_station(t, station_name, len_station_name);
			if (j > 1)
			{
				if ((name[i][j - 1] == "(" || name[i][j - 1] == ")") && j > 2)
					adjace[location1].push_back(check_station(name[i][j - 2], station_name, len_station_name));
				else if (name[i][j - 1] != "(" && name[i][j - 1] != ")")
					adjace[location1].push_back(check_station(name[i][j - 1], station_name, len_station_name));
			}
			if (j < name[i].size() - 1)
			{
				if (j < name[i].size() - 2 && (name[i][j + 1] == "(" || name[i][j + 1] == ")"))
					adjace[location1].push_back(check_station(name[i][j + 2], station_name, len_station_name));
				else if (name[i][j + 1] != "(" && name[i][j + 1] != ")")
					adjace[location1].push_back(check_station(name[i][j + 1], station_name, len_station_name));
			}
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
}



int main()
{
	readinText();
	finddiffername();
	creatadjace();
	string begin;
	string end;
	while (1)
	{
		string t;
		cin >> t;
		if (t == "/b")
		{
			cin >> begin >> end;
			int t;
			searchPath search;
			t = search.SearchNearestPath(begin, end, adjace, station_name, name, loc);
			if (t == -1)
				continue;
			else
				search.print(name, station_name, loc, t);
		}
		else if(t=="/a")
		{
			string around;
			cin >> around;
			searcharound c;
			c.search(around, adjace, station_name);
		}
	}
}

