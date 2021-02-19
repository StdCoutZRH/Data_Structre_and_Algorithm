#include<stdio.h>

//���ֲ��� O(logn)
int binary_search(int a[], int n,int value)
{
	/*
		���ֲ�����������˳���ṹ���򵥵�˵��������,
		��Σ����ֲ�����Ե����������ݡ�
	*/

	int low = 0, high = n - 1;
	while (low <= high)
	{
		int mid = low + ((high - low) >> 1);//����ע�����ţ�+���ȼ�����>>
		if (a[mid] == value)
		{
			return mid;
		}
		else if (a[mid] < value)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}

	return -1;
}