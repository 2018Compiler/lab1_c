#pragma once
class Core
{
public:

public:
	Core();


	int gen_chain_word(char* words[], int len, char* result[], char head='\0', char tail='\0');

	int gen_chain_char(char* words[], int len, char* result[], char head='\0', char tail='\0');

	int gen_chain_word_certain_num(char* words[], int len, char* result[][100], int &result_chain_count,int num,char head='\0', char tail='\0');

};

