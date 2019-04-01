#pragma once
class Core
{
public:
	bool longest_word = false, most_letter = false;
	char* filepath = nullptr, start_ch = 0, end_ch = 0;
	int set_num = 0;

public:
	int get_cmd(int argc, char* argv[]);

	int gen_chain_word(char* words[], int len, char* result[], char head='\0', char tail='\0');

	int gen_chain_char(char* words[], int len, char* result[], char head='\0', char tail='\0');

	int gen_chain_word_certain_num(char* words[], int len, char* result[][100], int &result_chain_count,int num,char head='\0', char tail='\0');

};

