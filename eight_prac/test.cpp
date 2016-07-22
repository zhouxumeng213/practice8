#include<stdio.h>
#include<assert.h>


//题目一：在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字是重复的，但不知道
//有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。例如，输入长度
//为7的数组{2，3，1，0，2，5，3}，那么对应的输出是重复的数字2或者3

//思路：由于所有数字都在0到n-1的范围内，如果数组中没有重复的数字，那么当数组排序之后数字i将出现
//在下标i的位置，由于数组中有重复的数字，有些位置可能有多个数字。从头到尾一次扫描这个数组中的
//每个数字，当扫描到下标为i的数字时，首先比较这个数字是不是等于i，如果是，扫描下一个数字，如果
//不想等，比较这个数字和下标为它的数字进行比较，如果相等，就找到了一个重复的数字。

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
			//相等的情况
			if (nums[i] == nums[nums[i]])
			{
				*duplication = nums[i];
				return true;
			}
			//交换nums[i]和nums[nums[i]]
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




//题目二、给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0]*A[1]*
//A[2]*...*A[i-1]*A[i+1]*...*A[n-1]。不能使用除法。

//思路：可以把B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]看成是A[0]*A[1]*...*A[i-1]和A[i+1]*...*A[n-1]
//两部分的乘积，因此，数组B可以用一个矩形来创建。这种思路的时间复杂度是O(n)

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




//题目三、请实现一个函数用来匹配包含‘.’和‘*’的正则表达式。模式中的字符‘.’表示任意一个字符，
//而‘*’表示它前面的字符可以出现任意（含0次）。在本题中，匹配是指字符串的所有字符匹配整个模式。
//例如，字符串“aaa”与模式“a.a”和“ab*ac*a”匹配，但与“aa.a”及“ab*a”均不匹配。

//思路：每次从字符串里拿出一个字符和模式中的字符去匹配，要分别判断‘.’和‘*’的情况。模式中的
//第二个字符是‘*’的情况比较复杂，它可以有三种处理情况，1、直接忽略；2、在模式上向后移动两个
//字符；3、保持当前状态

bool MatchCore(char* str, char* pattern)
{
	if (*str == '\0' && *pattern == '\0')
		return true;
	if (*str != '\0' && *pattern == '\0')
		return false;
	//处理第二个字符是*的情况
	if (*(pattern + 1) == '*')
	{
		if (*pattern == *str || (*pattern == '.' && *str != '\0'))
			//在模式上向后移动两个字符
			return MatchCore(str + 1, pattern + 2) || 
			//保持当前状态
			MatchCore(str + 1, pattern) || 
			//忽略*
			MatchCore(str, pattern + 2);
		else
			//忽略*
			return MatchCore(str, pattern + 2);
	}
	if (*str == *pattern || (*pattern == '.' && *str != '\0'))
		return MatchCore(str + 1, pattern + 1);
	return false;
}


//题目四：请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串“+100”、
//“5e2”、“-123”、“3.1416”及“-1E-16”都表示数值，但“12e”、“1a3.14”、“1.2.3”、
//“+-5”及“12e+5.4”都不是。

//思路：要判断字符串是否表示数值，首先在数值之前可能有一个正号或者负号，然后是数字，数字有可
//能是小数，可能包含小数点，小数点之后还有数字，然后又可能出现e或者E，e或者E之后有可能含有+或
//-，然后是数字。

//此函数用来扫描字符串中0-9的数位
void scanDigits(char** str)
{
	while (**str != '\0' && **str >= '0' && **str <= '9')
		++(*str);
}
//此函数用来匹配科学计数法表示的数值的结尾部分
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
	//处理第一个字符是+或者-的情况
	if (*str == '+' || *str == '-')
		str++;
	//处理空字符串的情况
	if (*str == '\0')
		return false;

	bool numeric = true;
	//扫描数字
	scanDigits(&str);

	if (*str != '\0')
	{
		//处理小数点的情况
		if (*str == '.')
		{
			str++;
			scanDigits(&str);

			//小数点后有e或者E
			if (*str == 'e' || *str == 'E')
				numeric = IsExpontial(&str);
		}
		//处理整数的情况
		else if (*str == 'e' || *str == 'E')
			numeric = IsExpontial(&str);
		else
			numeric = false;
	}
	return numeric && *str == '\0';
}




