#include "Level.h"
#include <string>

Level::Level(SDL_Surface* screen) {
	this->screen = screen;
	//wczytanie t³a
	background = SDL_LoadBMP("graphics/background1.bmp");
	if (background == NULL) {
		printf("SDL_LoadBMP(graphics/background1.bmp) error: %s\n", SDL_GetError());
		return;
	}
	mapBottomBorder = background->h;
	mapLeftBorder = (SCREEN_WIDTH - background->w) / 2;
	mapTopBorder = mapBottomBorder - ROW_HEIGHT * 13;
	mapRightBorder = mapLeftBorder + background->w;

	LoadPlayer();
	/*********************£ADOWANIE PRZESZKÓD**********************/
	//pojazdy
	LoadCars(1, 5, { -130, 0 }, 120);
	LoadCars(2, 4, { 150, 0 }, 90);
	LoadCars(3, 4, { -110, 0 }, 80);
	LoadCars(4, 2, { 170, 0 }, 100);
	LoadCars(5, 5, { -140, 0 }, 80);
	//¿ó³wie
	LoadTurtleGroups(1, 3, { -130, 0 }, 100);
	LoadTurtleGroups(4, 5, { -160, 0 }, 80);
	//k³ody
	LoadLogs(2, 3, { 120,0 }, 100);
	LoadLogs(3, 1, { -170,0 }, 200);
	LoadLogs(5, 4, { 150,0 }, 80);
}

Level::~Level() {
	unsigned short i;
	//zwalnianie obiektów
	for (i = 0; i < cars1Count; i++) {
		delete cars1[i];
	}
	for (i = 0; i < cars2Count; i++) {
		delete cars2[i];
	}
	for (i = 0; i < cars3Count; i++) {
		delete cars3[i];
	}
	for (i = 0; i < cars4Count; i++) {
		delete cars4[i];
	}
	for (i = 0; i < cars5Count; i++) {
		delete cars5[i];
	}
	//¿ó³wie
	for (i = 0; i < turtleGroups1Count; i++) {
		delete turtleGroups1[i];
	}
	for (i = 0; i < turtleGroups2Count; i++) {
		delete turtleGroups2[i];
	}
	//k³ody
	for (i = 0; i < logs1Count; i++) {
		delete logs1[i];
	}
	for (i = 0; i < logs2Count; i++) {
		delete logs2[i];
	}
	for (i = 0; i < logs3Count; i++) {
		delete logs3[i];
	}

	delete player;
	SDL_FreeSurface(background);
}

void Level::LoadPlayer() {
	SDL_Surface* froggerSf = SDL_LoadBMP("graphics/frogger.bmp");
	if (froggerSf == NULL) {
		printf("SDL_LoadBMP(graphics/frogger.bmp) error: %s\n", SDL_GetError());
		return;
	}
	Area frogger(mapLeftBorder, mapBottomBorder - froggerSf->h, froggerSf, screen);
	player = new MovingFree(frogger, mapTopBorder, mapRightBorder, mapBottomBorder, mapLeftBorder);
}

void Level::LoadCars(unsigned short streetRow, unsigned short count, Vector velocity, int gap) {
	char spritePath[128];
	sprintf(spritePath, "graphics/car%d.bmp", streetRow);
	SDL_Surface* carSf = SDL_LoadBMP(spritePath);
	if (carSf == NULL) {
		printf("SDL_LoadBMP(%s) error: %s\n", spritePath, SDL_GetError());
	}
	Area carA(mapLeftBorder, mapBottomBorder - ROW_HEIGHT * (streetRow+1), carSf, screen);
	Killing*** cars;
	switch (streetRow) {
	case 1:
		cars = &cars1;
		cars1Count = count;
		break;
	case 2:
		cars = &cars2;
		cars2Count = count;
		break;
	case 3:
		cars = &cars3;
		cars3Count = count;
		break;
	case 4:
		cars = &cars4;
		cars4Count = count;
		break;
	case 5:
		cars = &cars5;
		cars5Count = count;
		break;
	default:
		cars = &cars1;
		cars1Count = count;
		break;
	}

	int leftBoundary, rightBoundary;
	if (velocity.x < 0) { //zwrot w lewo
		leftBoundary = mapLeftBorder - background->w;
		rightBoundary = mapRightBorder;
	}
	else { //zwrot w prawo
		leftBoundary = mapLeftBorder;
		rightBoundary = mapRightBorder + background->w;
	}
	*cars = new Killing * [count];
	for (unsigned short i = 0; i < count; i++) {
		(*cars)[i] = new Killing({ 0,0,carA.width, carA.height }, //œmiercionoœny na ca³ej powierzchni
			carA, velocity, leftBoundary, rightBoundary);
		(*cars)[i]->x += i * ((*cars)[i]->width + gap);
	}
}

