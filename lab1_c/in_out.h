#pragma once
#include"in_out.h"
//����������������ĺ���
#define MAX_WORD_LEN 50


class In_Out
{

public:
	In_Out();

	void in(char *filepath);//���ļ��ж�����

	bool myisalpha(char &ch);//�ж��Ƿ����ַ���������д�ַ�ת��ΪСд

	void print_result();//������������ĸ�����ĵ��������

	void print_result_array();//����ض���Ŀ�ĵ�����

	~In_Out();
public:
	char *words[1000];//��ŵ���
	int  word_num;//��������
	char *result[100];//��ŵ�����
	char *result_array[1000][100];//����ض������ĵ�����
	int chain_count;//������������������-n�ͣ�
};

