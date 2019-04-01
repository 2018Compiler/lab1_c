#include "Adjlist_Graph.h"
#include<string.h>


Adjlist_Graph::Adjlist_Graph()
{
	Vnode_num = VNODE_SIZE;
	Arc_num = 0;
	adjlist = new Vnode[Vnode_num];
	if (!adjlist)
		throw "Exception: OVERFLOW";
	pre_arc = NULL;
	letter_flag = false;
	word_flag = false;
	num_flag = false;

	cur_letter_count = 0;
	max_letter_count = 0;
	chain_count = 0;

}
void Adjlist_Graph::Create_Graph(char *words[], int len)
{
	for (int i = 0; i < Vnode_num; i++)
	{
		adjlist[i].alpha = i+'a';
	}
	for (int i = 0; i < len; i++)
	{
		int j = words[i][0] - 'a';
		ArcNode *p = new ArcNode;
		if (!p)
			throw "Exception: OVERFLOW";
		
		int len=strlen(words[i]);
		p->alpha = words[i][len-1];//应该是作为末字母
		p->lenth = len;
		p->name = new char[p->lenth+1];
		if (!p->name)
			throw "Exception: OVERFLOW";
		strcpy(p->name, words[i]);
		p->visited = false;
		p->NextArc = adjlist[j].FirstArc;
		adjlist[j].FirstArc = p;
	}

}

void Adjlist_Graph::DFS()
{
	for (int i = 0; i < Vnode_num; i++)
	{
		if (adjlist[i].FirstArc)
		{
			if (head != '\0')
			{
				if (i+'a'==head)
				{
					DFS_ArcNode(i);
				}
			}
			else
			{
				DFS_ArcNode(i);
			}
		}

		
	}
}
void Adjlist_Graph::DFS_ArcNode(int i)
{
	ArcNode *tmp = pre_arc;
	for (ArcNode *p = adjlist[i].FirstArc; p; p = p->NextArc)
	{
		if (p->visited == false)
		{
			pre_arc = p;

			p->visited = true;
			word_chain.push_back(p->name);

			if (letter_flag)
				cur_letter_count += p->lenth;

			if (num_flag)
			{
				if (word_chain.size() == certain_num)//回溯是必须的，但保存看有没有tail
				{

					if (tail != '\0')
					{
						if (tail == p->alpha)
						{
							word_chain_array[chain_count++] = word_chain;
						}
					}
					else
					{
						word_chain_array[chain_count++] = word_chain;

					}
					p->visited = false;
					word_chain.pop_back();
				}

				else
				{
					DFS_ArcNode(p->alpha - 'a');
				}

			}

			else
			{
				DFS_ArcNode(p->alpha - 'a');
			}

		}
	}
	pre_arc = tmp;
	if (pre_arc)
	{


		if (word_flag)
		{
			if (word_chain.size() > longest_word_chain.size() && word_chain.size() >= 2)
			{
				if (tail != '\0')
				{
					if (i + 'a' == tail)
						longest_word_chain = word_chain;
				}
				else
				{
					longest_word_chain = word_chain;
				}
			}
		}
		else if (letter_flag)
		{
			if (word_chain.size() >= 2 && cur_letter_count > max_letter_count)
			{
				if (tail != '\0')
				{
					if (i + 'a' == tail)
					{
						longest_word_chain = word_chain;
						max_letter_count = cur_letter_count;
					}

				}
				else
				{
					longest_word_chain = word_chain;
					max_letter_count = cur_letter_count;
				}

			}


		}
		//对于certain_num的情况，直接回溯

		pre_arc->visited = false;
		word_chain.pop_back();
		cur_letter_count -= pre_arc->lenth;
	}
}

Adjlist_Graph::~Adjlist_Graph()
{
	for (int i = 0; i < Vnode_num; i++)
	{
		ArcNode*q, *p;
		for (p = adjlist[i].FirstArc; p; p = q)
		{
			q = p->NextArc;
			delete p->name;
			delete p;
		}
	}
	delete adjlist;
}
