#include "Killing.h"

Killing::Killing(rectangle lethalArea, Area a, Vector velocity, int leftBoundary, int rightBoundary)
	:MovingHor(a, velocity, leftBoundary, rightBoundary) {
	this->lethalArea = lethalArea;
}

bool Killing::DoesKill(Area object) {
	//zamiana wzglêdnych wspó³rzêdnych na bezwzglêdne
	Rectangle absolute = { x + lethalArea.x, y + lethalArea.y, lethalArea.width, lethalArea.height };
	return object.DoesCross(absolute);
	/*
	sprawdzanie, czy wierzcho³ki zawieraj¹ siê w polu,
	z wy³¹czeniem sytuacji, w której
	powierzchnie stykaj¹ siê krawêdziami górnymi lub dolnymi
	*/
	//VectorInt corner = { object.x, object.y };  //lewy, górny róg
	//if (Area::IsPointInside(corner, absolute) && corner.y != absolute.y + absolute.height) //zewnêtrzne stykniêcie
	//	return true;
	//corner = { object.x, object.y + object.height }; //lewy, dolny róg
	//if (Area::IsPointInside(corner, absolute) && corner.y != absolute.y)
	//	return true;
	//corner = { object.x + object.width, object.y }; //prawy, górny róg
	//if (Area::IsPointInside(corner, absolute) && corner.y != absolute.y + absolute.height)
	//	return true;
	//corner = { object.x + object.width, object.y + object.height }; //prawy, dolny róg
	//if (Area::IsPointInside(corner, absolute) && corner.y != absolute.y)
	//	return true;
	//return false;
}