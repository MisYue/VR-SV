/*
���ƣ�Ŀ��ֲ�����
���ܣ������Ŀ����һ�������ھ��ȷֲ���λ��
�����ˣ�����
����ʱ�䣺2016-5-3
�汾��1.0
*/
#pragma once

#include "TargetAndAmmo_Global.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class TARGETANDAMMO_API CSVRead
{
public:
	CSVRead();
	~CSVRead();

	bool inputDateBase( string filepath );//�������ݿ������
	string getFigure( int ii , int jj );//���кš��кŻ�ȡ����
	double transformStringDouble( string strFigure );//��string��ת����double

	int getLineCount();

private:
	double m_DaBaLineCount;//���ݿ�����

	map< int , vector< string >> m_Recorder;//
};