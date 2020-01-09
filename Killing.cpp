#include "Killing.h"

Killing::Killing(rectangle lethalArea, Area a, Vector velocity, int leftBoundary, int rightBoundary)
	:MovingHor(a, velocity, leftBoundary, rightBoundary) {
	this->lethalArea = lethalArea;
}

bool Killing::DoesKill(Area object) {
	//zamiana wzgl�dnych wsp�rz�dnych na bezwzgl�dne
	Rectangle absolute = { x + lethalArea.x, y + lethalArea.y, lethalArea.width, lethalArea.height };
	return object.DoesCross(absolute);
	/*
	sprawdzanie, czy wierzcho�ki zawieraj� si� w polu,
	z wy��czeniem sytuacji, w kt�rej
	powierzchnie stykaj� si� kraw�dziami g�rnymi lub dolnymi
	*/
	//VectorInt corner = { object.x, object.y };  //lewy, g�rny r�g
	//if (Area::IsPointInside(corner, absolute) && corner.y != absolute.y + absolute.height) //zewn�trzne stykni�cie
	//	return true;
	//corner = { object.x, object.y + object.height }; //lewy, dolny r�g
	//if (Area::IsPointInside(corner, absolute) && corner.y != absolute.y)
	//	return true;
	//corner = { object.x + object.width, object.y }; //prawy, g�rny r�g
	//if (Area::IsPointInside(corner, absolute) && corner.y != absolute.y + absolute.height)
	//	return true;
	//corner = { object.x + object.width, object.y + object.height }; //prawy, dolny r�g
	//if (Area::IsPointInside(corner, absolute) && corner.y != absolute.y)
	//	return true;
	//return false;
}