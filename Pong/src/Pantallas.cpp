#include "Pantallas.h"
#include "include/raylib.h"

void tituloUpdate() {
	tituloDraw();
	if (IsKeyPressed(KEY_SPACE)) {
		ChangeT = 1;
	}
	if (IsKeyPressed(KEY_ENTER)) {
		ChangeT = 2;
	}
}

void tituloDraw() {
	BeginDrawing();

	ClearBackground(BLACK);
	DrawText("P O N G", 20, 20, 40, MAROON);
	DrawText("Presione \"Espacio\" para empezar", 130, 220, 20, MAROON);
	DrawText("Presione \"Escape\" para salir", 130, 300, 20, MAROON);
	DrawText("Presione \"Enter\" para creditos", 130, 320, 20, MAROON);
	DrawText("Version 1.0", 130, 340, 20, MAROON);


	EndDrawing();
}
