#include <iostream>
#include <cstring>
using namespace std;
const char HELP='#';
char str[1000005];
char stre[2000005];

int main()
{
	int n,len;
	
	cin>>n;
	while(n--)
	{
		cin>>str;
		len=strlen(str);
		for (int i = 0; i < len; ++i)
		{
			stre[2*i]=str[i];
			stre[2*i+1]=HELP;
		}
		stre[2*len-1]=0;
		//cout<<stre<<endl;
		int P[2000005]={0};
		int id,mx;
		P[0]=1;
		id=0;
		mx=1;
		for(int i=1;i<2*len-1;++i)
		{
			P[i]=1;
			if(i<mx)
			{
				int j=2*id-i;
				if(P[j]<mx-i)
					P[i]=P[j];
				else
					P[i]=mx-i;
			}
			for(;;P[i]++)
			{
				int k=i-P[i]+1;
				int l=i+P[i]-1;
				if(k<0||l>=2*len-1||stre[k]!=stre[l])
				{
					P[i]--;
					break;
				}
			}
			if(i+P[i]>mx)
			{
				mx=i+P[i];
				id=i;
			}
		}
		int ans=1;
		for(int i=0;i<2*len-1;i++)
		{
			if(i%2==0)
			{
				int t=(P[i]-1)/2*2+1;
				if(t>ans)
					ans=t;
			}
			else
			{
				int t=P[i]/2*2;
				if(t>ans)
					ans=t;
			}
		}
		
		cout<<ans<<endl;
	}
	return 0;
}
