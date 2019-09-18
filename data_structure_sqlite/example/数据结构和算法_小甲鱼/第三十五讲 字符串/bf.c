// 返回子串T在主串S中第pos个字符之后的位置
// 若不存在，则返回0
// T非空，1 <= pos <= strlen(S)
// 注意：我们这里为了表述方便，字符串使用了第一个元素表示长度的方式。

int index( String S, String T, int pos )
{
	int i = pos;	// i用于主串S中当前位置下标
	int j = 1;		// j用于子串T中当前位置下标
	
	while( i <= S[0] && j <= T[0] )	// i或j其中一个到达尾部即终止搜索！
	{
		if( S[i] == T[i] )	// 若相等则继续下一个元素匹配
		{
			i++;
			j++;
		}
		else				// 若失配则j回溯到第一个元素从新匹配
		{
			i = i-j+2;		// i回溯到上次匹配首位的下一个元素，这是效率低下的关键！
			j = 1;
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