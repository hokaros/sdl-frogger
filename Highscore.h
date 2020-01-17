#pragma once
#include <fstream>
#include <string>
#include <iostream>

#define NAME_LENGTH 16
#define TOP_SIZE 10

class Highscore
{
public:
	int score;
	int position;
	char name[NAME_LENGTH];

	Highscore(char name[NAME_LENGTH], int score);
	Highscore(char name[NAME_LENGTH], int score, int position);
	bool IsTop(Highscore** highscores);
	static void LoadHighscore(char name[NAME_LENGTH], int score);
	static Highscore** LoadFromFile();
	static void SaveAll(Highscore *highscores[TOP_SIZE]);
	static void Sort(Highscore *highscores[TOP_SIZE]);
};

