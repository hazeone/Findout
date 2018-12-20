#include<bits/stdc++.h>
using namespace std;
const int N=1024;
int Maze[N][N][4];
int n=2,m=2;
void Division(int r1,int r2,int c1,int c2)
{
	if(r1<r2 && c1<c2)
	{
		int midr=rand()%(r2-r1)+r1;
		int midc=rand()%(c2-c1)+c1;
		int rr1=rand()%(midr-r1+1)+r1;
		int rr2=rand()%(r2-midr)+midr+1;
		int rc1=rand()%(midc-c1+1)+c1;
		int rc2=rand()%(c2-midc)+midc+1;
		int opt=rand()%4;
		if(opt==0)
		{
			//left wall
			Maze[midr][rc1][3]=1;
			Maze[midr+1][rc1][1]=1;

			//top wall
			Maze[rr1][midc][2]=1;
			Maze[rr1][midc+1][0]=1;

			//right wall
			Maze[midr][rc2][3]=1;
			Maze[midr+1][rc2][1]=1;
		}
		else if(opt==1)
		{
			//bottom wall
			Maze[rr2][midc][2]=1;
			Maze[rr2][midc-1][0]=1;

			//top wall
			Maze[rr1][midc][2]=1;
			Maze[rr1][midc+1][0]=1;

			//right wall
			Maze[midr][rc2][3]=1;
			Maze[midr+1][rc2][1]=1;
		}
		else if(opt==2)
		{
			//bottom wall
			Maze[rr2][midc][2]=1;
			Maze[rr2][midc-1][0]=1;

			//right wall
			Maze[midr][rc2][3]=1;
			Maze[midr+1][rc2][1]=1;

			//left wall
			Maze[midr][rc1][3]=1;
			Maze[midr+1][rc1][1]=1;
		}
		else
		{
			//bottom wall
			Maze[rr2][midc][2]=1;
			Maze[rr2][midc-1][0]=1;

			//top wall
			Maze[rr1][midc][2]=1;
			Maze[rr1][midc+1][0]=1;

			//left wall
			Maze[midr][rc1][3]=1;
			Maze[midr+1][rc1][1]=1;
		}
		Division(r1,midr,c1,midc);
		Division(r1,midr,midc+1,c2);
		Division(midr+1,r2,c1,midc);
		Division(midr+1,r2,midc+1,c2);
	}
	else if(r1<r2)
	{
		int midr=rand()%(r2-r1)+r1;
		Maze[midr][c1][3]=1;
		Maze[midr+1][c1][1]=1;
		Division(r1,midr,c1,c2);
		Division(midr+1,r2,c1,c2);
	}
	else if(c1<c2)
	{
		int midc=rand()%(c2-c1)+c1;
		Maze[r1][midc][2]=1;
		Maze[r2][midc+1][0]=1;
		Division(r1,r2,c1,midc);
		Division(r1,r2,midc+1,c2);
	}
}
int main()
{
	srand(time(0));
	int r1,c1,r2,c2;
	r1=c1=0;
	r2=n-1;
	c2=m-1;
	memset(Maze,0,sizeof(Maze));
	Division(r1,r2,c1,c2);
	Maze[r1][c1][0]=1;
	Maze[r2][c2][2]=1;
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	{
		for(int k=0;k<4;k++)
		{
			cout<<Maze[i][j][k]<<" ";
		}cout<<endl;
	}
	return 0;
}
