#pragma once
#include"in_out.h"
//用来管理输入输出的函数
#define MAX_WORD_LEN 50


class In_Out
{

public:
	In_Out();

	void in(char *filepath);//从文件中读单词

	bool myisalpha(char &ch);//判断是否是字符，并将大写字符转化为小写

	void print_result();//将单词数或字母数最多的单词链输出

	void print_result_array();//输出特定数目的单词链

	~In_Out();
public:
	char *words[1000];//存放单词
	int  word_num;//单词数量
	char *result[100];//存放单词链
	char *result_array[1000][100];//存放特定数量的单词链
	int chain_count;//单词链的数量（用于-n型）
};

