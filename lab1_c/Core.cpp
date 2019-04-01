#include "Core.h"
#include<iostream>
#include<vector>//给我用来存最长单词链
#include<string.h>
#include"Adjlist_Graph.h"
//#include"in_out.h"

int Core::get_cmd(int argc, char* argv[]) {
	for (int i = 1; i < argc; i += 2)
	{
		if (strcmp(argv[i], "-w") == 0)
		{
			if (most_letter)
			{
				throw("Exception: the parameter -w should not be used together with -c.");
			}
			longest_word = true;
			filepath = argv[i + 1];
		}

		else if (strcmp(argv[i], "-c") == 0)
		{
			if (set_num)
			{
				throw("Exception: the parameter -c should not be used together with -n.");
			}
			if (longest_word)
			{
				throw("Exception: the parameter -c should not be used together with -w.");
			}
			most_letter = true;
			filepath = argv[i + 1];
		}

		else if (strcmp(argv[i], "-h") == 0)
		{
			start_ch = argv[i + 1][0];
			if (strlen(argv[i + 1]) > 1 ||
				((start_ch < 'a' || start_ch > 'z') && (start_ch < 'A' || start_ch > 'Z')))
			{
				throw("Exception: parameter after -h should be a single letter.");
			}
		}
		else if (strcmp(argv[i], "-t") == 0)
		{
			end_ch = argv[i + 1][0];
			if (strlen(argv[i + 1]) > 1 ||
				((end_ch < 'a' || end_ch > 'z') && (end_ch < 'A' || end_ch > 'Z'))) 
			{
				throw("Exception: parameter after -t should be a single letter.");
			}
		}
		else if (strcmp(argv[i], "-n") == 0)
		{
			if (most_letter)
			{
				throw("Exception: the parameter -n should not be used together with -c.");
			}
			set_num = atoi(argv[i + 1]);
			if (set_num <= 0) 
			{
				throw("Exception: parameter after -n should be an integer above zero.");
			}
		}
		else
			throw("Exception: the parameter " , argv[i] , "is illegal.");
	}
	if (strcmp(&filepath[strlen(filepath) - 3], ".txt") != 0) 
	{
		throw("Exception: the input file should be a txt file.");
	}
	if (!(longest_word || most_letter))
	{
		throw("Exception: the command should include one of -w or -c.");
	}
	return 0;
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
	int i;
	for (i = 0; i < graph.longest_word_chain.size(); i++)
	{
		//字符串
		char buf[20];
		string str( graph.longest_word_chain[i]);
		int length = str.copy(buf, 9);
		buf[length] = '\0';
		result[i] = new char[length];
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
	int i;
	for (i = 0; i < graph.longest_word_chain.size(); i++)
	{
		//字符串
		char buf[20];
		string str(graph.longest_word_chain[i]);
		int length = str.copy(buf, 9);
		buf[length] = '\0';
		result[i] = new char[length];
		strcpy(result[i], buf);
	}
	result[i] = NULL;//作为结束标志
	return graph.longest_word_chain.size();
}
int Core::gen_chain_word_certain_num(char* words[], int len, char* result[][100],int &result_chain_count, int num,char head, char tail)
{
	if (len < num)
	{
		printf("the number of words in the file is less than n.\n");
		exit(0);
	}
	if (num > 100)
	{
		printf("there is too many word lists, we can't hold them.\n");
		exit(0);
	}
	Adjlist_Graph graph;
	graph.Create_Graph(words, len);
	graph.head = head;
	graph.tail = tail;
	graph.num_flag = true;
	graph.certain_num = num;

	graph.DFS();
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
			strcpy(result[k][i], buf);
		}
		result[k][i] = NULL;//作为结束标志
	}
	return graph.chain_count;

}
