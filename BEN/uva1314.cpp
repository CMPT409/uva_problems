#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int wa[200010],wb[200010];
int v[200010];
char s[200010];
int sa[200010];
int L;
int suffixArray(int n,int m)
{
	int c[200010];
	int i,j,k,t,p,min,pos;
	int *x=wa, *y=wb, *temp=wa; 
	for (i=0;i<m;i++) c[i] = 0;
	for (i=0;i<n;i++) c[x[i] = s[i]]++;
	for (i=0;i<m;i++) c[i] += c[i-1];
	for (i=n-1;i>=0;i--)
	{
		c[x[i]]--;
		v[c[x[i]]]=i;
		sa[c[x[i]]]=i;
	}
	t=L;
	int a[500], top=0;
	while (t!=1)
	{
		if (t%2)
		{
			a[top++]=0;
			t-=1;
		}
		else
		{
			a[top++]=1;
			t/=2;
		}
	}
	j=1;
	
	for (k=0;k<top;k++)
	{
		t=a[top-k-1];
		
		p=0;
		for (i=n-j;i<n;i++) y[p++] = i;
		if (!t)
		{
			for (i=0;i<n;i++) if (v[i] >= j) y[p++]=v[i]-j;
		}
		else 
		{
			for (i=0;i<n;i++) if (sa[i] >= j) y[p++]=sa[i]-j;
		}
		for (i=0;i<m;i++) c[i] = 0;
		for (i=0;i<n;i++) c[x[y[i]]]++;
		for (i=1;i<m;i++) c[i] += c[i-1];
		for (i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];	
		temp=x;
		x=y;
		y=temp;
		p=1;
		x[sa[0]]=0;
		if (!t)
		{
			for (i=1;i<n;i++)
			{
				x[sa[i]]=((y[sa[i]]==y[sa[i-1]])&&(y[sa[i]+1]==y[sa[i-1]+1]))?p-1:p++;
			}
		}
		else 
		{
			for (i=1;i<n;i++)
			{
				x[sa[i]]=((y[sa[i]]==y[sa[i-1]])&&(y[sa[i]+j]==y[sa[i-1]+j]))?p-1:p++;
			}
		}
		if (!t)
		{
			j+=1;
		}
		else 
		{
			j*=2;
		}
		m=p;
	}
	
	min=99999999;
	pos=0;
	for (i=0;i<n/2;i++)
	{
		if (x[i]<min)
		{
			min=x[i];
			pos=i;
		}
	}
	return pos;
}
	
int main()
{
	int T,i;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%s", &L, s);
		for (i=0;i<=L;i++)
		{
			s[i+L]=s[i];
		}
		printf("%d\n",suffixArray(L*2+1,256));
		
	}
	return 0;
}
