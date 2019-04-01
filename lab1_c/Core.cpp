#include "Core.h"
#include<iostream>
#include<vector>//给我用来存最长单词链
#include<string.h>
#include"Adjlist_Graph.h"
#include"in_out.h"
Core::Core()
{
	return;
}
int Core:: gen_chain_word(char* words[], int len, char* result[], char head, char tail)
{
	Adjlist_Graph graph;
	graph.Create_Graph(words, len);
	//graph.Show_Graph();
	graph.head = head;
	graph.tail = tail;
	graph.word_flag = true;

	graph.DFS();
	if (graph.longest_word_chain.size() > MAX_CHAIN_LEN)
		throw "Exception: the len of word-chain at the result exceed";
	int i;
	for (i = 0; i < graph.longest_word_chain.size(); i++)
	{
		//字符串
		char buf[20];
		string str( graph.longest_word_chain[i]);
		int length = str.copy(buf, 9);
		buf[length] = '\0';
		result[i] = new char[length];
		if (!result[i])
			throw "Exception: OVERFLOW";
		strcpy(result[i], buf);
	}
	result[i] = NULL;//作为结束标志
	return graph.longest_word_chain.size();
}
int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail)
{
	Adjlist_Graph graph;
	graph.Create_Graph(words, len);
	graph.head = head;
	graph.tail = tail;
	graph.letter_flag = true;

	graph.DFS();
	if(graph.longest_word_chain.size()>MAX_CHAIN_LEN)
		throw "Exception: the len of word-chain at the result exceed";
	int i;
	for (i = 0; i < graph.longest_word_chain.size(); i++)
	{
		//字符串
		char buf[20];
		string str(graph.longest_word_chain[i]);
		int length = str.copy(buf, 9);
		buf[length] = '\0';
		result[i] = new char[length];
		if (!result[i])
			throw "Exception: OVERFLOW";
		strcpy(result[i], buf);
	}
	result[i] = NULL;//作为结束标志
	return graph.longest_word_chain.size();
}
int Core::gen_chain_word_certain_num(char* words[], int len, char* result[][100],int &result_chain_count, int num,char head, char tail)
{
	if (len < num)
	{
		//printf("Exception: the number of words in the file is less than n.\n");
		throw "Exception: the number of words in the file is less than n.";

	}
	if (num > MAX_CHAIN_LEN)
	{
		//printf("there is too many word lists, we can't hold them.\n");
		throw "Exception: the len of word-chain  for searching exceed";
	}
	Adjlist_Graph graph;
	graph.Create_Graph(words, len);
	graph.head = head;
	graph.tail = tail;
	graph.num_flag = true;
	graph.certain_num = num;

	graph.DFS();
	if (graph.chain_count > MAX_CHAIN_COUNT)
		throw "Exception: the count of the word-chain with certain len exceed.";
	result_chain_count = graph.chain_count;
	for (int k = 0; k < graph.chain_count; k++)
	{
		int i;
		for (i = 0; i<graph.word_chain_array[k].size(); i++)
		{
			//字符串
			char buf[20];
			string str(graph.word_chain_array[k][i]);
			int length = str.copy(buf, 9);
			buf[length] = '\0';
			result[k][i] = new char[length];
			if (!result[k][i])
				throw "Exception: OVERFLOW";
			strcpy(result[k][i], buf);
		}
		result[k][i] = NULL;//作为结束标志
	}
	return graph.chain_count;

}
