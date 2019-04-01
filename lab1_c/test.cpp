#include"in_out.h"
#include"Adjlist_Graph.h"
#include"Core.h"
using namespace std;
int main(int argc,char *argv[])
{
	try {
		In_Out begin;
		Core core;
		core.get_cmd(argc, argv);
		begin.in(core.filepath);
		if (core.longest_word)
		{
			core.gen_chain_word(begin.words, begin.word_num, begin.result, core.start_ch, core.end_ch);
			begin.print_result();
		}
		else if (core.most_letter)
		{
			core.gen_chain_char(begin.words, begin.word_num, begin.result, core.start_ch, core.end_ch);
			begin.print_result();
		}
		else if (core.set_num > 0)
		{
			core.gen_chain_word_certain_num(begin.words, begin.word_num, begin.result_array,begin.chain_count,core.set_num,core.start_ch, core.end_ch);
			begin.print_result_array();
		}
		
	}
	catch (const char *msg)
	{
		cerr << msg << endl;
	}


}
