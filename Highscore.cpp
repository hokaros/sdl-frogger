#include "Highscore.h"

using namespace std;

Highscore::Highscore(char name[NAME_LENGTH], int score) {
	strcpy(this->name, name);
	this->score = score;
	position = 0;

	Highscore** highscores = LoadFromFile();
	if (IsTop(highscores)) {
		highscores[TOP_SIZE - 1] = this;
		SaveAll(highscores);
	}
}

Highscore::Highscore(char name[NAME_LENGTH], int score, int position) {
	strcpy(this->name, name);
	this->score = score;
	this->position = position;
}

bool Highscore::IsTop(Highscore** highscores) {
	if (position > 0)
		return (position <= TOP_SIZE);
	else {
		Sort(highscores);
		if (this->score > highscores[TOP_SIZE - 1]->score) {
			return true;
		}
		return false;
	}
}

void Highscore::LoadHighscore(char name[NAME_LENGTH], int score) {
	Highscore user(name, score);
}

Highscore** Highscore::LoadFromFile() {
	Highscore** highscores = new Highscore*[10];
	fstream file;
	file.open("highscores.txt", ios::in);
	char name[NAME_LENGTH];
	if (!file.good())
	{
		strcpy(name, "-");
		for (int l = 1; l <= 10; l++) {
			highscores[l-1] = new Highscore(name, 0, l);
		}
	}
	else {
		int l = 1;
		int score = 0;
		while (!file.eof() ) {
			file >> score;
			file >> name;
			if (file.eof())
				break;
			highscores[l-1] = new Highscore(name, score, l);
			l++;
		}
		strcpy(name, "-");
		for (; l <= 10; l++) {
			highscores[l-1] = new Highscore(name, 0, l);
		}
	}
	file.close();
	return highscores;
}

void Highscore::SaveAll(Highscore *highscores[TOP_SIZE]) {
	fstream file;
	file.open("highscores.txt", ios::out);

	Sort(highscores);
	for (int i = 0; i < TOP_SIZE; i++) {
		file << highscores[i]->score << ' ' << highscores[i]->name << endl;
	}
	file.close();
}

void Highscore::Sort(Highscore *highscores[TOP_SIZE]) {
	Highscore *helper;
	for (int i = 0; i < TOP_SIZE; i++) {
		for (int j = 0; j < TOP_SIZE-i-1; j++) {
			if (highscores[j]->score < highscores[j + 1]->score) {
				helper = highscores[j + 1];
				highscores[j + 1] = highscores[j];
				highscores[j] = helper;
			}
		}
	}

	for (int pos = 1; pos <= TOP_SIZE; pos++) {
		highscores[pos - 1]->position = pos;
	}
}