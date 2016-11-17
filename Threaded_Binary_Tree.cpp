//��ԭ�еĶ������Ļ����ϴ���һ������������
//ֻ��Ҫ�޸�һ�½ڵ�Ľṹ���ڱ����Ĺ����жԸ����ڵ���д������
//���������������������Լ��������������������Ĵ����262�п�ʼ
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <queue>
#include <stack>
using namespace std;
#define TRUE 1
#define FALSE 0
enum PointerTag {Link,Thread};
typedef struct TElemType
{
	char name[20];
	int number;
}TElemType;
typedef struct BitNode
{
	TElemType data;
	struct BitNode *Lch, *Rch;
	PointerTag Ltag, Rtag;
}BitNode, *BiTree;

int ElemIsEmpty(TElemType &e)
{
	if (strcmp(e.name, "NULL") == 0 && e.number == 0)
		return TRUE;
	else
		return FALSE;
}

BiTree N_CreateBiTree()
{
	queue<BitNode*> Q;
	BitNode *P = NULL, *R = NULL;
	BiTree bt;
	TElemType par, data;
	char LR;
	bt = NULL;

	printf("�밴˳������ڵ��˫�ף��ڵ��Լ�LR���ֵ: \n");
	scanf("%s %d", par.name, &par.number);
	scanf("%s %d", data.name, &data.number);
	scanf(" %c", &LR);
	while (LR != 'L'&&LR != 'R')
		scanf(" %c", &LR);
	while (!ElemIsEmpty(data))
	{
		P = (BitNode*)malloc(sizeof(BitNode));
		strcpy(P->data.name, data.name);
		P->data.number = data.number;
		P->Lch = NULL;
		P->Rch = NULL;
		P->Ltag = Link;
		P->Rtag = Link;
		if (ElemIsEmpty(par))
		{
			bt = P;
			Q.push(P);            //�����ӻ�û��ȷ���Ľڵ����
								  //���ӻ�ûȷ����������û��ָ���Һ��ӻ��߿�ʼ�����+1�Ľڵ����ڵ�
		}
		else
		{
			R = Q.front();
			while (strcmp(R->data.name, par.name) != 0)
			{
				Q.pop();   //���ʶ��У��������Ǻ��ӻ�û��ȷ���Ľڵ㣬ͨ�������������ҵ���Ӧ��˫�׽ڵ�
						   //if (!Q.empty())
				R = Q.front();//������һ�����⣬�˴��ǰ��������д��ģ�
							  //else
							  //fprintf(stderr,"Not found parent.\n");
							  //����ʼ����һ�����ڵ�ʱ����һ��Ľڵ㲻���ٱ���Ӻ��ӣ���Ϊ�����ʼ�����²�ڵ㣬�ϲ�ڵ��Ѿ������ˡ�
							  //����˫�׽ڵ��Ѿ����ӣ������Ҳ���˫�׽ڵ㣬������г�Ա���ӣ��������front�����ͻ�����ڴ����.
			}
			if (LR == 'L')
			{
				R->Lch = P;
			}
			else
			{
				R->Rch = P;
				Q.pop();
			}
			Q.push(P);
		}
		printf("�밴˳������ڵ��˫�ף��ڵ��Լ�LR���ֵ: \n");
		scanf("%s %d", par.name, &par.number);
		scanf("%s %d", data.name, &data.number);
		scanf(" %c", &LR);
		while (LR != 'L'&&LR != 'R')
			scanf(" %c", &LR);

	}

	return bt;
}

int TreeIsEmpty(BiTree bt)
{
	if (bt == NULL)
		return 1;
	else if (bt->data.name == "NULL"&&bt->data.number == 0)
		return 1;
	else
		return 0;
}

BiTree GetLeftChild(BiTree &bt)
{
	if (bt == NULL)
		return NULL;
	else
		return bt->Lch;
}

BiTree GetRightChild(BiTree &bt)
{
	if (bt == NULL)
		return NULL;
	else
		return bt->Rch;
}

//����Զ������ı�������
int PreOrderTravBiTree(BiTree bt)//�������
{
	if (TreeIsEmpty(bt))
		return 1;
	else
	{
		printf("%s ", bt->data.name);
		printf("%d\n", bt->data.number);
		PreOrderTravBiTree(bt->Lch);
		PreOrderTravBiTree(bt->Rch);
	}
}

int InOrderTravBiTree(BiTree bt)//�������
{
	if (TreeIsEmpty(bt))
		return 1;
	else
	{
		InOrderTravBiTree(bt->Lch);
		printf("%s %d\n", bt->data.name, bt->data.number);
		InOrderTravBiTree(bt->Rch);
	}
}

int PostOrderTravBiTree(BiTree bt)//�������
{
	if (TreeIsEmpty(bt))
		return 1;
	else
	{
		PostOrderTravBiTree(bt->Lch);
		PostOrderTravBiTree(bt->Rch);
		printf("%s %d\n", bt->data.name, bt->data.number);
	}
}

