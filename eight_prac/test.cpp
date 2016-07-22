#include<stdio.h>
#include<assert.h>


//��Ŀһ����һ������Ϊn����������������ֶ���0��n-1�ķ�Χ�ڡ�������ĳЩ�������ظ��ģ�����֪��
//�м��������ظ��ˣ�Ҳ��֪��ÿ�������ظ��˼��Ρ����ҳ�����������һ���ظ������֡����磬���볤��
//Ϊ7������{2��3��1��0��2��5��3}����ô��Ӧ��������ظ�������2����3

//˼·�������������ֶ���0��n-1�ķ�Χ�ڣ����������û���ظ������֣���ô����������֮������i������
//���±�i��λ�ã��������������ظ������֣���Щλ�ÿ����ж�����֡���ͷ��βһ��ɨ����������е�
//ÿ�����֣���ɨ�赽�±�Ϊi������ʱ�����ȱȽ���������ǲ��ǵ���i������ǣ�ɨ����һ�����֣����
//����ȣ��Ƚ�������ֺ��±�Ϊ�������ֽ��бȽϣ������ȣ����ҵ���һ���ظ������֡�

bool duplicate(int nums[], int len, int *duplication)
{
	if (nums == NULL || len < 0)
		return false;
	for (int i = 0; i < len; i++)
	{
		if (nums[i]<0 || nums[i]>len - 1)
			return false;
	}
	for (int i = 0; i < len; i++)
	{
		while (nums[i] != i)
		{
			//��ȵ����
			if (nums[i] == nums[nums[i]])
			{
				*duplication = nums[i];
				return true;
			}
			//����nums[i]��nums[nums[i]]
			int tmp = nums[i];
			nums[i] = nums[tmp];
			nums[tmp] = tmp;
		}
	}
	return false;
}
int main()
{
	int arr[] = { 2, 3, 1, 0, 2, 5, 3 };
	int ret = 0;
	duplicate(arr, 7, &ret);
	printf("%d\n", ret);
	return 0;
}




//��Ŀ��������һ������A[0,1,...,n-1],�빹��һ������B[0,1,...,n-1],����B�е�Ԫ��B[i]=A[0]*A[1]*
//A[2]*...*A[i-1]*A[i+1]*...*A[n-1]������ʹ�ó�����

//˼·�����԰�B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]������A[0]*A[1]*...*A[i-1]��A[i+1]*...*A[n-1]
//�����ֵĳ˻�����ˣ�����B������һ������������������˼·��ʱ�临�Ӷ���O(n)

#include<iostream>
using namespace std;
#include<vector>
void multiply(const vector<double>& arr1, vector<double>& arr2)
{
	int len1 = arr1.size();
	int len2 = arr2.size();
	if (len1 == len2 && len2 > 1)
	{
		arr2[0] = 1;
		for (int i = 1; i < len1; i++)
		{
			arr2[i] = arr2[i - 1] * arr1[i - 1];
		}
		double tmp = 1;
		for (int i = len1 - 2; i >= 0; --i)
		{
			tmp *= arr1[i + 1];
			arr2[i] *= tmp;
		}
	}
}




//��Ŀ������ʵ��һ����������ƥ�������.���͡�*����������ʽ��ģʽ�е��ַ���.����ʾ����һ���ַ���
//����*����ʾ��ǰ����ַ����Գ������⣨��0�Σ����ڱ����У�ƥ����ָ�ַ����������ַ�ƥ������ģʽ��
//���磬�ַ�����aaa����ģʽ��a.a���͡�ab*ac*a��ƥ�䣬���롰aa.a������ab*a������ƥ�䡣

//˼·��ÿ�δ��ַ������ó�һ���ַ���ģʽ�е��ַ�ȥƥ�䣬Ҫ�ֱ��жϡ�.���͡�*���������ģʽ�е�
//�ڶ����ַ��ǡ�*��������Ƚϸ��ӣ������������ִ��������1��ֱ�Ӻ��ԣ�2����ģʽ������ƶ�����
//�ַ���3�����ֵ�ǰ״̬

