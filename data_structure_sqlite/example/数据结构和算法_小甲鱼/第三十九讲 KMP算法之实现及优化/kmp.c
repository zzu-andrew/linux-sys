#include <stdio.h>

typedef char* String;

void get_next( String T, int *next )
{
	int j = 0;
	int i = 1;
	next[1] = 0;

	while( i < T[0] )
	{
		if( 0 == j || T[i] == T[j] )
		{
			i++;
			j++;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
}

// 返回子串T在主串S第pos个字符之后的位置
// 若不存在，则返回0
int Index_KMP( String S, String T, int pos )
{
	int i = pos;
	int j = 1;
	int next[255];

	get_next( T, next );
	
	while( i <= S[0] && j <= T[0] )
	{
		if( 0 == j || S[i] == T[j] )
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}

	if( j > T[0] )
	{
		return i - T[0];
	}
	else
	{
		return 0;
	}
}
