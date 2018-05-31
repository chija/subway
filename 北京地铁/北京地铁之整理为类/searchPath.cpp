#include "searchPath.h"

using namespace std;


searchPath::searchPath()
{
}


searchPath::~searchPath()
{
}
int searchPath::SearchNearestPath(string begin, string end, vector<vector<int>> adjace, vector<string> station_name, vector<vector<string>>name,
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
void searchPath::print(vector<vector<string>>name, vector<string>station_name, int loc, int red_i)
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
int searchPath::check_station(string t, vector<string>station, int len)//查询每个地铁站在地铁名不同的位置
{
	int i = -1;
	for (i = 0; i < len; i++)
		if (t == station[i])
			return i;
	cout << "wrong" << endl;
	return -1;
}
int searchPath::bfs(vector<string>name, vector<vector<int>>adjace, int begin, int end)
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
void searchPath::dfs(int *a, int *que, vector<string>name, vector<vector<int>>adjace, int len, int num)
{
	int t = que[len];
	a[num] = t;
	if (len == 0)
	{
		record[loc_red][0] =num + 2;
		for (int i = 0; i <=num; i++)
			record[loc_red][i + 1] = a[num - i];
		loc_red++;
	}
	int i;
	for (i = len - 1; i >= 0; i--)
	{
		for (size_t j = 0; j < adjace[t].size(); j++)
		{
			if (que[i] == adjace[t][j])
				dfs(a, que, name, adjace, i, num + 1);
		}
	}
}