bool MatchCore(char* str, char* pattern)
{
	if (*str == '\0' && *pattern == '\0')
		return true;
	if (*str != '\0' && *pattern == '\0')
		return false;
	//����ڶ����ַ���*�����
	if (*(pattern + 1) == '*')
	{
		if (*pattern == *str || (*pattern == '.' && *str != '\0'))
			//��ģʽ������ƶ������ַ�
			return MatchCore(str + 1, pattern + 2) || 
			//���ֵ�ǰ״̬
			MatchCore(str + 1, pattern) || 
			//����*
			MatchCore(str, pattern + 2);
		else
			//����*
			return MatchCore(str, pattern + 2);
	}
	if (*str == *pattern || (*pattern == '.' && *str != '\0'))
		return MatchCore(str + 1, pattern + 1);
	return false;
}


//��Ŀ�ģ���ʵ��һ�����������ж��ַ����Ƿ��ʾ��ֵ������������С���������磬�ַ�����+100����
//��5e2������-123������3.1416������-1E-16������ʾ��ֵ������12e������1a3.14������1.2.3����
//��+-5������12e+5.4�������ǡ�

//˼·��Ҫ�ж��ַ����Ƿ��ʾ��ֵ����������ֵ֮ǰ������һ�����Ż��߸��ţ�Ȼ�������֣������п�
//����С�������ܰ���С���㣬С����֮�������֣�Ȼ���ֿ��ܳ���e����E��e����E֮���п��ܺ���+��
//-��Ȼ�������֡�

//�˺�������ɨ���ַ�����0-9����λ
void scanDigits(char** str)
{
	while (**str != '\0' && **str >= '0' && **str <= '9')
		++(*str);
}
//�˺�������ƥ���ѧ��������ʾ����ֵ�Ľ�β����
bool IsExpontial(char** str)
{
	if (**str != 'e' || **str != 'E')
		return false;
	++(*str);
	if (**str == '+' || **str == '-')
		++(*str);
	if (**str == '\0')
		return false;
	scanDigits(str);
	return (**str == '\0') ? true : false;
}
bool IsNumeric(char* str)
{
	if (str == NULL)
		return false;
	//�����һ���ַ���+����-�����
	if (*str == '+' || *str == '-')
		str++;
	//������ַ��������
	if (*str == '\0')
		return false;

	bool numeric = true;
	//ɨ������
	scanDigits(&str);

	if (*str != '\0')
	{
		//����С��������
		if (*str == '.')
		{
			str++;
			scanDigits(&str);

			//С�������e����E
			if (*str == 'e' || *str == 'E')
				numeric = IsExpontial(&str);
		}
		//�������������
		else if (*str == 'e' || *str == 'E')
			numeric = IsExpontial(&str);
		else
			numeric = false;
	}
	return numeric && *str == '\0';
}




//��Ŀ�壺��ʵ��һ�����������ҳ��ַ����е�һ��ֻ����һ�ε��ַ������磬�����ַ�����ֻ����ǰ��
//���ַ���go��ʱ����һ��ֻ����һ�ε��ַ��ǡ�g�������Ӹ��ַ����ж���ǰ�����ַ���google��ʱ����һ
//��ֻ����һ�ε��ַ��ǡ�1��.

//˼·����������ÿһ���ַ����������������ù�ϣ������ԣ��Ϳ��Խ��ַ����ֵĴ���Ҳ����������Ȼ��
//�ٱ���һ�Σ��ҵ���һ�����ִ���Ϊ1���ַ�
#include<iostream>
using namespace std;
#include<string>
class Solution
{
private:
	string str;
	int arr[256];
public:
	Solution()
	{
		for (int i = 0; i < 256; i++)
		{
			arr[i] = 0;
		}
	}
	//��ÿ���ַ�������string�У����ַ���ASCII����Ϊ�±ֵ꣬Ϊ���ֵĴ���
	void Insert(char ch)
	{
		str += ch;
		arr[ch]++;
	}
	//�ҳ���һ��ֻ����һ�ε��ַ�
	char FirstAppearingOnce()
	{
		int len = str.size();
		for (int i = 0; i < len; i++)
		{
			if (arr[str[i]] == 1)
				return str[i];
		}
		cout << "û���ҵ�ֻ����һ�ε��ַ�" << endl;
		return '#';
	}
};
int main()
{
	Solution s;
	s.Insert('g');
	s.Insert('o');
	s.Insert('o');
	s.Insert('g');
	s.Insert('l');
	s.Insert('e');
	char ret=s.FirstAppearingOnce();
	printf("%c\n", ret);
	return 0;
}


