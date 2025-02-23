#pragma once

// ===================================
// .csv ファイルの読み込みクラス
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
	ifstream fin;    //ファイルストリーム
	string FileName; //ファイル名

	// ファイルをセット
	void SetFileName(string _FileName);
	// ファイルから値を読み出す関数
	map<pair<int, int>, int> FileRead();

public:
	// ファイルをセットしてファイルの値を２次元配列に代入して返す関数
	map<pair<int, int>, int> GetMapDate(string _FileName);
};

