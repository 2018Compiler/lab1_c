#include"in_out.h"
#include"Adjlist_Graph.h"
#include"Core.h"
using namespace std;
int main(int argc,char *argv[])
{
	try {
		//int a[10];
		//cout << a[10000];
		Core core;
		char *tmp[3];
		tmp[0] = new char[10];
		strcpy(tmp[0], "apple");
		tmp[1] = new char[10];
		strcpy(tmp[1], "egg");
		tmp[2] = new char[10];
		strcpy(tmp[2], "god");
		//tmp[3] = NULL;
		char *result[100];
		core.gen_chain_word(tmp, 6, result);
		for (int i = 0; result[i]; i++)
			cout << result[i] << endl;
	}

	//	In_Out begin;
	//	Core core;
	//	core.get_cmd(argc, argv);
	//	begin.in(core.filepath);
	//	if (core.longest_word)
	//	{
	//		core.gen_chain_word(begin.words, begin.word_num, begin.result, core.start_ch, core.end_ch);
	//		begin.print_result();
	//	}
	//	else if (core.most_letter)
	//	{
	//		core.gen_chain_char(begin.words, begin.word_num, begin.result, core.start_ch, core.end_ch);
	//		begin.print_result();
	//	}
	//	else if (core.set_num > 0)
	//	{
	//		core.gen_chain_word_certain_num(begin.words, begin.word_num, begin.result_array,begin.chain_count,core.set_num,core.start_ch, core.end_ch);
	//		begin.print_result_array();
	//	}
	//	
	//}
	catch (const int msg)
	{
		throw Exception[msg];
	}


}