//��Ŀ����һ�������а�����������ҳ�������ڽ�㣿

//˼�룺���л����������ҵ�������ڽ��Ĳ��裺1��ָ��p1��p2�ڳ�ʼ��ʱ��ָ�������ͷ��㣻2����
//���м�����㣬�ͽ�p1�����������ƶ�������3��ָ��p1��p2����ͬ���ٶ�����������ǰ�ƶ�ֱ��������
//���������Ľ����ǻ�����ڽ�㡣

//�ѵ�����󻷵Ľ�����,�������ڻ����ҳ�һ����㣬Ȼ��������������ߣ�һ����ǰ�ƶ�һ�߼���
//���ٴλص��������ʱ�򣬾Ϳ��Եõ����н�������Ҫ�ڻ����ҳ�һ����㣬�������ÿ���ָ���
//˼�롣
struct ListNode
{
	ListNode* next;
	int val;
};
ListNode* MeetingNode(ListNode* pHead)
{
	if (pHead == NULL)
		return NULL;
	ListNode* slow = pHead;
	ListNode* fast = pHead->next;
	while (slow != NULL && fast != NULL)
	{
		//����ָ�����������ҵ��������
		if (slow == fast)
			return fast;
		//��ָ��һ����һ��
		slow = slow->next;
		//��ָ��һ��������
		fast = fast->next->next;
	}
	return NULL;
}
ListNode* EntryOfLoop(ListNode* pHead)
{
	if (pHead == NULL)
		return NULL;

	ListNode* meetingNode = MeetingNode(pHead);
	
	//�󻷵Ľ�����
	int NodeInLoop = 1;
	ListNode* begin = meetingNode;
	while (begin->next != meetingNode)
	{
		begin = begin->next;
		NodeInLoop++;
	}
	//��һ��ָ����ǰ�ƶ�NodeInLoop��
	begin = pHead;
	for (int i = 0; i < NodeInLoop; i++)
		begin = begin->next;

	//����ָ��ͬʱ�ߣ�ֱ������
	ListNode* end = pHead;
	while (begin != end)
	{
		begin = begin->next;
		end = end->next;
	}
	return begin;
}


//��Ŀ�ߣ���һ������������У����ɾ���ظ��Ľ�㣿

//˼·�����Ҫɾ���Ľ����ͷ��㣬��ɾ�������Ĳ���Ӧ����ָ��ͷ����ָ�룬�����ǽ�ͷ��㴫��
//ɾ������������prev��next��ʵ��ɾ���ڵ㣬����prev��next��������
struct ListNode
{
	ListNode* next;
	int val;
};
void DeleteCommNode(ListNode** pHead)
{
	if ((pHead == NULL) || (*pHead == NULL))
		return;
	//pNode:ָ��ǰ�ڵ�
	ListNode* pNode = *pHead;
	//prev:ָ��ǰһ���ڵ�
	ListNode* prev = NULL;

	while (pNode != NULL)
	{
		ListNode* pNext = pNode->next;
		bool needDelete = false;
		//�ж�ͷ����Ƿ����ظ���
		if (pNext != NULL && pNode->val == pNext->val)
			needDelete = true;
		//ͷ���û���ظ�
		if (!needDelete)
		{
			prev = pNode;
			pNode = pNode->next;
		}
		//ͷ�����Ҫɾ��
		else
		{
			int val = pNode->val;
			//DelNode:����Ҫɾ���Ľ��
			ListNode* DelNode = pNode;
			while (DelNode != NULL && DelNode->val == val)
			{
				//ָ��ָ����һ���ڵ�
				pNext = DelNode->next;
				//ɾ�����
				delete DelNode;
				DelNode = NULL;

				//�����ж���һ�����
				DelNode = pNext;
			}
			//ͷ����ѱ�ɾ����������ͷ���
			if (prev == NULL)
				*pHead = pNext;
			//ͷ���û��ɾ��
			else
				prev->next = pNext;
			//pNodeָ��ͷ��㣬������һ��
			pNode = pNext;
		}
	}
}