void Level::LoadTurtleGroups(unsigned short riverRow, unsigned short count, Vector velocity, int gap) {
	SDL_Surface* turtleSf = SDL_LoadBMP("graphics/turtle.bmp");
	if (turtleSf == NULL) {
		printf("SDL_LoadBMP(graphics/turtle.bmp) error: %s\n", SDL_GetError());
	}
	Area turtleA(mapLeftBorder, mapBottomBorder - ROW_HEIGHT * (riverRow + 7), turtleSf, screen);
	TurtleGroup*** turtles;
	unsigned short groupCombo;
	switch (riverRow) {
	case 1:
		turtles = &turtleGroups1;
		turtleGroups1Count = count;
		groupCombo = 3;
		break;
	case 4:
		turtles = &turtleGroups2;
		turtleGroups2Count = count;
		groupCombo = 2;
		break;
	default:
		turtles = &turtleGroups1;
		turtleGroups1Count = count;
		groupCombo = 3;
		break;
	}

	int leftBoundary, rightBoundary;
	if (velocity.x < 0) { //zwrot w lewo
		leftBoundary = mapLeftBorder - background->w;
		rightBoundary = mapRightBorder;
	}
	else { //zwrot w prawo
		leftBoundary = mapLeftBorder;
		rightBoundary = mapRightBorder + background->w;
	}
	*turtles = new TurtleGroup * [count];
	for (int i = 0; i < count; i++) {
		(*turtles)[i] = new TurtleGroup(groupCombo, turtleA, velocity, leftBoundary, rightBoundary);
		(*turtles)[i]->MoveByVector({ i * ((*turtles)[i]->GetWidth() + gap), 0 });
	}
}

void Level::LoadLogs(unsigned short riverRow, unsigned short count, Vector velocity, int gap) {
	char spritePath[128];
	char* logType;
	Attachable*** logs;
	switch (riverRow) {
	case 2:
		logs = &logs1;
		logs1Count = count;
		logType = "Medium";
		break;
	case 3:
		logs = &logs2;
		logs2Count = count;
		logType = "Long";
		break;
	case 5:
		logs = &logs3;
		logs3Count = count;
		logType = "Short";
		break;
	default:
		logs = &logs1;
		cars1Count = count;
		logType = "Medium";
		break;
	}
	sprintf(spritePath, "graphics/log%s.bmp", logType);
	SDL_Surface* logSf = SDL_LoadBMP(spritePath);
	if (logSf == NULL) {
		printf("SDL_LoadBMP(%s) error: %s\n", spritePath, SDL_GetError());
	}
	Area logA(mapLeftBorder, mapBottomBorder - ROW_HEIGHT * (riverRow + 7), logSf, screen);

	int leftBoundary, rightBoundary;
	if (velocity.x < 0) { //zwrot w lewo
		leftBoundary = mapLeftBorder - background->w;
		rightBoundary = mapRightBorder;
	}
	else { //zwrot w prawo
		leftBoundary = mapLeftBorder;
		rightBoundary = mapRightBorder + background->w;
	}
	*logs = new Attachable * [count];
	for (int i = 0; i < count; i++) {
		(*logs)[i] = new Attachable(logA, velocity, leftBoundary, rightBoundary);
		(*logs)[i]->x += i * ((*logs)[i]->width + gap);
	}
}

void Level::MoveLogs(bool& attached, double deltaTime) {
	unsigned short i;
	for (i = 0; i < logs1Count; i++) {
		if (!attached && logs1[i]->IsAttached(*player)) {
			attached = true;
			player->MoveByVector(logs1[i]->Move(deltaTime));
		}
		else
			logs1[i]->Move(deltaTime);
	}
	for (i = 0; i < logs2Count; i++) {
		if (!attached && logs2[i]->IsAttached(*player)) {
			attached = true;
			player->MoveByVector(logs2[i]->Move(deltaTime));
		}
		else
			logs2[i]->Move(deltaTime);
	}
	for (i = 0; i < logs3Count; i++) {
		if (!attached && logs3[i]->IsAttached(*player)) {
			attached = true;
			player->MoveByVector(logs3[i]->Move(deltaTime));
		}
		else
			logs3[i]->Move(deltaTime);
	}
}

void Level::MoveCars(bool& killed, double deltaTime) {
	unsigned short i;
	for (i = 0; i < cars1Count; i++) {
		cars1[i]->Move(deltaTime);
		if (cars1[i]->DoesKill(*player)) {
			killed = true;
		}
	}
	for (i = 0; i < cars2Count; i++) {
		cars2[i]->Move(deltaTime);
		if (cars2[i]->DoesKill(*player)) {
			killed = true;
		}
	}
	for (i = 0; i < cars3Count; i++) {
		cars3[i]->Move(deltaTime);
		if (cars3[i]->DoesKill(*player)) {
			killed = true;
		}
	}
	for (i = 0; i < cars4Count; i++) {
		cars4[i]->Move(deltaTime);
		if (cars4[i]->DoesKill(*player)) {
			killed = true;
		}
	}
	for (i = 0; i < cars5Count; i++) {
		cars5[i]->Move(deltaTime);
		if (cars5[i]->DoesKill(*player)) {
			killed = true;
		}
	}
}

void Level::MoveTurtles(bool& attached, double deltaTime) {
	unsigned short i;
	for (i = 0; i < turtleGroups1Count; i++) {
		if (!attached && turtleGroups1[i]->IsAttached(*player)) {
			attached = true;
			player->MoveByVector(turtleGroups1[i]->Move(deltaTime));
		}
		else
			turtleGroups1[i]->Move(deltaTime);
	}
	for (i = 0; i < turtleGroups2Count; i++) {
		if (!attached && turtleGroups2[i]->IsAttached(*player)) {
			attached = true;
			player->MoveByVector(turtleGroups2[i]->Move(deltaTime));
		}
		else
			turtleGroups2[i]->Move(deltaTime);
	}
}