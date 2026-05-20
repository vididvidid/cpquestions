/*
 * File: orig.cpp
 * Author: vididvidid 
 * Created: 2026-04-15 02:31:44
 */

#include<iostream>
#include<cassert>
using namespace std;
int N,L[20];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>N;
	for(int i=0;i<N;i++)cin>>L[i];
	int ans=0;
	for(int i=0;i<1<<N;i++)
	{
		long cur=0;
		int cnt=0;
		for(int j=0;j<N;j++)
		{
			long nxt=cur;
			if(i>>j&1)nxt+=L[j];
			else nxt-=L[j];
			if(cur>=0&&nxt<0||cur<0&&nxt>=0)cnt++;
			cur=nxt;
		}
		ans=max(ans,cnt);
	}
	cout<<ans<<endl;
}

