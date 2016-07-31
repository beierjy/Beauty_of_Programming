//Chapter 1.3 翻转烙饼
//基于动态规划的思想

#include <stdlib.h>
#include <stdio.h>

void reverse(int* &array, int begin, int end){
	if (array == NULL || end <= begin){
		return;
	}
	while (begin < end){
		int temp = array[begin];
		array[begin] = array[end];
		array[end] = temp;
		end--; begin++;
	}
	for (int j = begin; j < end; j++){
		printf("%d", array[j]);
	}
}

int PreFixSorting_up(int*r_array,int  m_num,int be,int en){
	if (r_array == NULL ||be < 0 ||en < be||m_num <= 1)
		return 0;
	if (be + 1 == en && be == 0){
		if (r_array[be] > r_array[en]){
			reverse(r_array, be, en);
			return 1;
		}
		else
			return 0;
	}
	int sum_min = INT_MAX; int tag = 0;
	for (int pos = 0; pos < m_num; ++pos){
		reverse(r_array, 0, pos);
		for (int j = 0; j < m_num; j++){
			printf("%d", r_array[j]);
		}
		printf("\n");
		int m = 1 + PreFixSorting_up(r_array, m_num,0, m_num - 1);
		if (m > 2 * (m_num - 1)){
			reverse(r_array, 0, pos);
			continue;
		}
		if (sum_min > m+1){
			sum_min = m + 1;
		}
		reverse(r_array, 0, pos);
	}
	return sum_min;
}

int CPreFixSorting(int* r_array, int m_num){
	if (r_array == NULL || m_num <= 1)
		return 0;
	int min = PreFixSorting_up(r_array, m_num,0,m_num-1);
	return min;
}