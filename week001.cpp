// Accepted at Dec. 10, 2016
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 1000000 + 5;
const char STARTCHAR = 'a' - 1;
const char ENDCHAR = 'a' - 2;
const char INTERCHAR = 'a' - 3;

char str[MAXN];
int N;
int len;
int f[2 * MAXN]; // f[i]=j means that the length of string centered at i with the largest length  is 2*j+1

char getChar(int index)
{
	if (index < 0)
		return STARTCHAR;
	if (index >= 2 * len - 1)
		return ENDCHAR;
	if (index % 2 == 1)
		return INTERCHAR;
	return str[index / 2];
}

void increase(int index)
{
	for (;;)
	{
		int nextf = f[index] + 1;
		if (getChar(index + nextf) == getChar(index - nextf))
			f[index] = nextf;
		else
			break;
	}
}

int main()
{
	cin >> N;
	while (N--)
	{
		cin >> str;
		len = strlen(str);
		memset(f, 0, sizeof(f));
		increase(1);
		for (int i = 2; i < 2 * len - 1; ++i)
		{
			if (f[i - 1] - 1>f[i - 2])
				f[i] = f[i - 2];
			else if (f[i - 1] - 1 < f[i - 2] && f[i-1]>=1)
				f[i] = f[i - 1] - 1;
			else
			{
				f[i] = min(f[i - 2],f[i-1]-1);
				increase(i);
			}
		}
		
		int ans = 0;
		for (int i = 0; i < 2 * len - 1; ++i)
		{
			if (i % 2 == 0)
			{
				ans = max(ans, f[i] / 2 * 2 + 1);
			}
			else
			{
				ans = max(ans, (f[i] +1)/2*2);
			}
		}
		cout << ans << endl;
	}

	return 0;
}





// Accepted

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
