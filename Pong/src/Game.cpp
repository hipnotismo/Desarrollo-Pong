#include "Game.h"
#include "include/raylib.h"
#include "Pantallas.h"
#include "Over.h"
#include "Creditos.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

#define PLAYER_MAX_LIFE 5
#define max	5
#define min -5

GameScreen Screens;


struct Player {
	Vector2 position;
	Vector2 size;
	int life;
};

struct Ball {
	Vector2 position;
	Vector2 speed;
	int radius;
	bool active;
};

static Player player;
static Player player2;
static Ball ball;

bool gameOver;
static bool pause;

int finishScreen;
int ChangeT;
int screenWidth = 800;
int screenHeight = 450;
Sound Ping;
Music Ambient;
Rectangle rec1;
Rectangle rec2;


void Update(void) {
	UpdateGame();
	DrawGame();
}

void core() {
	InitWindow(screenWidth, screenHeight, "P O N G");

	Init();

//#define AUDIO
#ifdef AUDIO
	InitAudioDevice();


	 Ping = LoadSound("res/Ball_VS_Player.wav");
	 Ambient = LoadMusicStream("res/Tema");

#endif

	while (!WindowShouldClose()) {

		CamPantallas();

	}
#ifdef AUDIO
	UnloadSound(Ping);
	UnloadMusic(Ambient);
	CloseAudioDevice();
#endif // AUDIO

	End();
	CloseWindow();


}

void Init(void) {
	player.position = { (float)screenWidth / 9, (float)screenHeight / 7 };
	player.size = { (float)screenWidth / 10, 20 };
	player.life = PLAYER_MAX_LIFE;

	player2.position = {(float)screenWidth - 40,(float)screenHeight / 7};
	player2.size = { (float)screenWidth / 10, 20 };
	player2.life = PLAYER_MAX_LIFE;


	ball.position = { (float)screenWidth / 2, (float)screenHeight / 2 };
	ball.speed = { 0, 0 };
	ball.radius = 7;
	ball.active = false;

	ChangeT = 0;

	Screens = Main;
}

void UpdateGame(void) {
	if (!gameOver)
	{
		if (IsKeyPressed('P')) pause = !pause;

		if (!pause) {
			// Player movement logic
			if (IsKeyDown(KEY_W)) player.position.y -= 300 * GetFrameTime();
			if ((player.position.y - player.size.y / 2) <= 0) player.position.y = player.size.y / 2;
			if (IsKeyDown(KEY_S)) player.position.y += 300 * GetFrameTime();
			if ((player.position.y + player.size.y / 2) >= screenWidth) player.position.y = screenWidth - player.size.y / 2;

			if (IsKeyDown(KEY_UP)) player2.position.y -= 300 * GetFrameTime();
			if ((player2.position.y - player2.size.y / 2) <= 0) player2.position.y = player2.size.y / 2;
			if (IsKeyDown(KEY_DOWN)) player2.position.y += 300 * GetFrameTime();
			if ((player2.position.y /*+ player2.size.y / 2*/) >= screenWidth) player2.position.y = screenWidth - player2.size.y / 2;

			// Ball launching logic
			if (!ball.active) {
				if (IsKeyPressed(KEY_SPACE)) {
					ball.active = true;
					InitBallSpeed();
				}
			}

			// Ball movement logic 
			if (ball.active) {
				ball.position.x += ball.speed.x * GetFrameTime();
				ball.position.y += ball.speed.y * GetFrameTime();
			}

			rec1.width = player.size.x;
			rec1.height = player.size.y;
			rec1.x = player.position.x;
			rec1.y = player.position.y;
			
			rec2.width = player2.size.x;
			rec2.height = player2.size.y;
			rec2.x = player2.position.x;
			rec2.y = player2.position.y;

			// Collision logic: ball vs walls 

			if (((ball.position.y + ball.radius) >= screenHeight) || ((ball.position.y - ball.radius) <= 0)) ball.speed.y *= -1;
			if ((ball.position.x - ball.radius) <= 0) ball.speed.y *= -1;
			if ((ball.position.x + ball.radius) >= screenWidth) {
				ball.speed = { 0, 0 };
				ball.active = false;

				player2.life--;
				ball.position = { (float)screenWidth / 2, (float)screenHeight / 2 };
				InitBallSpeed();
			}

			if ((ball.position.x + ball.radius) < screenWidth / 20) {
				ball.speed = { 0, 0 };
				ball.active = false;

				player.life--;
				ball.position = { (float)screenWidth / 2, (float)screenHeight / 2 };
				InitBallSpeed();
			}

			// Collision logic: ball vs player
			if (CheckCollisionCircleRec(ball.position, (float)ball.radius,  rec1))
				{

				ball.speed.x *= -1;
				ball.speed.y *= -1;
				//PlaySound(Ping);
			}

			if (CheckCollisionCircleRec(ball.position, (float)ball.radius,  rec2)) {

				ball.speed.x *= -1;
				ball.speed.y *= -1;
				//PlaySound(Ping);
			}

			// Game over logic
			if (player.life <= 0) {
				gameOver = true;
				Screens = Over;
			}
			if (player2.life <= 0) {
				gameOver = true;
				Screens = Over;
			}
		}
	}
}

void DrawGame(void) {
	BeginDrawing();

	ClearBackground(BLACK);

	if (!gameOver) {
		// Draw player bar
		DrawRectangle(player.position.x , player.position.y , player.size.y, player.size.x, RAYWHITE);

		DrawRectangle(player2.position.x , player2.position.y , player2.size.y, player2.size.x, RAYWHITE);

		// Draw player lives
		for (int i = 0; i < player.life; i++) DrawRectangle(20 + 40 * i, screenHeight - 30, 35, 10, LIGHTGRAY);

		for (int i = 0; i < player2.life; i++) DrawRectangle(500 + 40 * i, screenHeight - 30, 35, 10, LIME);


		// Draw ball
		DrawCircleV(ball.position, (float)ball.radius, MAROON);
		if (pause) DrawText("Juego en pausa", screenWidth / 2 - MeasureText("Juego en pausa", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
	}

	EndDrawing();
}

void ResetLife() {
	player2.life = PLAYER_MAX_LIFE;
	player.life = PLAYER_MAX_LIFE;

}

void InitBallSpeed() {
	int tempX;
	int tempY;
	do {
		tempX = GetRandomValue(min, max);
		tempY = GetRandomValue(min, max);
	} while (tempX == 0 || tempY == 0);
	ball.speed = { (float)tempX*60, (float)tempY*60 };
}

void CamPantallas() {
	switch (Screens) {
	case Main: {
		tituloUpdate();
		if (ChangeT == 1) {
			Screens = Play;
		}
		if (ChangeT == 2) {
			Screens = Credits;
		}
	} break;
	case Credits: {
		creditosUpdate();
	} break;
	case Play: {
		Update();
	} break;
	case Over: {
		overUpdate();

	}
	}
}

void End() {

}