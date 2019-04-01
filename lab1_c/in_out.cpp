#include"in_out.h"
#include<iostream>
#include<set>

using namespace std;
bool In_Out::myisalpha(char &ch)
{
	if (ch <= 'Z' && ch >= 'A')
	{
		ch -= 32;
		return true;
	}
	else if (ch <= 'z' && ch >= 'a')
		return true;
	else
		return false;
}
void In_Out::in(char *filepath)
{
	FILE *fp = fopen(filepath, "r");
	if (!fp)
	{
		printf("open file failed.\n");
		exit(0);
	}
	set<string> readin;
	char ch = fgetc(fp);
	while (!feof(fp))
	{
		while (!myisalpha(ch))
		{
			if (feof(fp))
				return;
			ch = fgetc(fp);

		}

		int k = 0;
		char temp[MAX_WORD_LEN + 1];
		do
		{
			if (k < MAX_WORD_LEN)
			{
				temp[k++] = ch;
			}
			ch = fgetc(fp);
		} while (myisalpha(ch));
		temp[k] = '\0';
		if (readin.insert(temp).second == true)
		{
			words[word_num] = new char[k];
			strcpy(words[word_num], temp);
			word_num++;
		}
			
	}
	if (!word_num)
	{
		printf("there is no word in the file.\n");
		exit(0);
	}
	readin.clear();


}
void In_Out::print_result()
{
	FILE*fp = fopen("./solution.txt", "w");
	if (!fp)
	{
		printf("output to solution.txt failed.\n");
		exit(0);
	}
	for (int i = 0; result[i]; i++)
	{
		fprintf(fp, "%s\n", result[i]);
	}
	fclose(fp);
}
void In_Out::print_result_array()
{
	FILE*fp = fopen("./solution.txt", "w");
	if (!fp)
	{
		printf("output to solution.txt failed.\n");
		exit(0);
	}
	fprintf(fp, "%d\n", chain_count);
	for (int i = 0; i < chain_count; i++)
	{
		for (int j = 0; result_array[i][j]; j++)
		{
			fprintf(fp, "%s\n", result_array[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}


In_Out::In_Out()
{
	word_num = 0;
}


In_Out::~In_Out()
{
}
