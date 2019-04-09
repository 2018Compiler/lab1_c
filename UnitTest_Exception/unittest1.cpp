#include "stdafx.h"
#include "CppUnitTest.h"
#include "../lab1_c/Core.h"
#include "../lab1_c/in_out.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct sample {
	char *word[100];
	int word_len;
	char start_ch;
	char end_ch;
	int set_num;
	int expected_return_value;
};

namespace UnitTestWordlist
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(gen_chain_word)
		{
			// TODO: �ڴ�������Դ���
			sample sample_list[5] = { 
				// ���Ա߽�����, ���еĵ��ʶ��ܹ������
				{ { "elf", "erase", "asdf", "fdsa", "aquire", }, 5, 0, 0, 0, 5 } ,
				// ��һ������������, ��ָ������ĸ
				{ { "elf", "asdf", "erase", "aquire", "fdsa",  }, 5, 'a', 0, 0, 5 } ,
				// ָ��ĩ��ĸ
				{ { "elf", "erase", "asdf", "fdsa", "aquire", }, 5, 0, 'f', 0, 5 } ,
				// ָ����ĩ��ĸ
				{ { "elf", "erase", "asdf", "fdsa", "aquire", }, 5, 'a', 'e', 0, 4 } ,
				{ {"ab", "cd", "ef", "gh"}, 4, 0, 0, 0, 0},
			};

			// ���Կ�ʼ
			for (int i = 0; i < sizeof(sizeof(sample_list) / sizeof(sample_list[0])); i++) {
				char **word = sample_list[i].word, *result[100] = { 0 }, start_ch = sample_list[i].start_ch, end_ch = sample_list[i].end_ch;
				int expect_len = sample_list[i].expected_return_value; 
				int word_len = sample_list[i].word_len;

				Core core_test = Core();
				int real_len = core_test.gen_chain_word(word, word_len, result, start_ch, end_ch);
				char last_tail;
				// ���Գ���
				Assert::AreEqual(expect_len, real_len);

				//������β��ӵĺϷ���
				for (int i = 0; i < real_len; i++) {
					if (i > 0)
						Assert::AreEqual(last_tail, result[i][0]);
					last_tail = result[i][strlen(result[i]) - 1];
				}

				//����ָ����λ��ĸ������µĺϷ���
				if (start_ch && real_len > 0)
					Assert::AreEqual(start_ch, result[0][0]);
				if (end_ch && real_len > 0)
					Assert::AreEqual(end_ch, result[real_len - 1][strlen(result[real_len - 1]) - 1]);

			}
		}

		TEST_METHOD(gen_chain_num) {
			// TODO: �ڴ�������Դ���
			sample sample_list[7] = {
				// �趨�����ܶ�ĵ�������
				{ { "ab", "bc", "cd", "de", "ef", }, 5, 0, 0, 2, 4 } ,
				// ��һ������������
				{ { "ab", "cd", "bc", "ef","de", }, 5, 0, 0, 2, 4 } ,
				// ���Ը�������, ָ������ĸ
				{ { "ab", "bc", "cd", "de", "ef", }, 5, 'a', 0, 2, 1 } ,
				// ������һ�����������ӿ��ܵĵ�������
				//{ { "ab", "bc", "dbc", "cd", "de", "ef", }, 6, 0, 'd', 2, 2 } ,
				// ������һ����������, ָ����β��ĸ
				{ { "ab", "cd", "bc", "ef","de", }, 5, 'a', 'c', 2, 1 } ,
				// ����û����ȷ���������
				{ { "ab", "cd", "bc", "ef","de", }, 5, 'a', 'd', 2, 0 } ,
				{ { "ab", "cd", "ef", "gh" }, 4, 0, 0, 0, 0 },
			};

			// ���Կ�ʼ
			for (int i = 0; i < sizeof(sizeof(sample_list) / sizeof(sample_list[0])); i++) {
				char **word = sample_list[i].word, 
					*result[100][100] = { 0 }, 
					start_ch = sample_list[i].start_ch, 
					end_ch = sample_list[i].end_ch;
				int expected_len = sample_list[i].expected_return_value,
					result_chain_num,
					word_len = sample_list[i].word_len,
					set_num = sample_list[i].set_num;

				Core core_test = Core();
				int real_chain_num = core_test.gen_chain_word_certain_num(word, word_len, result, result_chain_num, set_num,start_ch, end_ch);
				char last_tail;

				// ���Գ���
				Assert::AreEqual(expected_len, real_chain_num);

				//������β��ӵĺϷ���
				for (int j = 0; j < result_chain_num; j++) {
					for (int i = 0; i < set_num; i++) {
						if (i > 0)
							Assert::AreEqual(last_tail, result[j][i][0]);
						last_tail = result[j][i][strlen(result[j][i]) - 1];
					}

					//����ָ����λ��ĸ������µĺϷ���
					if (start_ch && set_num > 0)
						Assert::AreEqual(start_ch, result[j][0][0]);
					if (end_ch && set_num > 0)
						Assert::AreEqual(end_ch, result[j][set_num - 1][strlen(result[j][set_num - 1]) - 1]);
				}
			}
		}

		TEST_METHOD(get_chain_char) {
			// TODO: �ڴ�������Դ���
			sample sample_list[5] = {
				// ���õ��ʽ϶����ĸ���϶�������ͬ�ĵ�����
				{ { "ab", "bc", "cd", "de","abcdefg", "ghijkl" }, 6, 0, 0, 0, 2 } ,
				// ��⸽������, ָ����β��ĸ
				{ { "ab", "bc", "cd", "de","abcdefg", "ghijkl" }, 6, 'a', 0, 0, 2 } ,
				{ { "ab", "bc", "cd", "de","abcdefg", "ghijkl" }, 6, 'b', 0, 0, 3 } ,
				{ { "ab", "bc", "cd", "de","abcdefg", "ghijkl" }, 6, 'a', 'e', 0, 4 } ,
			};

			// ���Կ�ʼ
			for (int i = 0; i < sizeof(sizeof(sample_list) / sizeof(sample_list[0])); i++) {
				char **word = sample_list[i].word, *result[100] = { 0 }, start_ch = sample_list[i].start_ch, end_ch = sample_list[i].end_ch;
				int expect_len = sample_list[i].expected_return_value;
				int word_len = sample_list[i].word_len;

				Core core_test = Core();
				int real_len = core_test.gen_chain_char(word, word_len, result, start_ch, end_ch);
				char last_tail;
				// ���Գ���
				Assert::AreEqual(expect_len, real_len);

				//������β��ӵĺϷ���
				for (int i = 0; i < real_len; i++) {
					if (i > 0)
						Assert::AreEqual(last_tail, result[i][0]);
					last_tail = result[i][strlen(result[i]) - 1];
				}

				//����ָ����λ��ĸ������µĺϷ���
				if (start_ch && real_len > 0)
					Assert::AreEqual(start_ch, result[0][0]);
				if (end_ch && real_len > 0)
					Assert::AreEqual(end_ch, result[real_len - 1][strlen(result[real_len - 1]) - 1]);

			}
		}

		TEST_METHOD(gen_chain_and_output) {
			FILE* fp = fopen("Unittest.txt", "w");
			fwrite("elf erase asdf fdsa aquire", 28, 1, fp);
			fclose(fp);
			In_Out begin;
			begin.in("Unittest.txt");
			Core core;
			core.gen_chain_word(begin.words, begin.word_num, begin.result, 'a', 'e');
			begin.print_result();
			fp = fopen("solution.txt", "r");
			char expected[4][100] = { "asdf", "fdsa", "aquire", "erase" };
			int i = 0;
			while (!feof(fp)) {
				char buffer[100];
				Assert::IsTrue(i < 4);
				fscanf(fp, "%s\n", buffer);
				Assert::AreEqual(expected[i++], buffer);
			}
			fp = fopen("Unittest.txt", "w");
			fwrite("ab bc cd de ef", 16, 1, fp);
			fclose(fp);
			In_Out begin1;
			begin1.in("Unittest.txt");
			core.gen_chain_word_certain_num(begin1.words, begin1.word_num, begin1.result_array, begin1.chain_count, 2, 'a', 'c');
			begin1.print_result_array();
			fp = fopen("solution.txt", "r");
			char expected2[3][100] = { "1", "ab", "bc" };
			i = 0;
			while (!feof(fp)) {
				char buffer[100];
				Assert::IsTrue(i < 3);
				fscanf(fp, "%s\n", buffer);
				Assert::AreEqual(expected2[i++], buffer);
			}
		}

	};
}