//在原有的二叉树的基础上创建一个线索二叉树
//只需要修改一下节点的结构并在遍历的过程中对各个节点进行处理就行
//中序，先序线索化二叉树以及按照线索遍历二叉树的代码从262行开始
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

	printf("请按顺序输入节点的双亲，节点以及LR标记值: \n");
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
			Q.push(P);            //将孩子还没有确定的节点入队
								  //孩子还没确定的条件是没有指定右孩子或者开始往深度+1的节点插入节点
		}
		else
		{
			R = Q.front();
			while (strcmp(R->data.name, par.name) != 0)
			{
				Q.pop();   //访问队列，队列中是孩子还没被确定的节点，通过遍历队列来找到对应的双亲节点
						   //if (!Q.empty())
				R = Q.front();//这里有一个问题，此处是按树的深度写入的，
							  //else
							  //fprintf(stderr,"Not found parent.\n");
							  //当开始往下一层加入节点时，上一层的节点不能再被添加孩子，因为如果开始访问下层节点，上层节点已经出队了。
							  //由于双亲节点已经出队，函数找不到双亲节点，会把所有成员出队，最后再用front（）就会访问内存出错.
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
		printf("请按顺序输入节点的双亲，节点以及LR标记值: \n");
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

//定义对二叉树的遍历操作
int PreOrderTravBiTree(BiTree bt)//先序遍历
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

int InOrderTravBiTree(BiTree bt)//中序遍历
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

int PostOrderTravBiTree(BiTree bt)//后序遍历
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

//递归遍历虽然简单易于书写，但是当一个二叉树十分复杂的时候，递归的效率比较低
//所以，当树十分复杂的时候，一般使用非递归的方式对树进行遍历，非递归的遍历方式要用到栈的结构。
int PreOrderTravBiTree_nr(BiTree bt)
{
	stack<BitNode*> S;
	BitNode * p;

	p = bt;
	while (1)//当继续循环的条件为多个而出循环的条件有限时，用这种方式更加方便
	{
		if (!TreeIsEmpty(p))       //如果左孩子右孩子都为空，则将
		{
			printf("%s %d\n", p->data.name, p->data.number);
			S.push(p);               //先（访问）输出当前（双亲）节点，然后将当前（双亲）节点入栈，方便之后访问
			p = p->Lch;				 //然后访问左孩子
		}
		else if (S.empty())
		{
			return 1;
		}
		else            //左孩子访问过（不管是不是空），访问并输出右孩子，为了能够访问右孩子，将双亲节点出栈
		{
			p = S.top();
			S.pop();				 //将已经遍历完的节点出栈
			p = p->Rch;              //访问右孩子，如果右孩子也为空，则将双亲节点的双亲节点出栈
		}
	}
}

int InOrderTravBiTree_nr(BiTree bt)   //其实遍历顺序都是一样的，左右都访问过了，才会访问上一层的，但是输出数据的时间点不同，
									  //先序是双亲节点时输出，中序是先左然后双亲
{
	stack<BitNode *> S;
	BitNode * p;					//怎么看待叶子节点的遍历呢？其实两者也是一样的，由于没有左右孩子，所以输出顺序不重要
									//因为都只能输出当前节点（双亲），只是先序先输出双亲再访问左右，中序先访问左，再访问中

	p = bt;
	while (1)
	{
		if (!TreeIsEmpty(p))
		{
			S.push(p);         //将当前（双亲）节点入栈，但先不输出当前结点
			p = p->Lch;			//先输出左孩子
		}
		else if (S.empty())
			return 1;
		else
		{
			p = S.top();
			S.pop();          //将双亲节点出栈，并输出双亲节点的值
			printf("%s %d\n", p->data.name, p->data.number); //然后输出双亲节点
			p = p->Rch;       //最后输出右孩子
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
			while (p->Rch == NULL || p->Rch == pr)        //当左孩子为空，首先访问右孩子
			{

				//右孩子为空或者右孩子在之前已被输出过,则将双亲出栈，输出双亲
				S.pop();
				printf("%s %d\n", p->data.name, p->data.number);
				pr = p;      //pr用于控制右孩子，因为双亲节点在这个循环中会不断地访问右孩子，如果pr任然是左孩子
							 //则对右孩子进行遍历，右孩子遍历完毕之后，pr=右孩子，此时双亲的右孩子等于pr，
							 //说明右孩子已经输出过了，应该输出双亲了。如果没有pr的判断，就会不断遍历右孩子造成死循环
				if (S.empty())
					return 1;
				p = S.top();
			}
			p = p->Rch;
		}
	}
}


//虽然我们可以得到一棵中序线索化之后的二叉树，但是不代表我们可以轻松地遍历它，因为要按线索遍历
//首先要找到这棵线索二叉树的第一个节点，它显然在大多数情况下不是根节点。
//为了方便中序线索化二叉树进行遍历，我们应该添加一头节点
//令头节点的Lch域指针指向二叉树的根节点，Rch域的指针指向中序遍历时访问的最后一个节点
//同时，令中序遍历的第一个节点的Lch域指向头节点，令中序遍历的最后一个节点的Rch域也指向头节点
//这样一来，既可以沿着头节点顺着后继访问到最后一个节点，也可以沿着前驱访问到第一个节点。
BiTree pre=NULL;     //设置前驱和后继节点。
int InThreading(BiTree &bt)//中序遍历创建线索二叉树,既有前驱又有后继,先序和后序遍历类似
{
	BitNode * p;

	p = bt;
	if (p)
	{
		//if(p->Ltag==Link)
			InThreading(p->Lch);
		if (!p->Lch)                   //为后继节点建立前驱
		{
			p->Ltag = Thread;
			p->Lch = pre;
		}
		if (!p->Rch)
			p->Rtag = Thread;        //只要没有右孩子，不管Rch应该设置成什么，首先置Rtag为Thread,
									 //这是为了防止FindInNext()函数在访问尾节点的时候出错。
		if(pre!=NULL&&!pre->Rch)      //为前驱节点建立后继
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

	T = (BiTree)malloc(sizeof(BitNode)); //为中序遍历创建一个头节点。
	if (!T)
	{
		fprintf(stderr, "OUT OF SPACE!!!\n");
		exit(0);
	}
	//T->Lch = bt;            //头节点的Lch域指针指向根节点（此处不用，先序遍历头节点才这样写）
	p = bt;										//将中序遍历第一个节点的Lch域指向头节点
	while (p->Lch)
		p = GetLeftChild(p);
	p->Lch = T;
	T->Lch = p;
	p = bt;										//将中序遍历的最后一个节点的Rch域指向头节点
	while (p->Rch)
		p = GetRightChild(p);
	T->Rch = p;
	p->Rch = T;

	return T;
}

int PreThreading(BiTree &bt)            //先序遍历创建线索二叉树
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
		if(pre!=NULL&&!pre->Rch)          //一定不能访问空的pre！！！！！！！！！！！！
										//此处访问空的pre内存肯定会出错！！！
		{
			pre->Rtag = Thread;
			pre->Rch = p;
		}
		pre = p;
		if(p->Ltag==Link)              //这个判断也不能少，为什么？不再遍历重复节点？
			PreThreading(p->Lch);
		if(p->Rtag==Link)              
			PreThreading(p->Rch);
	}

	return 1;
}

//先序遍历下的线索二叉树的求p的后继的操作
BitNode * FindPreNext(BiTree &p,BiTree &Q)
{
	if (p->Ltag == Thread)
		Q = p->Rch;
	else
		Q = p->Lch;

	return Q;
}

//中序遍历下求后继的操作
BitNode * FindInNext(BiTree &p,BiTree & Q)
{
	if (p->Rtag == Thread)
		Q = p->Rch;
	else
	{
		Q = p->Rch;
		while (Q->Ltag != Thread)         //访问这里会出现内存访问错误，因为之前创建线索的时候
										//并没有把最后节点的Rtag设置为Thread，导致了访问空节点的Ltag
										//所以会出错（已解决）
			Q = Q->Lch;
	}

	return Q;
}

//利用线索二叉树顺序遍历二叉树
int PreThreadTrav(BiTree bt)
{
	BitNode * p, *Q = NULL;       //记住Q要初始化，不能将没有初始化的指针传入函数。

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
	PreThreading(BT);               //前序线索化二叉树，只能分别测试，你不能同时先序中序线索化一棵树。
	PreThreadTrav(BT);			  //前序遍历前序线索二叉树
	//InThreading(BT);				  //中序线索化二叉树
	//InHead = CreateInThreadHead(BT);
	//InThreadTrav(InHead->Lch,InHead);		  //中序遍历中序线索二叉树

	return 0;
}



//还要补充的问题：
//前序线索和中序线索的头节点的定义是不同的（对头节点的改进）？（已解决）
//L->Tlag==Link这个判断的作用？中序没有问题，但是先序有问题,用调试来看这个问题（未解决）？
//遍历线索的开始和结束条件？（已解决）