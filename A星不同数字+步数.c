#include "Stdio.h"
#include "Conio.h"
#include "stdlib.h"
#include "math.h"

void Copy_node(struct node *p1, struct node *p2);
void Calculate_f(int deepth, struct node *p);
void Add_to_open(struct node *p);
void Add_to_closed(struct node *p);
void Remove_p(struct node *name, struct node *p);
int Test_A_B(struct node *p1, struct node *p2);
struct node * Search_A(struct node *name, struct node *temp);
void Print_result(struct node *p);


struct node // 定义8数码的节点状态 
{
	int s[3][3]; //当前8数码的状态
	int i_0;   //当前空格所在行号
	int j_0;   //当前空格所在列号
	int f;     //当前代价值
	int d;     //当前节点深度
	int h;     //启发信息，采用数码"不在位"距离和
	struct node *father; //指向解路径上该节点的父节点
	struct node *next;   //指向所在open或closed表中的下一个元素
};

struct node s_0 = { {2,0,8,1,5,3,7,4,6},0,1,0,0,0,NULL,NULL }; //定义初始状态
struct node s_g = { {1,2,3,8,0,4,7,6,5},1,1,0,0,0,NULL,NULL }; //定义目标状态
struct node *open = NULL;               //建立open表指针
struct node *closed = NULL;             //建立closed表指针
int sum_node = 0;                       //用于记录生成节点总数(含所有)
int sum_new_node = 0;                   //用于记录生成节点总数（仅新生产节点)
int sum_ex_node = 0;                    //用于记录扩展节点总数


//***********************************************************
//**********************               **********************
//**********************   主函数开始  **********************
//**********************               **********************
//***********************************************************

