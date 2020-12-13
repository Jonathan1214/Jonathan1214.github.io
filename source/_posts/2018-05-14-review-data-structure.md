---
title: 数据结构复习
categories:
  - 学习
tags:
  - C/C++
  - 数据结构
date: 2018-05-14 20:25:46
updated: 2020-03-11 20:10:12
---

先抄一段Dave在他的书《The Pragmatic Programmer》中的话：
>You're a Pragmatic Programmer. You aren't wedded to any particular technology, but you have a broad enough background in the science, and your experience with practical projects allow you to choose good solution in particular situations. Theory and practice combine to make you strong. You adjust your approach to suit the current circumstance and environment. And you do this continuously as the work progresses. Pragmatic Programmers get the job done, and do it well.

Ok，现在开始吧！

<!--more-->
# C语言程序设计
## 开始
1. 先上第一段代码：

```C
#include <stdio.h>
int main(void)
{
    printf("Hello world\n");
    printf("This is a C program");
	return 0;
}
```
这是一个简单的C程序，我从这里开始，解释什么的是不需要的。

2. 第二段代码：
```C
#include <stdio.h>
int main (void)
{
	//这个程序根据你输入的两个整数和输入的一个四则运算符进行运算
	int a, b;
	unsigned int Bool = 0;
	char ch;
	printf("请输入两个整数：");
	scanf("%d", &a);

    scanf("%d", &a);
    printf("\n请输入一个四则运算符：");
    Bool = scanf("%c", &ch);

    switch (ch)
    {
		case '+': printf("\n%d + %d = %d", a, b, a+b);
				  break;
		case '-': printf("\n%d - %d = %d", a, b, a-b);
				  break:;
		case '*': printf("\n%d * %d = %d", a, b, a*b);
				  break;
		case '/': printf("\n%d / %d = %f", a, b, float(a)/b);
				  break;
		default:  printf("输入的不是四则运算符！！！");
				  break;
	}
	return 0;
}
```
OK，上面的代码写出来了！没有什么问题！记几个需要注意的地方：
	1. `scanf()`的是有返回值，读到了几个正确的输入就返回几，例如在上面的代码的中，如果输入了一个字符，`Bool`的值就变成`1`，在这里作用不大，不过就是为了复习嘛，无所谓的啦。
	2. 注意`switch() case`语句的用法：`switch()`括号内的变量类型一定要是__整型或者字符型__。

3. 第三段代码：
```C
#include <stdio.h>
int main (void)
{
	//定义一个二维数组并初始化
	int a[2][3] = {
		{1, 2, 3},
		{4, 5, 6}
	};

	//几个指针的声明
	int *pt;
	int (*pa)[3];  //注意：[]的优先级高于*
	int *pax[3];   //注意与上一个进行对比，这是不一样的
	int ar1[2][3];
	int ar2[3][2];
	int **p2;

	//以下均是有效的赋值
	pt = &a[0][0];
	pa = &a[0];   //在这里pt和pa的值相同
	pa = &a[1];
	p2 = &pt;
}
```
从上面就可以看出来，指针这个东西还是很烦人的，不过也不难，多看几遍就行了，还有要注意指针和数组的关系。指针比数组更本质！

4. 第四段代码：
```C
//找二维数组的鞍点，行最小且列最大的即为鞍点
#include <stdio.h>
int main (void)
{
	int a[20][20];
	int Row, Col;
	int i, j;
	printf("请输入数组的行数和列数：");
	scanf("%d%d", Row, Col);
	printf("\n请输入%d个整数：\n\t", Row*Col);
	for (i = 0; i < Row; i++)
		for (j = 0; j < Col; j++)
			scanf("%d", &a[i][j]);

	for (i = 0; i < Row; i++)
	{
		int temp = a[i][0];
		int k = 0;
		int f = 1;
		for (j = 1; j < Col; j++)
		{
			if (temp > a[i][j])
			{
				temp = a[i][j];
				k = j;
			}
		}
		for (j = 0; j < Row; j++)
		{
			if (j == i)
				continue;
			else
			{
				if (a[j][k] > a[i][k])
					f = 0;
			}
		}
		if (f)
			printf("\n%d", &a[i][k]);
		else
			printf("\n无鞍点");
	}
	return 0;
}
```
我也不管什么优化了，丑就丑吧，几个循环套起来又怕什么，比比谁写的更丑，没有运行时间和内存使用限制，写起来就是爽！

