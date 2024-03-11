#ifndef GAME_H
#define GAME_H
#define MAX_FILE_LENGTH 256
#define BUFFER_LENGTH 512
#define OCEAN_TOKEN 'O'
#define GRIZZLY 'G'
#define BOAR 'B'
#define ELK 'E'
#define HARE 'H'
#define COLD 'C'
#define FLU 'F'
#define DYSENTERY 'D'
#define RIVER 'R'
#define CURRENT_POS 'X'
#define ENDING_POS 'Z'
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum { DISEASE, ANIMAL } THREAT_TYPE_t;
typedef struct Grizzly
{
    const char grizzly;
    int food;

} GRIZZLY_t;

typedef struct Boar
{
    const char boar;
    int food;

} BOAR_t;

typedef struct Elk
{
    const char elk;
    int food;

} ELK_t;

typedef struct Hare
{
    const char hare;
    int food;

} HARE_t;

typedef struct Animal
{
    GRIZZLY_t grizzly;
    BOAR_t boar;
    ELK_t elk;
    HARE_t hare;

} ANIMAL_t;

typedef struct Cold
{
    const char cold;
    int food;
} COLD_t;

typedef struct Flu
{
    const char flu;
    int food;
} FLU_t;

typedef struct Dysentery
{
    const char dysentery;
    int food;
} DYSENTERY_t;

typedef struct River
{
    const char river;
    int food;
} RIVER_t;

typedef struct Disease
{
    COLD_t cold;
    FLU_t flu;
    DYSENTERY_t dysentery;
    RIVER_t river;
} DISEASE_t;

typedef union Threat
{
    ANIMAL_t animal;
    DISEASE_t disease;
} THREAT_t;

typedef struct Node
{
    THREAT_t threat;
    THREAT_TYPE_t threatType;
    int xPos;
    int yPos;
    bool discovered;
    char cellChar;
    struct Node* up;
    struct Node* down;
    struct Node* left;
    struct Node* right;
} NODE_t;

NODE_t** map;
NODE_t** viewPort;
char* fileName;
int mapSize;
int viewPortSize;
int playerFood;
int currX;
int currY;
FILE* file;

bool startGame();
bool readFile();
void createViewPort();
void gamePlay();
bool userInteract(char cellChar);
bool userAction();
void displayView();
void freeMem();
void red();
void yellow();
void green();
void blue();
void white();
void cyan();
void purple();
void reset();
#endif