void main()
{
	int bingo = 0;                              //定义查找成功标志，bingo=1，成功
	struct node s;                              //定义头结点s
	struct node *n, *ls, *temp, *same;     //定义结构体指针   *target, 
	Copy_node(&s_0, &s);                              //复制初始状s_0态给头结点s
	Calculate_f(0, &s);                               //计算头结点的代价值
	Add_to_open(&s);                                 //将头结点s放入open表
	while (open != NULL)                                //只要open表不为空，进行以下循环
	{
		n = open;             //n指向open表中当前要扩展的元素
		ls = open->next;
		Add_to_closed(n);
		open = ls;            //将n指向的节点放入closed表中
		if (Test_A_B(n, &s_g))  //当前n指向节点为目标时，跳出程序结束；否则，继续下面的步骤
		{
			bingo = 1;
			break;
		}
		else 
		{ 
			sum_ex_node++;   //该节点需要扩展，扩展计数加1
		}

		//******从下面开始，分别向n的四个方向移动空格，即相当于扩展当前节点的子节点。
		//******生成新的子节点，但是新生成的子节点，并是一定会用于再次扩展新的节点。
		if (n->j_0 >= 1)  //空格所在列号不小于1,可左移
		{
			temp = n->father;
			if (temp != NULL && temp->i_0 == n->i_0&&temp->j_0 - 1 == n->j_0)  //新节点与其祖父节点相同
					;
			else  //新节点与其祖父节点不同，或其父节点为起始节点
			{
				temp = (struct node *)malloc(sizeof(struct node));  //给新节点分配空间
				Copy_node(n, temp);  //拷贝n指向的节点状态
				temp->s[temp->i_0][temp->j_0] = temp->s[temp->i_0][temp->j_0 - 1];  //空格左边的数字右移
				temp->s[temp->i_0][temp->j_0 - 1] = 0;    //空格左移
				temp->j_0--;
				temp->d++;
				Calculate_f(temp->d, temp);       //修改新节点的代价值
				temp->father = n;                //新节点指向其父节点		  
				if (same = Search_A(closed, temp))   //在closed表中找到与新节点状态相同的节点
				{
					if (temp->f < same->f)  //temp指向的节点,其代价比closed表中相同状态节点代价小，加入open表
					{
						Remove_p(closed, same);  //从closed表中删除与temp指向节点状态相同的节点
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else if (same = Search_A(open, temp))  //在open表中找到与新节点状态相同的节点
				{
					if (temp->f < same->f)  //temp指向的节点,其代价比open表中相同状态节点代价小，加入open表
					{
						Remove_p(open, same);  //从open表中删除与temp指向节点状态相同的节点
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else  //新节点为完全不同的新节点，加入open表
				{
					Add_to_open(temp);
					sum_node++;
					sum_new_node++;
				}
			}
		}//end左移

		if (n->j_0 <= 1)  //空格所在列号不大于1,可右移
		{
			temp = n->father;
			if (temp != NULL && temp->i_0 == n->i_0&&temp->j_0 + 1 == n->j_0)  //新节点与其祖父节点相同
				;
			else  //新节点与其祖父节点不同，或其父节点为起始节点
			{
				temp = (struct node *)malloc(sizeof(struct node));  //给新节点分配空间
				Copy_node(n, temp);  //拷贝p指向的节点状态
				temp->s[temp->i_0][temp->j_0] = temp->s[temp->i_0][temp->j_0 + 1];  //空格右移
				temp->s[temp->i_0][temp->j_0 + 1] = 0;
				temp->j_0++;
				temp->d++;
				Calculate_f(temp->d, temp);       //修改新节点的代价值
				temp->father = n;                //新节点指向其父节点
				if (same = Search_A(closed, temp))   //在closed表中找到与新节点状态相同的节点
				{
					if (temp->f < same->f)  //temp指向的节点,其代价比closed表中相同状态节点代价小，加入open表
					{
						Remove_p(closed, same);  //从closed表中删除与temp指向节点状态相同的节点
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else if (same = Search_A(open, temp))  //在open表中找到与新节点状态相同的节点
				{
					if (temp->f < same->f)  //temp指向的节点,其代价比open表中相同状态节点代价小，加入open表
					{
						Remove_p(open, same);  //从open表中删除与temp指向节点状态相同的节点
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else  //新节点为完全不同的新节点，加入open表
				{
					Add_to_open(temp);
					sum_node++;
					sum_new_node++;
				}
			}
		}//end右移
		if (n->i_0 >= 1)  //空格所在列号不小于1,上移
		{
			temp = n->father;
			if (temp != NULL && temp->i_0 == n->i_0 - 1 && temp->j_0 == n->j_0)  //新节点与其祖父节点相同
				;
			else  //新节点与其祖父节点不同，或其父节点为起始节点
			{
				temp = (struct node *)malloc(sizeof(struct node));  //给新节点分配空间
				Copy_node(n, temp);  //拷贝p指向的节点状态
				temp->s[temp->i_0][temp->j_0] = temp->s[temp->i_0 - 1][temp->j_0];  //空格上移
				temp->s[temp->i_0 - 1][temp->j_0] = 0;
				temp->i_0--;
				temp->d++;
				Calculate_f(temp->d, temp);       //修改新节点的代价值
				temp->father = n;                //新节点指向其父节点
				if (same = Search_A(closed, temp))   //在closed表中找到与新节点状态相同的节点
				{
					if (temp->f < same->f)  //temp指向的节点,其代价比closed表中相同状态节点代价小，加入open表
					{
						Remove_p(closed, same);  //从closed表中删除与temp指向节点状态相同的节点
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else if (same = Search_A(open, temp))  //在open表中找到与新节点状态相同的节点
				{
					if (temp->f < same->f)  //temp指向的节点,其代价比open表中相同状态节点代价小，加入open表
					{
						Remove_p(open, same);  //从open表中删除与temp指向节点状态相同的节点
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else  //新节点为完全不同的新节点，加入open表
				{
					Add_to_open(temp);
					sum_node++;
					sum_new_node++;
				}
			}
		}//end上移
		if (n->i_0 <= 1)  //空格所在列号不大于1,下移
		{
			temp = n->father;
			if (temp != NULL && temp->i_0 == n->i_0 + 1 && temp->j_0 == n->j_0)  //新节点与其祖父节点相同
				;
			else  //新节点与其祖父节点不同，或其父节点为起始节点
			{
				temp = (struct node *)malloc(sizeof(struct node));  //给新节点分配空间
				Copy_node(n, temp);  //拷贝p指向的节点状态
				temp->s[temp->i_0][temp->j_0] = temp->s[temp->i_0 + 1][temp->j_0];  //空格下移
				temp->s[temp->i_0 + 1][temp->j_0] = 0;
				temp->i_0++;
				temp->d++;
				Calculate_f(temp->d, temp);       //修改新节点的代价值
				temp->father = n;                //新节点指向其父节点
				if (same = Search_A(closed, temp))   //在closed表中找到与新节点状态相同的节点
				{
					if (temp->f < same->f)  //temp指向的节点,其代价比closed表中相同状态节点代价小，加入open表
					{
						Remove_p(closed, same);  //从closed表中删除与temp指向节点状态相同的节点
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else if (same = Search_A(open, temp))  //在open表中找到与新节点状态相同的节点
				{
					if (temp->f < same->f)  //temp指向的节点,其代价比open表中相同状态节点代价小，加入open表
					{
						Remove_p(open, same);  //从open表中删除与temp指向节点状态相同的节点
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else  //新节点为完全不同的新节点，加入open表
				{
					Add_to_open(temp);
					sum_node++;
					sum_new_node++;
				}
			}
		}//end下移

	}
	if ((bingo = 1) && (n !=NULL)) Print_result(n);   //输出解路径
	else printf("问题求解失败！");

}//主函数结束


//*************************************************************************
//**********************                             **********************
//**********************  计算某个节点状态的代价值   **********************
//**********************                             **********************
//*************************************************************************


void Calculate_f(int deepth, struct node *p)
{
	int i1, j1, m, n, temp1,i2,j2;
	int temp2=0;
	int x[3][3]={1,2,3,8,0,4,7,6,5};
	for(i1=0;i1<3;i1++)
	for(j1=0;j1<3;j1++){
		for(i2=0;i2<3;i2++)
		for(j2=0;j2<3;j2++){
			if(p->s[i1][j1]==x[i2][j2])
			temp2=temp2+abs(i1-i2)+abs(j1-j2);
		}
	}

	p->h = temp2;
	p->f = deepth + p->h;
}



//*************************************************************************
//**********************                             **********************
//**********************  添加p指向的节点到open表中  **********************
//**********************                             **********************
//*************************************************************************

void Add_to_open(struct node *p)
{
	struct node *p1, *p2;
	p1 = open;              //初始时p1指向open表首部
	p2 = NULL;
	if (open == NULL)        //open表为空时，待插入节点即为open表第一个元素，open指向该元素
	{
		p->next = NULL;
		open = p;
	}
	else                   //open表不为空时，添加待插入节点，并保证open表代价递增的排序
	{
		while (p1 != NULL && (p->f > p1->f))
		{
			p2 = p1;         //p2始终指向p1指向的前一个元素
			p1 = p1->next;
		}
		if (p2 == NULL)      //待插入节点为当前open表最小
		{
			p->next = open;
			open = p;
		}
		else if (p1 == NULL)  //待插入节点为当前open表最大
		{
			p->next = NULL;
			p2->next = p;
		}
		else               //待插入节点介于p2、p1之间
		{
			p2->next = p;
			p->next = p1;
		}
	}
}



//***************************************************************************
//**********************                               **********************
//**********************  添加p指向的节点到closed表中  **********************
//**********************                               **********************
//***************************************************************************

void Add_to_closed(struct node *p)
{
	if (closed == NULL)     //closed表为空时，p指向节点为closed表第一个元素，closed指向该元素
	{
		p->next = NULL;
		closed = p;
	}
	else                 //closed表不为空时，直接放到closed表首部
	{
		p->next = closed;
		closed = p;
	}
}


//**************************************************************************************************
//**********************                                                      **********************
//**********************  在open表或closed表中搜索和temp指向的节点相同的节点  **********************
//**********************                                                      **********************
//**************************************************************************************************

struct node * Search_A(struct node *name, struct node *temp)
{
	struct node *p1;
	p1 = name;                  //p1指向open表或closed表
	while (p1 != NULL)
	{
		if (Test_A_B(p1, temp))   //找到相同的节点，返回该节点地址
			return p1;
		else
			p1 = p1->next;
	}
	return NULL;
}



//***********************************************************************************************
//**********************                                                   **********************
//********************** 判断两个节点状态是否相同，相同则返回1，否则返回0  **********************
//**********************                                                   **********************
//***********************************************************************************************

int Test_A_B(struct node *p1, struct node *p2)
{
	int i, j, flag;
	flag = 1;
	for (i = 0; i <= 2; i++)
		for (j = 0; j <= 2; j++)
		{
			if ((p2->s[i][j]) != (p1->s[i][j])) { flag = 0; return flag; }
			else;
		}
	return flag;
}



//******************************************************************************
//**********************                                  **********************
//**********************  从open表或closed表删除指定节点  **********************
//**********************                                  **********************
//******************************************************************************


void Remove_p(struct node *name, struct node *p)
{
	struct node *p1, *p2;
	p1 = NULL;
	p2 = NULL;
	if (name == NULL)                           //如果name指向的链表为空，则不需要进行删除
		return;
	else if (Test_A_B(name, p) && name->f == p->f)    //指定节点为name指向的链表的第一个元素
	{
		p1 = name;
		name = name->next;
		p1->next = NULL;
		return;
	}
	else
	{
		p2 = name;
		p1 = p2->next;
		while (p1)
		{
			if (Test_A_B(p1, p) && p1->f == p->f)   //找到指定节点
			{
				p2->next = p1->next;
				return;
			}
			else
			{
				p2 = p1;              //p2始终指向p1指向的前一个元素
				p1 = p1->next;
			}
		}
		return;
	}
}



//**************************************************************************************
//**********************                                          **********************
//**********************  将p1指向的节点状态拷贝到p2指向的节点中  **********************
//**********************                                          **********************
//**************************************************************************************

void Copy_node(struct node *p1, struct node *p2)
{
	int i, j;
	for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 2; j++)
		{
			p2->s[i][j] = p1->s[i][j];
		}
	}
	p2->i_0 = p1->i_0;
	p2->j_0 = p1->j_0;
	p2->f = p1->f;
	p2->d = p1->d;
	p2->h = p1->h;
	p2->next = p1->next;
	p2->father = p1->father;
}



//***********************************************************
//**********************               **********************
//**********************    输出结果   **********************
//**********************               **********************
//***********************************************************

void Print_result(struct node *p)
{
	struct node *path[100];
	struct node *temp, *temp_father;
	int i, j, k;
	for (i = 0; i <= 99; i++)                   //初始化路径指针数组
		path[i] = 0;
	temp = p;
	printf("总共生成 %d 个节点\n", sum_node);    
	printf("总共生成 %d 个新节点\n", sum_new_node);   
	printf("总共扩展 %d 个节点\n", sum_ex_node);
	printf("总共扩展 %d 层\n", temp->d);
	printf("解路径如下：\n");
	for (i = p->d; i >= 0; i--)                  //存储解路径上各节点的地址
	{
		path[i] = temp;
		temp = temp->father;
	}
	for (k = 0; k <= p->d; k++)                //输出解路径
	{
		temp = path[k];                  //建立节点指点指针
		printf("第%d步 ", temp->d);
		if (k - 1 >= 0)                     //输出移动策略
		{
			temp_father = path[k - 1];
			if (temp->i_0 < temp_father->i_0) printf("->上移\n");
			if (temp->i_0 > temp_father->i_0) printf("->下移\n");
			if (temp->j_0 < temp_father->j_0) printf("->左移\n");
			if (temp->j_0 > temp_father->j_0) printf("->右移\n");
		}
		else
			printf("\n");
		printf("当前节点状态为：\n");
		for (i = 0; i <= 2; i++)
		{
			for (j = 0; j <= 2; j++)
			{
				printf("%d  ", temp->s[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
}
