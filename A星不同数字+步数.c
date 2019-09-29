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


struct node // ����8����Ľڵ�״̬ 
{
	int s[3][3]; //��ǰ8�����״̬
	int i_0;   //��ǰ�ո������к�
	int j_0;   //��ǰ�ո������к�
	int f;     //��ǰ����ֵ
	int d;     //��ǰ�ڵ����
	int h;     //������Ϣ����������"����λ"�����
	struct node *father; //ָ���·���ϸýڵ�ĸ��ڵ�
	struct node *next;   //ָ������open��closed���е���һ��Ԫ��
};

struct node s_0 = { {2,0,8,1,5,3,7,4,6},0,1,0,0,0,NULL,NULL }; //�����ʼ״̬
struct node s_g = { {1,2,3,8,0,4,7,6,5},1,1,0,0,0,NULL,NULL }; //����Ŀ��״̬
struct node *open = NULL;               //����open��ָ��
struct node *closed = NULL;             //����closed��ָ��
int sum_node = 0;                       //���ڼ�¼���ɽڵ�����(������)
int sum_new_node = 0;                   //���ڼ�¼���ɽڵ����������������ڵ�)
int sum_ex_node = 0;                    //���ڼ�¼��չ�ڵ�����


//***********************************************************
//**********************               **********************
//**********************   ��������ʼ  **********************
//**********************               **********************
//***********************************************************