//�ݹ������Ȼ��������д�����ǵ�һ��������ʮ�ָ��ӵ�ʱ�򣬵ݹ��Ч�ʱȽϵ�
//���ԣ�����ʮ�ָ��ӵ�ʱ��һ��ʹ�÷ǵݹ�ķ�ʽ�������б������ǵݹ�ı�����ʽҪ�õ�ջ�Ľṹ��
int PreOrderTravBiTree_nr(BiTree bt)
{
	stack<BitNode*> S;
	BitNode * p;

	p = bt;
	while (1)//������ѭ��������Ϊ�������ѭ������������ʱ�������ַ�ʽ���ӷ���
	{
		if (!TreeIsEmpty(p))       //��������Һ��Ӷ�Ϊ�գ���
		{
			printf("%s %d\n", p->data.name, p->data.number);
			S.push(p);               //�ȣ����ʣ������ǰ��˫�ף��ڵ㣬Ȼ�󽫵�ǰ��˫�ף��ڵ���ջ������֮�����
			p = p->Lch;				 //Ȼ���������
		}
		else if (S.empty())
		{
			return 1;
		}
		else            //���ӷ��ʹ��������ǲ��ǿգ������ʲ�����Һ��ӣ�Ϊ���ܹ������Һ��ӣ���˫�׽ڵ��ջ
		{
			p = S.top();
			S.pop();				 //���Ѿ�������Ľڵ��ջ
			p = p->Rch;              //�����Һ��ӣ�����Һ���ҲΪ�գ���˫�׽ڵ��˫�׽ڵ��ջ
		}
	}
}

int InOrderTravBiTree_nr(BiTree bt)   //��ʵ����˳����һ���ģ����Ҷ����ʹ��ˣ��Ż������һ��ģ�����������ݵ�ʱ��㲻ͬ��
									  //������˫�׽ڵ�ʱ���������������Ȼ��˫��
{
	stack<BitNode *> S;
	BitNode * p;					//��ô����Ҷ�ӽڵ�ı����أ���ʵ����Ҳ��һ���ģ�����û�����Һ��ӣ��������˳����Ҫ
									//��Ϊ��ֻ�������ǰ�ڵ㣨˫�ף���ֻ�����������˫���ٷ������ң������ȷ������ٷ�����

	p = bt;
	while (1)
	{
		if (!TreeIsEmpty(p))
		{
			S.push(p);         //����ǰ��˫�ף��ڵ���ջ�����Ȳ������ǰ���
			p = p->Lch;			//���������
		}
		else if (S.empty())
			return 1;
		else
		{
			p = S.top();
			S.pop();          //��˫�׽ڵ��ջ�������˫�׽ڵ��ֵ
			printf("%s %d\n", p->data.name, p->data.number); //Ȼ�����˫�׽ڵ�
			p = p->Rch;       //�������Һ���
		}
	}
}

int PostOrderTravBiTree_nr(BiTree bt)
{
	stack<BitNode *> S;
	BitNode *p, *pr = NULL;

	p = bt;
	while (1)
	{
		if (!TreeIsEmpty(p))
		{
			S.push(p);
			p = p->Lch;
		}
		else
		{
			if (S.empty())
				return 1;
			p = S.top();
			while (p->Rch == NULL || p->Rch == pr)        //������Ϊ�գ����ȷ����Һ���
			{

				//�Һ���Ϊ�ջ����Һ�����֮ǰ�ѱ������,��˫�׳�ջ�����˫��
				S.pop();
				printf("%s %d\n", p->data.name, p->data.number);
				pr = p;      //pr���ڿ����Һ��ӣ���Ϊ˫�׽ڵ������ѭ���л᲻�ϵط����Һ��ӣ����pr��Ȼ������
							 //����Һ��ӽ��б������Һ��ӱ������֮��pr=�Һ��ӣ���ʱ˫�׵��Һ��ӵ���pr��
							 //˵���Һ����Ѿ�������ˣ�Ӧ�����˫���ˡ����û��pr���жϣ��ͻ᲻�ϱ����Һ��������ѭ��
				if (S.empty())
					return 1;
				p = S.top();
			}
			p = p->Rch;
		}
	}
}


