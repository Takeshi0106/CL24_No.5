#include "MapFileOperations.h"

// �Z�b�g�����t�@�C���̔z���Ԃ��֐�
map<pair<int, int>, int> MapFileOperations::GetMapDate(string _FileName)
{
	SetFileName(_FileName);
	return FileRead();
}

// �t�@�C���̖��O���Z�b�g����
void MapFileOperations::SetFileName(string _FileName)
{
	FileName = _FileName;
}

// �t�@�C����ǂފ֐�
map<pair<int, int>, int> MapFileOperations::FileRead()
{
	string readBuffer; // �ǂݏo���f�[�^�̕ۑ��p
	map<pair<int, int>, int> dateMap; //�}�b�v�f�[�^���i�[����R���e�i

	// �t�@�C���I�[�v��
	fin.open(FileName, ios::in);

	if (!fin.is_open())
	{
		// �t�@�C���I�[�v���G���[
		cout << "�t�@�C�����J���܂���ł���" << endl;
	}
	else
	{
		// UTF-8��BOM���o
		char bom[3] = { 0 };
		fin.read(bom, 3);
		if (!(bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF))
		{
			fin.seekg(0);
		}

		string tempBuffer; // �ꎞ�ǂݏo���p
		int row = 0;

		// �t�@�C������̓ǂݏo��
		while (getline(fin, tempBuffer))
		{
			stringstream lineStream(tempBuffer);
			string cell;
			int col = 0;

			while (getline(lineStream,cell,','))
			{
				int value = stoi(cell);
				dateMap[{row, col}] = value;
				col++;
			}
			
			row++;
		}
	}

	// �t�@�C���N���[�Y
	fin.close();

	return dateMap;
}