void main()
{
	int bingo = 0;                              //������ҳɹ���־��bingo=1���ɹ�
	struct node s;                              //����ͷ���s
	struct node *n, *ls, *temp, *same;     //����ṹ��ָ��   *target, 
	Copy_node(&s_0, &s);                              //���Ƴ�ʼ״s_0̬��ͷ���s
	Calculate_f(0, &s);                               //����ͷ���Ĵ���ֵ
	Add_to_open(&s);                                 //��ͷ���s����open��
	while (open != NULL)                                //ֻҪopen��Ϊ�գ���������ѭ��
	{
		n = open;             //nָ��open���е�ǰҪ��չ��Ԫ��
		ls = open->next;
		Add_to_closed(n);
		open = ls;            //��nָ��Ľڵ����closed����
		if (Test_A_B(n, &s_g))  //��ǰnָ��ڵ�ΪĿ��ʱ������������������򣬼�������Ĳ���
		{
			bingo = 1;
			break;
		}
		else 
		{ 
			sum_ex_node++;   //�ýڵ���Ҫ��չ����չ������1
		}

		//******�����濪ʼ���ֱ���n���ĸ������ƶ��ո񣬼��൱����չ��ǰ�ڵ���ӽڵ㡣
		//******�����µ��ӽڵ㣬���������ɵ��ӽڵ㣬����һ���������ٴ���չ�µĽڵ㡣
		if (n->j_0 >= 1)  //�ո������кŲ�С��1,������
		{
			temp = n->father;
			if (temp != NULL && temp->i_0 == n->i_0&&temp->j_0 - 1 == n->j_0)  //�½ڵ������游�ڵ���ͬ
					;
			else  //�½ڵ������游�ڵ㲻ͬ�����丸�ڵ�Ϊ��ʼ�ڵ�
			{
				temp = (struct node *)malloc(sizeof(struct node));  //���½ڵ����ռ�
				Copy_node(n, temp);  //����nָ��Ľڵ�״̬
				temp->s[temp->i_0][temp->j_0] = temp->s[temp->i_0][temp->j_0 - 1];  //�ո���ߵ���������
				temp->s[temp->i_0][temp->j_0 - 1] = 0;    //�ո�����
				temp->j_0--;
				temp->d++;
				Calculate_f(temp->d, temp);       //�޸��½ڵ�Ĵ���ֵ
				temp->father = n;                //�½ڵ�ָ���丸�ڵ�		  
				if (same = Search_A(closed, temp))   //��closed�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
				{
					if (temp->f < same->f)  //tempָ��Ľڵ�,����۱�closed������ͬ״̬�ڵ����С������open��
					{
						Remove_p(closed, same);  //��closed����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else if (same = Search_A(open, temp))  //��open�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
				{
					if (temp->f < same->f)  //tempָ��Ľڵ�,����۱�open������ͬ״̬�ڵ����С������open��
					{
						Remove_p(open, same);  //��open����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else  //�½ڵ�Ϊ��ȫ��ͬ���½ڵ㣬����open��
				{
					Add_to_open(temp);
					sum_node++;
					sum_new_node++;
				}
			}
		}//end����

		if (n->j_0 <= 1)  //�ո������кŲ�����1,������
		{
			temp = n->father;
			if (temp != NULL && temp->i_0 == n->i_0&&temp->j_0 + 1 == n->j_0)  //�½ڵ������游�ڵ���ͬ
				;
			else  //�½ڵ������游�ڵ㲻ͬ�����丸�ڵ�Ϊ��ʼ�ڵ�
			{
				temp = (struct node *)malloc(sizeof(struct node));  //���½ڵ����ռ�
				Copy_node(n, temp);  //����pָ��Ľڵ�״̬
				temp->s[temp->i_0][temp->j_0] = temp->s[temp->i_0][temp->j_0 + 1];  //�ո�����
				temp->s[temp->i_0][temp->j_0 + 1] = 0;
				temp->j_0++;
				temp->d++;
				Calculate_f(temp->d, temp);       //�޸��½ڵ�Ĵ���ֵ
				temp->father = n;                //�½ڵ�ָ���丸�ڵ�
				if (same = Search_A(closed, temp))   //��closed�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
				{
					if (temp->f < same->f)  //tempָ��Ľڵ�,����۱�closed������ͬ״̬�ڵ����С������open��
					{
						Remove_p(closed, same);  //��closed����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else if (same = Search_A(open, temp))  //��open�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
				{
					if (temp->f < same->f)  //tempָ��Ľڵ�,����۱�open������ͬ״̬�ڵ����С������open��
					{
						Remove_p(open, same);  //��open����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else  //�½ڵ�Ϊ��ȫ��ͬ���½ڵ㣬����open��
				{
					Add_to_open(temp);
					sum_node++;
					sum_new_node++;
				}
			}
		}//end����
		if (n->i_0 >= 1)  //�ո������кŲ�С��1,����
		{
			temp = n->father;
			if (temp != NULL && temp->i_0 == n->i_0 - 1 && temp->j_0 == n->j_0)  //�½ڵ������游�ڵ���ͬ
				;
			else  //�½ڵ������游�ڵ㲻ͬ�����丸�ڵ�Ϊ��ʼ�ڵ�
			{
				temp = (struct node *)malloc(sizeof(struct node));  //���½ڵ����ռ�
				Copy_node(n, temp);  //����pָ��Ľڵ�״̬
				temp->s[temp->i_0][temp->j_0] = temp->s[temp->i_0 - 1][temp->j_0];  //�ո�����
				temp->s[temp->i_0 - 1][temp->j_0] = 0;
				temp->i_0--;
				temp->d++;
				Calculate_f(temp->d, temp);       //�޸��½ڵ�Ĵ���ֵ
				temp->father = n;                //�½ڵ�ָ���丸�ڵ�
				if (same = Search_A(closed, temp))   //��closed�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
				{
					if (temp->f < same->f)  //tempָ��Ľڵ�,����۱�closed������ͬ״̬�ڵ����С������open��
					{
						Remove_p(closed, same);  //��closed����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else if (same = Search_A(open, temp))  //��open�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
				{
					if (temp->f < same->f)  //tempָ��Ľڵ�,����۱�open������ͬ״̬�ڵ����С������open��
					{
						Remove_p(open, same);  //��open����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else  //�½ڵ�Ϊ��ȫ��ͬ���½ڵ㣬����open��
				{
					Add_to_open(temp);
					sum_node++;
					sum_new_node++;
				}
			}
		}//end����
		if (n->i_0 <= 1)  //�ո������кŲ�����1,����
		{
			temp = n->father;
			if (temp != NULL && temp->i_0 == n->i_0 + 1 && temp->j_0 == n->j_0)  //�½ڵ������游�ڵ���ͬ
				;
			else  //�½ڵ������游�ڵ㲻ͬ�����丸�ڵ�Ϊ��ʼ�ڵ�
			{
				temp = (struct node *)malloc(sizeof(struct node));  //���½ڵ����ռ�
				Copy_node(n, temp);  //����pָ��Ľڵ�״̬
				temp->s[temp->i_0][temp->j_0] = temp->s[temp->i_0 + 1][temp->j_0];  //�ո�����
				temp->s[temp->i_0 + 1][temp->j_0] = 0;
				temp->i_0++;
				temp->d++;
				Calculate_f(temp->d, temp);       //�޸��½ڵ�Ĵ���ֵ
				temp->father = n;                //�½ڵ�ָ���丸�ڵ�
				if (same = Search_A(closed, temp))   //��closed�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
				{
					if (temp->f < same->f)  //tempָ��Ľڵ�,����۱�closed������ͬ״̬�ڵ����С������open��
					{
						Remove_p(closed, same);  //��closed����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else if (same = Search_A(open, temp))  //��open�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
				{
					if (temp->f < same->f)  //tempָ��Ľڵ�,����۱�open������ͬ״̬�ڵ����С������open��
					{
						Remove_p(open, same);  //��open����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
						Add_to_open(temp);
						sum_node++;
					}
					else;
				}
				else  //�½ڵ�Ϊ��ȫ��ͬ���½ڵ㣬����open��
				{
					Add_to_open(temp);
					sum_node++;
					sum_new_node++;
				}
			}
		}//end����

	}
	if ((bingo = 1) && (n !=NULL)) Print_result(n);   //�����·��
	else printf("�������ʧ�ܣ�");

}//����������


//*************************************************************************
//**********************                             **********************
//**********************  ����ĳ���ڵ�״̬�Ĵ���ֵ   **********************
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
//**********************  ���pָ��Ľڵ㵽open����  **********************
//**********************                             **********************
//*************************************************************************

void Add_to_open(struct node *p)
{
	struct node *p1, *p2;
	p1 = open;              //��ʼʱp1ָ��open���ײ�
	p2 = NULL;
	if (open == NULL)        //open��Ϊ��ʱ��������ڵ㼴Ϊopen���һ��Ԫ�أ�openָ���Ԫ��
	{
		p->next = NULL;
		open = p;
	}
	else                   //open��Ϊ��ʱ����Ӵ�����ڵ㣬����֤open����۵���������
	{
		while (p1 != NULL && (p->f > p1->f))
		{
			p2 = p1;         //p2ʼ��ָ��p1ָ���ǰһ��Ԫ��
			p1 = p1->next;
		}
		if (p2 == NULL)      //������ڵ�Ϊ��ǰopen����С
		{
			p->next = open;
			open = p;
		}
		else if (p1 == NULL)  //������ڵ�Ϊ��ǰopen�����
		{
			p->next = NULL;
			p2->next = p;
		}
		else               //������ڵ����p2��p1֮��
		{
			p2->next = p;
			p->next = p1;
		}
	}
}



//***************************************************************************
//**********************                               **********************
//**********************  ���pָ��Ľڵ㵽closed����  **********************
//**********************                               **********************
//***************************************************************************

void Add_to_closed(struct node *p)
{
	if (closed == NULL)     //closed��Ϊ��ʱ��pָ��ڵ�Ϊclosed���һ��Ԫ�أ�closedָ���Ԫ��
	{
		p->next = NULL;
		closed = p;
	}
	else                 //closed��Ϊ��ʱ��ֱ�ӷŵ�closed���ײ�
	{
		p->next = closed;
		closed = p;
	}
}


//**************************************************************************************************
//**********************                                                      **********************
//**********************  ��open���closed����������tempָ��Ľڵ���ͬ�Ľڵ�  **********************
//**********************                                                      **********************
//**************************************************************************************************

struct node * Search_A(struct node *name, struct node *temp)
{
	struct node *p1;
	p1 = name;                  //p1ָ��open���closed��
	while (p1 != NULL)
	{
		if (Test_A_B(p1, temp))   //�ҵ���ͬ�Ľڵ㣬���ظýڵ��ַ
			return p1;
		else
			p1 = p1->next;
	}
	return NULL;
}



//***********************************************************************************************
//**********************                                                   **********************
//********************** �ж������ڵ�״̬�Ƿ���ͬ����ͬ�򷵻�1�����򷵻�0  **********************
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
//**********************  ��open���closed��ɾ��ָ���ڵ�  **********************
//**********************                                  **********************
//******************************************************************************


void Remove_p(struct node *name, struct node *p)
{
	struct node *p1, *p2;
	p1 = NULL;
	p2 = NULL;
	if (name == NULL)                           //���nameָ�������Ϊ�գ�����Ҫ����ɾ��
		return;
	else if (Test_A_B(name, p) && name->f == p->f)    //ָ���ڵ�Ϊnameָ�������ĵ�һ��Ԫ��
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
			if (Test_A_B(p1, p) && p1->f == p->f)   //�ҵ�ָ���ڵ�
			{
				p2->next = p1->next;
				return;
			}
			else
			{
				p2 = p1;              //p2ʼ��ָ��p1ָ���ǰһ��Ԫ��
				p1 = p1->next;
			}
		}
		return;
	}
}



//**************************************************************************************
//**********************                                          **********************
//**********************  ��p1ָ��Ľڵ�״̬������p2ָ��Ľڵ���  **********************
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
//**********************    ������   **********************
//**********************               **********************
//***********************************************************

void Print_result(struct node *p)
{
	struct node *path[100];
	struct node *temp, *temp_father;
	int i, j, k;
	for (i = 0; i <= 99; i++)                   //��ʼ��·��ָ������
		path[i] = 0;
	temp = p;
	printf("�ܹ����� %d ���ڵ�\n", sum_node);    
	printf("�ܹ����� %d ���½ڵ�\n", sum_new_node);   
	printf("�ܹ���չ %d ���ڵ�\n", sum_ex_node);
	printf("�ܹ���չ %d ��\n", temp->d);
	printf("��·�����£�\n");
	for (i = p->d; i >= 0; i--)                  //�洢��·���ϸ��ڵ�ĵ�ַ
	{
		path[i] = temp;
		temp = temp->father;
	}
	for (k = 0; k <= p->d; k++)                //�����·��
	{
		temp = path[k];                  //�����ڵ�ָ��ָ��
		printf("��%d�� ", temp->d);
		if (k - 1 >= 0)                     //����ƶ�����
		{
			temp_father = path[k - 1];
			if (temp->i_0 < temp_father->i_0) printf("->����\n");
			if (temp->i_0 > temp_father->i_0) printf("->����\n");
			if (temp->j_0 < temp_father->j_0) printf("->����\n");
			if (temp->j_0 > temp_father->j_0) printf("->����\n");
		}
		else
			printf("\n");
		printf("��ǰ�ڵ�״̬Ϊ��\n");
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
