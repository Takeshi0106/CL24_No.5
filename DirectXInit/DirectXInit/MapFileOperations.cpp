#include "MapFileOperations.h"

// セットしたファイルの配列を返す関数
map<pair<int, int>, int> MapFileOperations::GetMapDate(string _FileName)
{
	SetFileName(_FileName);
	return FileRead();
}

// ファイルの名前をセットする
void MapFileOperations::SetFileName(string _FileName)
{
	FileName = _FileName;
}

// ファイルを読む関数
map<pair<int, int>, int> MapFileOperations::FileRead()
{
	string readBuffer; // 読み出しデータの保存用
	map<pair<int, int>, int> dateMap; //マップデータを格納するコンテナ

	// ファイルオープン
	fin.open(FileName, ios::in);

	if (!fin.is_open())
	{
		// ファイルオープンエラー
		cout << "ファイルを開けませんでした" << endl;
	}
	else
	{
		// UTF-8のBOM検出
		char bom[3] = { 0 };
		fin.read(bom, 3);
		if (!(bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF))
		{
			fin.seekg(0);
		}

		string tempBuffer; // 一時読み出し用
		int row = 0;

		// ファイルからの読み出し
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

	// ファイルクローズ
	fin.close();

	return dateMap;
}