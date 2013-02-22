#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 31000
#define RED 1
#define BLACK -1
void Left_Rotate(int);
void Right_Rotate(int);
void Rb_Insert(int);
void Rb_Insert_Fixup(int);
typedef struct
{
	int key;
	int lsize, rsize;
	int left, right;
	int p;
	int color;
}Rb_Tree;
typedef struct
{
	int root;
	int nil;
}Rb_Guard;
Rb_Tree tr[MAXN];
Rb_Guard T;
void Left_Rotate(int x)
{
	int y = tr[x].right;
	tr[x].right = tr[y].left;
	if(tr[y].left != T.nil)
		tr[tr[y].left].p = x;
	tr[y].p = tr[x].p;
	if(tr[x].p == T.nil)
		T.root = y;
	else if(x == tr[tr[x].p].left)
		tr[tr[x].p].left = y;
	else
		tr[tr[x].p].right = y;
	tr[y].left = x;
	tr[x].p = y;
	tr[x].rsize = tr[tr[x].right].lsize + tr[tr[x].right].rsize;
	tr[y].lsize = tr[tr[y].left].lsize + tr[tr[y].left].rsize + 1;
}
void Right_Rotate(int x)
{
	int y = tr[x].left;
	tr[x].left = tr[y].right;
	if(tr[y].right != T.nil)
		tr[tr[y].right].p = x;
	tr[y].p = tr[x].p;
	if(tr[x].p == T.nil)
		T.root = y;
	else if(x == tr[tr[x].p].right)
		tr[tr[x].p].right = y;
	else
		tr[tr[x].p].left = y;
	tr[y].right = x;
	tr[x].p = y;
	tr[x].lsize = tr[tr[x].left].lsize + tr[tr[x].left].rsize + 1;
	tr[y].rsize = tr[tr[y].right].lsize + tr[tr[y].right].rsize;
}
void Rb_Insert(int z)
{
	int y = T.nil, x = T.root;
	while(x != T.nil)
	{
		y = x;
		if(tr[z].key < tr[x].key)
			tr[x].lsize ++, x = tr[x].left;
		else
			tr[x].rsize ++, x = tr[x].right;
	}
	tr[z].p = y;
	if(y == T.nil)
		T.root = z;
	else if(tr[z].key < tr[y].key)
		tr[y].left = z;
	else
		tr[y].right = z;
	tr[z].left = tr[z].right = T.nil;
	tr[z].color = RED;
	Rb_Insert_Fixup(z);
}
void Rb_Insert_Fixup(int z)
{
	int y;
	while(tr[tr[z].p].color == RED)
	{
		if(tr[z].p == tr[tr[tr[z].p].p].left)
		{
			y = tr[tr[tr[z].p].p].right;
			if(tr[y].color == RED)
			{
				tr[tr[z].p].color = BLACK;
				tr[y].color = BLACK;
				tr[tr[tr[z].p].p].color = RED;
				z = tr[tr[z].p].p;
			}
			else 
			{
				if(z == tr[tr[z].p].right)
				{
					z = tr[z].p;
					Left_Rotate(z);
				}
				tr[tr[z].p].color = BLACK;
				tr[tr[tr[z].p].p].color = RED;
				Right_Rotate(tr[tr[z].p].p);
			}
		}
		else
		{
			y = tr[tr[tr[z].p].p].left;
			if(tr[y].color == RED)
			{
				tr[tr[z].p].color = BLACK;
				tr[y].color = BLACK;
				tr[tr[tr[z].p].p].color = RED;
				z = tr[tr[z].p].p;
			}
			else 
			{
				if(z == tr[tr[z].p].left)
				{
					z = tr[z].p;
					Right_Rotate(z);
				}
				tr[tr[z].p].color = BLACK;
				tr[tr[tr[z].p].p].color = RED;
				Left_Rotate(tr[tr[z].p].p);
			}
		}
	}
	tr[T.root].color = BLACK;
}
int Rb_Find(int nth)
{
	int site = T.root, sum = tr[T.root].lsize;
	while(sum != nth)
	{
		if(sum > nth)
			site = tr[site].left, sum -= tr[site].rsize + 1;
		else
			site = tr[site].right, sum += tr[site].lsize;
	}
	return tr[site].key;
}