#include "include/raylib.h"
#include "Game.h"
#include "Over.h"

void overUpdate() {
	overDraw();

	if (IsKeyDown(KEY_SPACE)) {
		ResetLife();
		gameOver = false;
		Screens = Play;
	}
 }
void overDraw() {
	BeginDrawing();

	ClearBackground(BLACK);
	DrawText("GAME O V E R", 20, 20, 40, MAROON);
	DrawText("Presione \"Espacio\" para reiniciar", 130, 220, 20, MAROON);
	DrawText("Presione \"Escape\" para salir", 130, 300, 20, MAROON);

	EndDrawing();
}