//��Ȼ���ǿ��Եõ�һ������������֮��Ķ����������ǲ��������ǿ������ɵر���������ΪҪ����������
//����Ҫ�ҵ���������������ĵ�һ���ڵ㣬����Ȼ�ڴ��������²��Ǹ��ڵ㡣
//Ϊ�˷����������������������б���������Ӧ�����һͷ�ڵ�
//��ͷ�ڵ��Lch��ָ��ָ��������ĸ��ڵ㣬Rch���ָ��ָ���������ʱ���ʵ����һ���ڵ�
//ͬʱ������������ĵ�һ���ڵ��Lch��ָ��ͷ�ڵ㣬��������������һ���ڵ��Rch��Ҳָ��ͷ�ڵ�
//����һ�����ȿ�������ͷ�ڵ�˳�ź�̷��ʵ����һ���ڵ㣬Ҳ��������ǰ�����ʵ���һ���ڵ㡣
BiTree pre=NULL;     //����ǰ���ͺ�̽ڵ㡣
int InThreading(BiTree &bt)//���������������������,����ǰ�����к��,����ͺ����������
{
	BitNode * p;

	p = bt;
	if (p)
	{
		//if(p->Ltag==Link)
			InThreading(p->Lch);
		if (!p->Lch)                   //Ϊ��̽ڵ㽨��ǰ��
		{
			p->Ltag = Thread;
			p->Lch = pre;
		}
		if (!p->Rch)
			p->Rtag = Thread;        //ֻҪû���Һ��ӣ�����RchӦ�����ó�ʲô��������RtagΪThread,
									 //����Ϊ�˷�ֹFindInNext()�����ڷ���β�ڵ��ʱ�����
		if(pre!=NULL&&!pre->Rch)      //Ϊǰ���ڵ㽨�����
		{
			pre->Rtag = Thread;
			pre->Rch = p;
		}
		pre = p;
		//if(p->Rtag==Link)
			InThreading(p->Rch);
	}
	
	return 1;
}

BiTree CreateInThreadHead(BiTree &bt)
{
	BitNode * p, *T;

	T = (BiTree)malloc(sizeof(BitNode)); //Ϊ�����������һ��ͷ�ڵ㡣
	if (!T)
	{
		fprintf(stderr, "OUT OF SPACE!!!\n");
		exit(0);
	}
	//T->Lch = bt;            //ͷ�ڵ��Lch��ָ��ָ����ڵ㣨�˴����ã��������ͷ�ڵ������д��
	p = bt;										//�����������һ���ڵ��Lch��ָ��ͷ�ڵ�
	while (p->Lch)
		p = GetLeftChild(p);
	p->Lch = T;
	T->Lch = p;
	p = bt;										//��������������һ���ڵ��Rch��ָ��ͷ�ڵ�
	while (p->Rch)
		p = GetRightChild(p);
	T->Rch = p;
	p->Rch = T;

	return T;
}

int PreThreading(BiTree &bt)            //���������������������
{
	BitNode * p;

	p = bt;
	if (p)
	{
		if (!p->Lch)
		{
			p->Ltag = Thread;
			p->Lch = pre;
		}
		if(pre!=NULL&&!pre->Rch)          //һ�����ܷ��ʿյ�pre������������������������
										//�˴����ʿյ�pre�ڴ�϶����������
		{
			pre->Rtag = Thread;
			pre->Rch = p;
		}
		pre = p;
		if(p->Ltag==Link)              //����ж�Ҳ�����٣�Ϊʲô�����ٱ����ظ��ڵ㣿
			PreThreading(p->Lch);
		if(p->Rtag==Link)              
			PreThreading(p->Rch);
	}

	return 1;
}

//��������µ���������������p�ĺ�̵Ĳ���
BitNode * FindPreNext(BiTree &p,BiTree &Q)
{
	if (p->Ltag == Thread)
		Q = p->Rch;
	else
		Q = p->Lch;

	return Q;
}

//������������̵Ĳ���
BitNode * FindInNext(BiTree &p,BiTree & Q)
{
	if (p->Rtag == Thread)
		Q = p->Rch;
	else
	{
		Q = p->Rch;
		while (Q->Ltag != Thread)         //�������������ڴ���ʴ�����Ϊ֮ǰ����������ʱ��
										//��û�а����ڵ��Rtag����ΪThread�������˷��ʿսڵ��Ltag
										//���Ի�����ѽ����
			Q = Q->Lch;
	}

	return Q;
}

//��������������˳�����������
int PreThreadTrav(BiTree bt)
{
	BitNode * p, *Q = NULL;       //��סQҪ��ʼ�������ܽ�û�г�ʼ����ָ�봫�뺯����

	p = bt;
	while (p)
	{
		printf("%s %d\n",p->data.name,p->data.number);
		p = FindPreNext(p,Q);
	}

	return 1;
}

int InThreadTrav(BiTree bt,BiTree thrhead)
{
	BitNode *p,*Q=NULL;
	
	p = bt;
	while (p!=thrhead)
	{
		printf("%s %d\n",p->data.name,p->data.number);
		p = FindInNext(p,Q);  
	}

	return 1;
}


int main()
{
	BiTree BT;
	BiTree InHead;

	BT = N_CreateBiTree();
	PreThreading(BT);               //ǰ����������������ֻ�ֱܷ���ԣ��㲻��ͬʱ��������������һ������
	PreThreadTrav(BT);			  //ǰ�����ǰ������������
	//InThreading(BT);				  //����������������
	//InHead = CreateInThreadHead(BT);
	//InThreadTrav(InHead->Lch,InHead);		  //���������������������

	return 0;
}



//��Ҫ��������⣺
//ǰ������������������ͷ�ڵ�Ķ����ǲ�ͬ�ģ���ͷ�ڵ�ĸĽ��������ѽ����
//L->Tlag==Link����жϵ����ã�����û�����⣬��������������,�õ�������������⣨δ�������
//���������Ŀ�ʼ�ͽ������������ѽ����