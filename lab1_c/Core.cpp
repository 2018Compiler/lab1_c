#include "Core.h"
#include<iostream>
#include<vector>//给我用来存最长单词链
#include<string.h>
#include"Adjlist_Graph.h"
#include"in_out.h"

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
			if (i + 1 >= argc)
			{
				throw "Exception: the filepath of wordlist should be pointed after -w";
			}
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
			if (i + 1 >= argc)
			{
				throw "Exception: the filepath of wordlist should be pointed after -c";
			}
			filepath = argv[i + 1];
		}

		else if (strcmp(argv[i], "-h") == 0)
		{
			if (i + 1 >= argc)
			{
				throw "Exception: the start char of word-chain should be pointed after -h";
			}
			if (strlen(argv[i + 1]) > 1)
			{
				throw "Exception: only one char should be pointed after -h";
			}
			start_ch = argv[i + 1][0];
			if (strlen(argv[i + 1]) > 1 ||
				((start_ch < 'a' || start_ch > 'z') && (start_ch < 'A' || start_ch > 'Z')))
			{
				throw("Exception: parameter after -h should be a single letter.");
			}
		}
		else if (strcmp(argv[i], "-t") == 0)
		{
			if (i + 1 >= argc)
			{
				throw "Exception: the end char of word-chain should be pointed after -t";
			}
			if (strlen(argv[i + 1]) > 1)
			{
				throw "Exception: only one char should be pointed after -t";
			}
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
			if (i + 1 >= argc)
			{
				throw "Exception: the len of word-chain should be pointed after -n";
			}
			else
			{
				for (int j = 0; j < strlen(argv[i + 1]); j++)
				{
					if(argv[i+1][j]<'0'||argv[i+1][j]>'9')
						throw "Exception: the len of word-chain should be integer above zero";
				}
				set_num = atoi(argv[i + 1]);

			}

		}
		else
			throw("Exception: the parameter ", argv[i], "is illegal.");
	}

	if (argc <= 1)
	{
		throw "Lack of parameter for searching";
	}
	if (strlen(filepath) < 4||strcmp(&filepath[strlen(filepath) - 4], ".txt") != 0)
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
	if (WordList_Test(words, len))
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

}
int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail)
{
	if (WordList_Test(words, len))
	{
		Adjlist_Graph graph;
		graph.Create_Graph(words, len);
		graph.head = head;
		graph.tail = tail;
		graph.letter_flag = true;

		graph.DFS();
		if (graph.longest_word_chain.size() > MAX_CHAIN_LEN)
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
	
}
int Core::gen_chain_word_certain_num(char* words[], int len, char* result[][100],int &result_chain_count, int num,char head, char tail)
{
	if (WordList_Test(words, len))
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
			throw "Exception: the count of the word-chain with certain len exceeds.";
		result_chain_count = graph.chain_count;
		for (int k = 0; k < graph.chain_count; k++)
		{
			int i;
			for (i = 0; i < graph.word_chain_array[k].size(); i++)
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
	
}
bool Core::isWord(char word[])
{
	for (int i = 0; word[i]; i++)
	{
		if (word[i]<'A' || (word[i] > 'Z'&&word[i] < 'a') || word[i]>'z')
			return false;
		else if (word[i] >= 'A'&&word[i] <= 'Z')
		{
			word[i] = 'a' + word[i] - 'A';
		}
	}
	return true;
}
bool Core::WordList_Test(char *words[], int len)
{
	int i=0;
	char tmp[100];
	sprintf(tmp, "%p", words[i]);
	for ( i = 0; strcmp(tmp,"CCCCCCCC")!=0&&i<len; i++)
		//目前只能做得这么狼狈，而且还不保证在你们的机器上会不会是这样，因为因为当这个单词不存在的时候它的指针不是NULL，我也不知道为什么，它的值反而是CCCCCCCC,所以在不同的机器上，这个末尾的判断可能不一样。									
	{
		sprintf(tmp, "%p", words[i]);
		//cout << tmp << endl;
		//printf("%p  :  %p \n", &words[i],words[i]);
		if (!isWord(words[i]))
		{
			throw"Exception: some word is illegal.";
			return false;
		}
		sprintf(tmp, "%p", words[i+1]);
			
	}
	if (i < len)
	{
		throw"Exception: the actual num of words is less than given.";
		return false;
	}
	return true;
}
