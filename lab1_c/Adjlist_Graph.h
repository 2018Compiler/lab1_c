#pragma once
#include<iostream>
#include<vector>
using namespace std;
#define VNODE_SIZE 26

struct ArcNode
{
	ArcNode():NextArc(NULL){}//初始化
	char alpha;	//顶点;0-25对应a-z
	char *name; //单词
	int lenth;	//单词长度
	bool visited;
	ArcNode *NextArc;
};

struct Vnode
{
	Vnode():FirstArc(NULL){}//初始化为null
	char alpha;//用来放字母
	ArcNode *FirstArc;
};



 class Adjlist_Graph
{
public:
	Adjlist_Graph();
	void Create_Graph(char *words[], int len);

	void DFS();
	
	void DFS_ArcNode(int i);

	

	~Adjlist_Graph();


public:
	vector<string>longest_word_chain;//已经是初始化为size=0；
	vector<string>word_chain_array[10000];//先是静态的10000个
	char head;
	char tail;
	bool letter_flag;
	bool word_flag;
	bool num_flag;
	int certain_num;
	int chain_count = 0;

private:
	Vnode* adjlist;
	int Vnode_num;
	int Arc_num;
	ArcNode *pre_arc;

	int cur_letter_count;
	int max_letter_count;

	vector<string> word_chain;

 };

