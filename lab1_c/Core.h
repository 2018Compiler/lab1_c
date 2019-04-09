#pragma once

static char Exception[29][100] = {
	"Exception: the parameter -w should not be used together with -c.",
	"Exception: the filepath of wordlist should be pointed after -w",
	"Exception: the parameter -c should not be used together with -n.",
	"Exception: the parameter -c should not be used together with -w.",
	"Exception: the filepath of wordlist should be pointed after -c",
	"Exception: the start char of word-chain should be pointed after -h",
	"Exception: only one char should be pointed after -h",
	"Exception: parameter after -h should be a single letter.",
	"Exception: the end char of word-chain should be pointed after -t",
	"Exception: only one char should be pointed after -t",
	"Exception: parameter after -t should be a single letter.",
	"Exception: the parameter -n should not be used together with -c.",
	"Exception: the len of word-chain should be pointed after -n",
	"Exception: the len of word-chain should be integer above zero",
	"Exception: contains illegal parameter.",
	"Lack of parameter for searching",
	"Exception: the input file should be a txt file.",
	"Exception: the command should include one of -w or -c.",
	"Exception: the len of word-chain at the result exceeds.",
	"Exception: OVERFLOW",
	"Exception: the number of words in the file is less than n.",
	"Exception: the count of the word-chain with certain len exceeds.",
	"Exception: some word is illegal.",
	"Exception: the actual num of words is less than given.",
	"Exception: open file failed.",
	"Exception: the number of letters in some word exceed.",
	"Exception: the number of words in the inputfile exceeds ",
	"Exception: there is no word in the file.",
	"Exception: output to solution.txt failed.\n",
};

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

	bool isWord(char word[]);

	bool WordList_Test(char *words[],int len);
};

