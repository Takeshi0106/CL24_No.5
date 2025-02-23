#pragma once

// ===================================
// .csv �t�@�C���̓ǂݍ��݃N���X
// ===================================

#include <iostream>
#include <fstream>
#include <sstream>

#include <map>
#include <utility>

using namespace std;

class MapFileOperations
{
private:
	ifstream fin;    //�t�@�C���X�g���[��
	string FileName; //�t�@�C����

	// �t�@�C�����Z�b�g
	void SetFileName(string _FileName);
	// �t�@�C������l��ǂݏo���֐�
	map<pair<int, int>, int> FileRead();

public:
	// �t�@�C�����Z�b�g���ăt�@�C���̒l���Q�����z��ɑ�����ĕԂ��֐�
	map<pair<int, int>, int> GetMapDate(string _FileName);
};

