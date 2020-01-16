#pragma once
#include <fstream>
#include <string>
#include <iostream>

class Highscore
{
public:
	int score;
	int position;
	const char* name;

	Highscore(const char* name, int score);
	Highscore(const char* name, int score, int position);
	bool IsTop10();
	static void LoadHighscore(char* name, int score);
	static Highscore** LoadFromFile();
};

