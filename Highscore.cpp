#include "Highscore.h"

using namespace std;

Highscore::Highscore(const char* name, int score) {
	this->name = name;
	this->score = score;
	fstream file;
	file.open("highscores.txt", ios::in);
	if (!file.good()) {
		ofstream fileNew{};
		position = 1;
	}
	else {
		position = 1;
	}

	file.close();
	if (IsTop10()) {
		file.open("highscores.txt", ios::out | ios::app);
		string line;
		int l = 1;
		for (; l < position; l++) {
			getline(file, line);
		}
		file << score<<' '<< name << endl;
		file.close();
	}
}

Highscore::Highscore(const char* name, int score, int position) {
	this->name = strdup(name);
	this->score = score;
	this->position = position;
}

bool Highscore::IsTop10() {
	if (position > 0)
		return (position <= 10);
	else {
		return false;
	}
}

void Highscore::LoadHighscore(char* name, int score) {
	Highscore user(name, score);
}

Highscore** Highscore::LoadFromFile() {
	Highscore** highscores = new Highscore*[10];
	fstream file;
	file.open("highscores.txt", ios::in);
	if (!file.good())
	{
		for (int l = 1; l <= 10; l++) {
			highscores[l-1] = new Highscore("", 0, l);
		}
	}
	else {
		int l = 1;
		string name;
		const char* nameC = new char[17];
		int score;
		while (!file.eof() ) {
			file >> score;
			if (file.eof())
				break;
			file >> name;
			nameC = name.c_str();
			highscores[l-1] = new Highscore(nameC, score, l);
			l++;
		}
		for (int l = 1; l <= 10; l++) {
			highscores[l-1] = new Highscore("", 0, l);
		}
	}
	file.close();
	return highscores;
}