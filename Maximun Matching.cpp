/*code review 2017/11/29
important principle1:notes are important
important principle2:mark the usage of the varoable
*/ 
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
const int len = 9;
vector<vector<int>> lftneib;//neib of left points
vector<vector<int>> rgtneib;//neib of right points
int lftmatch[len];
int rgtmatch[len];
int memint[2 * len];
map <int, vector<int>> mem;
bool dfs(int i);
void greedy();//using greedy approach to ini
bool tiling();
void init(int i,int j);//the function to color the whole board
const int m=5;
const int n=5;
int color[m][n];//the color of the floors black or white
int numb[m][n];
int rem[m][n];
vector<string> board;//initial input board
int main(void)
{
	string s1 = "....#";
	string s2 = "#....";
	string s3 = "..#..";
	string s4 = ".#.#.";
	board.push_back(s1);
	board.push_back(s2);
	board.push_back(s3);
	board.push_back(s4);
	board.push_back(s4);
	/*string s1 = "......";
	string s2 = "#####.";
	string s3 = ".#####";
	string s4 = "......";
	board.push_back(s1);
	board.push_back(s2);
	board.push_back(s1);
	board.push_back(s3);
	board.push_back(s4);*/
	int i = 0;
	int j = 0;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			rem[i][j] = 0;
		}
	}
	for (i = 0; i < len; i++)
	{
		lftmatch[i] = -1;
		rgtmatch[i] = -1;
	}
	for (i = 0; i < len; i++)
	{
		lftneib.push_back({});
		rgtneib.push_back({});
	}
	int cntb = 0;//count the number of black segments
	int cntw = 0;//count the number of white segments
	int initi = 0;
	int initj = 0;
	for (i = 0; i < m; i++)//find the first segment that can be filled with segments
	{
		for (j = 0; j < n; j++)
		{
			if (board[i][j] != '#')
			{
				initi = i;
				initj = j;
				color[initi][initj] = 0;
				goto out;
			}
		}
	}
out:for (i = 0; i < m; i++)//mark the ones that cannot be filled with dominos
	{
		for (j = 0; j < n; j++)
		{
			if (board[i][j] == '#')
			{
				color[i][j] = -1;//-1 for areas that can not be filled with dominos
			}
		}
	}
	init(initi,initj);//color the whole board
	for (i = 0; i < m; i++)//count the number of black and white segments
	{
		for (j = 0; j < n; j++)
		{
			if (color[i][j] == -1)
			{
				numb[i][j] = -1;
			}
			else if (color[i][j] == 0)
			{
				numb[i][j] = cntw;
				cntw++;
			}
			else if (color[i][j] == 1)
			{
				numb[i][j] = cntb;
				cntb++;
			}
		}
	}
	if (cntb != cntw)//count the number of white segments and black segmentss;
	{
		cout << 0 << endl;
		char buf[2014];
		scanf_s("%s", buf);
		return 0;
	}
	for (i = 0; i < m; i++)//construct the neibtable
	{
		for (j = 0; j < n; j++)
		{
			if (color[i][j] == 0)
			{
				if ((j + 1 != n) && (numb[i][j + 1] != -1))
				{
					lftneib[numb[i][j]].push_back(numb[i][j + 1]);
				}
				if ((j - 1 != -1) && (numb[i][j - 1] != -1))
				{
					lftneib[numb[i][j]].push_back(numb[i][j -1]);
				}
				if ((i + 1 != m) && (numb[i + 1][j] != -1))
				{
					lftneib[numb[i][j]].push_back(numb[i+1][j]);
				}
				if ((i - 1 != -1) && (numb[i - 1][j] != -1))
				{
					lftneib[numb[i][j]].push_back(numb[i-1][j]);
				}
			}
			else if (color[i][j] == 1)
			{
				if ((j + 1 != n) && (numb[i][j + 1] != -1))
				{
					rgtneib[numb[i][j]].push_back(numb[i][j + 1]);
				}
				if ((j - 1 != -1) && (numb[i][j - 1] != -1))
				{
					rgtneib[numb[i][j]].push_back(numb[i][j - 1]);
				}
				if ((i + 1 != m) && (numb[i + 1][j] != -1))
				{
					rgtneib[numb[i][j]].push_back(numb[i + 1][j]);
				}
				if ((i - 1 != -1) && (numb[i - 1][j] != -1))
				{
					rgtneib[numb[i][j]].push_back(numb[i - 1][j]);
				}
			}
			else
			{
				continue;
			}
		}
	}
	bool res= tiling();
	cout << res << endl;
	char buf[2014];
	scanf_s("%s", buf);
	return res;
	
}
void greedy()//use greedy approach to find a match first
{
	int i = 0;
	int j = 0;
	for (i = 0; i < len; i++)//i is the num of the lft one
	{
		for (j = 0; j<lftneib[i].size(); j++)
		{
			if (rgtmatch[lftneib[i][j]] == -1)//if leftneibpijh has't been matched,match.
			{
				lftmatch[i] = lftneib[i][j];
				rgtmatch[lftneib[i][j]] = i;
				break;
			}
		}
	}
	
}
bool tiling()
{
	greedy();
	int i = 0;
	int cnt = 0;
	int j = 0;
	int ind = 0;
	memset(rgtmatch, -1, sizeof(rgtmatch));
	for (i = 0; i < len; i++)
	{
		memset(memint, 0, sizeof(memint));
		if (dfs(i))//if an augment path has been found
			cnt++;
	}
	if (cnt == len)
		return 1;
	return 0;
}
bool dfs(int start)
{
	int i = 0;
	for (i = 0; i < lftneib[start].size(); i++)
	{
		if (memint[lftneib[start][i]] == 0)
		{
			memint[lftneib[start][i]]= 1;
			if((rgtmatch[lftneib[start][i]]==-1)||dfs(lftneib[start][i]))//if it hasn't been matched or u can find a augment path
			{
				rgtmatch[lftneib[start][i]] = start;
				return 1;
			}
		}
	}
	return 0;
}
void init(int i,int j)//the function to color the whole board
{
	if (rem[i][j] == 1)//memorization if has been searched return 
	{
		return;
	}
	rem[i][j] = 1;//mark
	if (color[i][j] == -1)//can not be filled with a domino
		return;
	if (color[i][j] == 0)//recursive color
	{
			if ((j+1!=n)&&(board[i][j + 1] != '#'))
			{
				color[i][j + 1] = 1;//the white one is close to a black one; 
				init(i, j + 1);
			}
			if ((j-1 != -1) && (board[i][j-1] != '#'))
			{
				color[i][j - 1] = 1;
				init(i, j - 1);
			}if ((i + 1 != m) && (board[i+1][j] != '#'))
			{
				color[i+1][j ] = 1;
				init(i+1, j);
			}if ((i-1 != -1) && (board[i-1][j] != '#'))
			{
				color[i-1][j ] = 1;
				init(i-1, j );
			}
	}
	else if (color[i][j] == 1)
	{
		if ((j + 1 != n) && (board[i][j + 1] != '#'))
		{
			color[i][j + 1] = 0;
			init(i, j + 1);
		}
		if ((j - 1 != -1) && (board[i][j - 1] != '#'))
		{
			color[i][j - 1] = 0;
			init(i, j - 1);
		}if ((i + 1 != m) && (board[i + 1][j] != '#'))
		{
			color[i + 1][j] = 0;
			init(i + 1, j);
		}if ((i - 1 != -1) && (board[i - 1][j] != '#'))
		{
			color[i - 1][j] = 0;
			init(i - 1, j);
		}
	}
}
	
