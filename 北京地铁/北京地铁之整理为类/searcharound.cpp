#include "searcharound.h"

using namespace std;

searcharound::searcharound()
{
}


searcharound::~searcharound()
{
}

void searcharound::search(string StationAround, vector<vector<int>>adjace, vector<string>station_name)
{
	int i, j, k;
	memset(StationSign, 0, sizeof(StationSign));
	int len_station_name = station_name.size();
	int sign_location = check_station(StationAround, station_name, len_station_name);
	vector<int>RoadTrack;
	stack<int>stk;
	int loop = 0;
	//����·��
	while (1)//̰��������δ��ǵĽڵ㿿��
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
	cout << RoadTrack.size() << endl;
	for (i = 0; i < RoadTrack.size(); i++)
		cout << station_name[RoadTrack[i]] << endl;
}
int searcharound::checkStationSign(bool *StationSign, int len, vector<string>station)
{
	for (int i = 0; i < len; i++)
		if (StationSign[i] == 0 && station[i] != "ʯ��"&&station[i] != "С԰"&&station[i] != "��԰ׯ"&&station[i] != "�ϰ�"
			&&station[i] != "�Ż�Ӫ"&&station[i] != "�ĵ���"&&station[i] != "����")
			return 1;
	return 0;
}
int searcharound::check_station(string t, vector<string>station, int len)//��ѯÿ������վ�ڵ�������ͬ��λ��
{
	int i = -1;
	for (i = 0; i < len; i++)
		if (t == station[i])
			return i;
	cout << "wrong" << endl;
	return -1;
}