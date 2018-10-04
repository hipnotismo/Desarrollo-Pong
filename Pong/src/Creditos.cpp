#include "Creditos.h"
#include "Game.h"
#include "include/raylib.h"

void creditosUpdate() {
	creditoDraw();
	if (IsKeyDown(KEY_SPACE)) {
		Screens = Play;
	}
}


void creditoDraw() {
	BeginDrawing();

	ClearBackground(BLACK);
	DrawText("Presione \"Espacio\" para empezar", 20, 180, 20, MAROON);
	DrawText("Funciones creadas por Palau and Ramon Santamaria", 20, 200, 20, MAROON);
	DrawText("Copyright (c) 2015 Ramon Santamaria (@raysan5)", 20, 220, 20, MAROON);

	DrawText("P O N G, por Martin Concetti", 20, 260, 20, MAROON);
	DrawText("Creado usando raylib y sfxr", 130, 280, 20, MAROON);
	DrawText("Consultantes: Baretto, Sergio", 130, 300, 20, MAROON);
	DrawText("Version 1.0", 130, 320, 20, MAROON);

	EndDrawing();
}