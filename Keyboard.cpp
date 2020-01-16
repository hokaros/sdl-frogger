#include "Keyboard.h"

char Keyboard::GetChar(SDL_Keycode sym) {
	switch (sym) {
	case SDLK_0:
		return '0';
	case SDLK_1:
		return '1';
	case SDLK_2:
		return '2';
	case SDLK_3:
		return '3';
	case SDLK_4:
		return '4';
	case SDLK_5:
		return '5';
	case SDLK_6:
		return '6';
	case SDLK_7:
		return '7';
	case SDLK_8:
		return '8';
	case SDLK_9:
		return '9';
	case SDLK_a:
		return 'A';
	case SDLK_b:
		return 'B';
	case SDLK_c:
		return 'C';
	case SDLK_d:
		return 'D';
	case SDLK_e:
		return 'E';
	case SDLK_f:
		return 'F';
	case SDLK_g:
		return 'G';
	case SDLK_h:
		return 'H';
	case SDLK_i:
		return 'I';
	case SDLK_j:
		return 'J';
	case SDLK_k:
		return 'K';
	case SDLK_l:
		return 'L';
	case SDLK_m:
		return 'M';
	case SDLK_n:
		return 'N';
	case SDLK_o:
		return 'O';
	case SDLK_p:
		return 'P';
	case SDLK_q:
		return 'Q';
	case SDLK_r:
		return 'R';
	case SDLK_s:
		return 'S';
	case SDLK_t:
		return 'T';
	case SDLK_u:
		return 'U';
	case SDLK_v:
		return 'V';
	case SDLK_w:
		return 'W';
	case SDLK_x:
		return 'X';
	case SDLK_y:
		return 'Y';
	case SDLK_z:
		return 'Z';
	default:
		return NULL;
	}
}