//题目五：请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两
//个字符“go”时，第一个只出现一次的字符是‘g’。当从该字符流中读出前六个字符“google”时，第一
//个只出现一次的字符是‘1’.

//思路：将读到的每一个字符都保存起来，利用哈希表的特性，就可以将字符出现的次数也保存起来，然后
//再遍历一次，找到第一个出现次数为1的字符
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
	//将每个字符保存在string中，其字符的ASCII码作为下标，值为出现的次数
	void Insert(char ch)
	{
		str += ch;
		arr[ch]++;
	}
	//找出第一个只出现一次的字符
	char FirstAppearingOnce()
	{
		int len = str.size();
		for (int i = 0; i < len; i++)
		{
			if (arr[str[i]] == 1)
				return str[i];
		}
		cout << "没有找到只出现一次的字符" << endl;
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


//题目六：一个链表中包含环，如何找出环的入口结点？

//思想：在有环的链表中找到环的入口结点的步骤：1、指针p1和p2在初始化时都指向链表的头结点；2、环
//中有几个结点，就将p1现在链表上移动几步；3、指针p1和p2以相同的速度在链表上向前移动直到它们相
//遇，相遇的结点就是环的入口结点。

//难点就是求环的结点个数,可以先在环中找出一个结点，然后从这个结点往后走，一边向前移动一边计数
//当再次回到这个结点的时候，就可以得到环中结点个数。要在环中找出一个结点，可以利用快慢指针的
//思想。
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
		//快慢指针相遇，即找到相遇结点
		if (slow == fast)
			return fast;
		//慢指针一次走一步
		slow = slow->next;
		//快指针一次走两步
		fast = fast->next->next;
	}
	return NULL;
}
ListNode* EntryOfLoop(ListNode* pHead)
{
	if (pHead == NULL)
		return NULL;

	ListNode* meetingNode = MeetingNode(pHead);
	
	//求环的结点个数
	int NodeInLoop = 1;
	ListNode* begin = meetingNode;
	while (begin->next != meetingNode)
	{
		begin = begin->next;
		NodeInLoop++;
	}
	//第一个指针向前移动NodeInLoop步
	begin = pHead;
	for (int i = 0; i < NodeInLoop; i++)
		begin = begin->next;

	//两个指针同时走，直到相遇
	ListNode* end = pHead;
	while (begin != end)
	{
		begin = begin->next;
		end = end->next;
	}
	return begin;
}


//题目七：在一个排序的链表中，如何删除重复的结点？

//思路：如果要删除的结点是头结点，则删除函数的参数应该是指向头结点的指针，而不是将头结点传给
//删除函数。定义prev、next来实现删除节点，并将prev和next连接起来
struct ListNode
{
	ListNode* next;
	int val;
};
void DeleteCommNode(ListNode** pHead)
{
	if ((pHead == NULL) || (*pHead == NULL))
		return;
	//pNode:指向当前节点
	ListNode* pNode = *pHead;
	//prev:指向前一个节点
	ListNode* prev = NULL;

	while (pNode != NULL)
	{
		ListNode* pNext = pNode->next;
		bool needDelete = false;
		//判断头结点是否是重复的
		if (pNext != NULL && pNode->val == pNext->val)
			needDelete = true;
		//头结点没有重复
		if (!needDelete)
		{
			prev = pNode;
			pNode = pNode->next;
		}
		//头结点需要删除
		else
		{
			int val = pNode->val;
			//DelNode:保存要删除的结点
			ListNode* DelNode = pNode;
			while (DelNode != NULL && DelNode->val == val)
			{
				//指针指向下一个节点
				pNext = DelNode->next;
				//删除结点
				delete DelNode;
				DelNode = NULL;

				//继续判断下一个结点
				DelNode = pNext;
			}
			//头结点已被删除，重新置头结点
			if (prev == NULL)
				*pHead = pNext;
			//头结点没被删除
			else
				prev->next = pNext;
			//pNode指向头结点，继续下一次
			pNode = pNext;
		}
	}
}