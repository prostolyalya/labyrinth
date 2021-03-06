#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using std::vector;
using namespace std;

int main()
{
	char o;
	int s=0,s1=0, sx, sy, fx, fy;
	int q, qe,z;
	string nameFile;
	bool wall, ex = false;
	cout << "what name your file?('labyrinth.txt') -> ";
	cin >> nameFile;
	ifstream file(nameFile);
	ofstream fout;
	std::string line;
	if (!file.is_open())
	{
		cout << "don't open file!" << endl;
		system("pause");
		return -1;
	}
	vector<vector<char>> mass;
	for (int i = 0; getline(file, line); i++)
	{
		mass.push_back(vector<char>());
		for (int j = 0; j < line.size(); j++)
		{
			mass[i].push_back(line[j]);
			s++;
		}
		if (s != s1 && i!=0)
		{
			cout << "labyrinth not rectangular!" << endl;
			system("pause");
			return -1;
		}
		s1 = s;
		s = 0;

	}
	s = line.size();
	cout << endl << "your labirint-> " << endl;
	z = 0;
	for (int i = 0; i < mass.size(); i++)
	{
		for (int j = 0; j < s; j++)
		{
			cout << mass[i][j];
			if (mass[i][j] == 'I')
			{
				sx = i;
				sy = j;
				mass[i][j] = '1';
				z++;
			}
			else if (mass[i][j] == 'E')
			{
				fx = i;
				fy = j;
				mass[i][j] = '9';
				z++;
			}
			else if (mass[i][j] == ' ')
				mass[i][j] = '2';
			else if (mass[i][j] == '0')
				;
			else
			{
				cout << endl << "unknown characters!" << endl;
				system("pause");
				return -1;
			}

		}
		cout << endl;
	}
	if (z!=2)
	{
		cout << endl << "incorrect entry or exit!" << endl;
		system("pause");
		return -1;
	}

	// WALL

	for (int i = 0; i < mass.size(); i++)
	{
		for (int j = 0; j < s; j++)
		{
			if (i == 0 || i == mass.size() - 1)
			{
				if (mass[i][j] == '0') wall = true;
				else wall = false;
			}
			else if (mass[i][0] == '0' && mass[i][s - 1] == '0')
			{
				wall = true;
			}
			else
			{
				wall = false;
				i = mass.size();
				break;
			}
		}
	}
	if (wall == false)
	{
		vector<vector<char>> massive;
		for (int i = 0; i < mass.size() + 2; i++)
		{
			massive.push_back(vector<char>());
			for (int j = 0; j < s + 2; j++)
			{
				if (i > 0 && j > 0 && i < mass.size() + 1 && j <s + 1)
				{
					massive[i].push_back(mass[i - 1][j - 1]);
				}
				else massive[i].push_back('0');
			}
		}
		mass = massive;
		s = s + 2;
		for (int i = 0; i < mass.size(); i++)
		{
			for (int j = 0; j < s; j++)
			{
				if (mass[i][j] == '1')
				{
					sx = i;
					sy = j;
				}
				else if (mass[i][j] == '9')
				{
					fx = i;
					fy = j;
				}
			}
		}
	}
	cout << endl;
	// LAB
	vector < vector <int>> massive;
	for (int i = 0; i < mass.size(); i++)
	{
		massive.push_back(vector<int>());
		for (int j = 0; j < s; j++)
		{
			massive[i].push_back(mass[i][j] - '0');
			if (massive[i][j] == 2) massive[i][j] = -2;
			if (massive[i][j] == 9) 
				massive[i][j] = -1;
		}
	}

	q = 1;
	while (!ex)
	{
		if (massive[fx][fy] == q)
		{
			qe = q - 1;
			ex = true;
			break;
		}
		z = 0;
		for (int i = 1; i < massive.size() - 1; i++)
		{
			for (int j = 1; j < s - 1; j++)
			{
				if (massive[i][j] == q)
				{
					if (massive[i][j + 1] == -2 || massive[i][j + 1] == -1)
					{
						massive[i][j + 1] = q + 1;
						z++;
					}
					if (massive[i][j - 1] == -2 || massive[i][j - 1] == -1)
					{
						massive[i][j - 1] = q + 1;
						z++;
					}
					if (massive[i + 1][j] == -2 || massive[i + 1][j] == -1)
					{
						massive[i + 1][j] = q + 1;
						z++;
					}
					if (massive[i - 1][j] == -2 || massive[i - 1][j] == -1)
					{
						massive[i - 1][j] = q + 1;
						z++;
					}
				}
			}
		}
		if (z>0) q++;
		else
		{
			cout << "the labyrinth does not have a way out!" << endl;
			system("pause");
			return -1;
		}
	}
	ex = false;
	// EXIT
	while (!ex)
	{
		for (int i = 0; i < massive.size(); i++)
		{
			for (int j = 0; j < s; j++)
			{
				if (massive[i][j] == q)
				{
					if (q == 1)
					{
						ex = true;
						i = massive.size();
						break;
					}
					if (q == qe + 1)
					{
						mass[i][j] == '+';
					}
					if (massive[i][j + 1] == q - 1)
					{
						mass[i][j + 1] = '+';
						q--;
					}
					else if (massive[i][j - 1] == q - 1)
					{
						mass[i][j - 1] = '+';
						j -= 2;
						q--;
					}
					else if (massive[i + 1][j] == q - 1)
					{
						mass[i + 1][j] = '+';
						i++;
						j--;
						q--;
					}
					else if (massive[i - 1][j] == q - 1)
					{
						mass[i - 1][j] = '+';
						i--;
						j--;
						q--;
					}
				}
			}
		}
	}
	fout.open("exit.txt");
	fout << "congratulations, step on road -> " << qe << endl;
	cout << endl << "congratulations, step on road -> " << qe << endl;
	mass[sx][sy] = 'I';
	for (int i = 0; i < mass.size(); i++)
	{
		for (int j = 0; j < s; j++)
		{
			if (mass[i][j] == '2')
				mass[i][j] = ' ';
			if (mass[i][j] == '9')
				mass[i][j] = 'E';
			cout << mass[i][j];
			fout << mass[i][j];
		}
		cout << endl;
		fout << endl;
	}
	cout << endl << "you want look all road?(y/n)-> ";
	cin >> o;
	massive[fx][fy] = -1;
	if (o == 'y')
	{
		cout << endl << "1 start, -1 finish, -2 space, 0 wall, 2 3 4 ... roads." << endl;
		for (int i = 0; i < massive.size(); i++)
		{
			for (int j = 0; j < s; j++)
			{
				cout << setw(3) << massive[i][j];
			}
			cout << endl;
		}

	}
	o = 'n';
	cout << endl << "you want output in file all road?(y/n)-> ";
	cin >> o;
	if (o == 'y')
	{
		fout << endl << "1 start, -1 finish, -2 space, 0 wall, 2 3 4 ... roads." << endl;
		for (int i = 0; i < massive.size(); i++)
		{
			for (int j = 0; j < s; j++)
			{
				fout << setw(3) << massive[i][j];
			}
			fout << endl;
		}
	}
	file.close();
	fout.close();
	return 0;
}