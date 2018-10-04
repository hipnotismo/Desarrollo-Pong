#ifndef Game_H
#define Game_H
#include "Creditos.h"
#include "Over.h"
#include "Pantallas.h"

void core();
void Init();
void UpdateGame();
void DrawGame();
void End();
void Update();
void InitBallSpeed();
void ResetLife();
void CamPantallas();
extern  bool gameOver;
enum GameScreen { Main = 0, Play, Over, Credits };
extern GameScreen Screens;
#endif // !Game_H