5. 第五段代码：
```C
#include <stdio.h>
int main (void)
{
	printf("这是一个计算函数值的程序：\n");
	int x, y;
	printf("请输入整数x的值：");
	scanf("%d", &x);
	if (x < 0)
		y = 5*x;
	else
	{
		if (x < 8)
			y = 2*x - 1;
		else
			y = x + 4;
	}
	printf("\ny = %d", y);
	return 0;
}
```
这段代码没什么意思，纯粹是送的。

6. 第六段代码：
```C
#include <stdio.h>
void Pri_as_ord(int *p, int *q)
{
	int temp;
	if (*p > *q)
	{
		temp = *p;
		*p = *q;
		*q = temp;
	}
}
int main (void)
{
	int a, b;
	printf("请输入两个整数：");
	scanf("%d%d", &a, &b);
	Pri_as_ord(&a, &b);
	printf("按由小到大的顺序输出：%d %d", a, b);
	return 0;
}
```
还是没什么意思，接着写！

7. 第七段代码：
```C
/*录入三个学生的学号和各自两门课的成绩

*/
#include <stdio.h>
struct Student{
	int num;
	float score1;
	float score2;
};
void Best(struct Student student[], int n)
{
	int i, m, aver[n];
	for (i = 0; i < n; i++)
		aver[i] = (student[i].score1 + student[i].score2)/2;
	if (aver[0] > aver[1])
	{
		if (aver[0] > aver[2])
			m = 0;
		else
			m = 2;
	}
	else
	{
		if (aver[1] > aver[2])
			m = 1;
		else
			m = 2;
	}
	printf("平均成绩最高的学生的学号是：%d", student[m].num);
}
int main (void)
{
	int i = 1;
	struct Student student[3];
	for (; i < 4; i++)
		printf("请输入第%d个学生的学号和两门课的成绩:%d %f %f",
				i, student[i-1].num, student[i-1].score1, student[i-1].score2);
	Best(student, 3);
	return 0;
}
```
哇！写得想吐了！超级累！不管继续！

8. 第八段代码
```C
/*这只是一个函数，用来实现删除单链表中码值相同的节点，只保留一个

假设节点是这样的：struct node{
					int data;
					struct node *next;
				};
*/

void Del(struct node *head)
{
	struct node *p, *q, *s;
	p = head->next;
	if (p == NULL)
		printf("Empty List");
	else
	{
		while (p->next != NULL)
		{
			q = p->next;
			do {
				while ((q->data != p->data) && (q->next != NULL))
				{
					s = q;
					q = q->next;
				}
				if (q->data == x)
				{
					s->next = q->next;
					free (q);
				}
				p = s->next;
			} while (p != NULL);
			p = p->next;
		}
	}
}
```
上面的代码有点烦，不过好在思路还算清晰，没有遇到问题，就是时间花得太长了，单链表还是不够熟练，接着来！

9. 第九段代码：
```C
//一个队列入排操作
struct queue{
	int item[max];
	int front;
	int rear;
};

//初始化时rear=-1，front为0~max-1的任意值
//front指向队列第一个元素的前一个位置，rear指向队尾元素所在位置
//front=rear时队列满，rear=-1时队列空
struct queue q;
void Inqueue(struct queue q, int x)
{
	if (q.front == q.rear)
		printf("队满");
	else
	{
		if (q.rear = -1)
			q.rear = q.front;
		if (q.rear = max-1)
			q.rear = 0;
		q.rear += 1;
		q.item[q.rear] = x;
	}
}
```
简单的顺序存储的队列，实现入排操作不难，弄懂原理就好。
