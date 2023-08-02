/*
Author: Brenton Thomas
Assignment: Computer Graphics Lab 2
Date: 03/16/2022
*/

#include <iostream>
#include "..\ClassUtilities\RasterSurface.cpp"
#include "Cube.h"
#include "Grid.h"
#include "View.h"
#include "VectorShader.h"
#include "PixelShader.h"

#pragma region Fields

static const unsigned int WIDTH = 500;
static const unsigned int HEIGHT = 500;
static const int ORIGINOFFSET_X = WIDTH / 2;
static const int ORIGINOFFSET_Y = HEIGHT / 2;

unsigned int pixels[WIDTH * HEIGHT];

VectorShader* vShader;

#pragma endregion

#pragma region Functions

void ClearColorBuffer();
void DrawShape(Vector**, int, Cube*);
void DrawShape(Vector**, int, Grid*);
void DrawVector(Vector*);
void DrawVertex(Vertex*);
void DrawPixel(int, int, unsigned int);
int ConvertCoordinates(int, int);
float Lerp(float, float, float);

#pragma endregion



int main() {

	//initialize raster surface
	RS_Initialize("Brenton Thomas", WIDTH, HEIGHT);
	
	//clear color buffer
	ClearColorBuffer();

	//create view
	View* view = new View(1, 10);
	view->BuildProjectionMatrix(90, WIDTH / HEIGHT, 0.1, 10);

	//rotation values
	float cubeR = 0;
	float cubeR_rate = 0.5f;
	float frameRate = 15;
	float nextTrigger = 0;
	auto start = std::chrono::steady_clock::now();

	//set up shaders
	vShader = new VectorShader(view);

	//render loop
	do {
		//check if frameRate number of seconds has passed
		if (std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::steady_clock::now() - start).count()
			>= nextTrigger) 
		{

			if (cubeR == 360) {
				cubeR = 0;
			}

			cubeR += cubeR_rate;

			//build objects
			Cube* cube = new Cube(0.5, 0xff0055ff);
			cube->SetScale();
			cube->RotateY(cubeR);
			cube->SetPostion(0, 0.25, 0);
			Grid* grid = new Grid(1, 1, 0xff808080);
			grid->SetScale();
			grid->SetPostion(0, 0.5, 0);


			//clear color buffer
			ClearColorBuffer();

			//draw test data
			DrawShape(grid->vec, grid->vecSize, grid);
			DrawShape(cube->vec, cube->vecSize, cube);

			//update clock trigger
			nextTrigger += frameRate;

			delete cube;
			delete grid;
		}
	} while (RS_Update(pixels, (WIDTH * HEIGHT)));
	
	//shutdown raster surface
	RS_Shutdown();

}

void ClearColorBuffer() {
	//set every pixel to a default color (Black)
	for (int y = -ORIGINOFFSET_Y; y < ORIGINOFFSET_Y; y++) {
		for (int x = -ORIGINOFFSET_X; x < ORIGINOFFSET_X; x++) {
			DrawPixel(x, y, 0);
		}
	}
}

void DrawShape(Vector** v, int numV, Cube* c) {

	//draw all vectors
	for (int i = 0; i < numV; i++) {

		//apply vShader
		Vector* temp = new Vector(v[i]->start, v[i]->end, v[i]->color);
		temp->start = vShader->ApplyShader(temp->start, c);
		temp->end = vShader->ApplyShader(temp->end, c);

		DrawVector(temp);
	}
}

void DrawShape(Vector** v, int numV, Grid* g) {

	//draw all vectors
	for (int i = 0; i < numV; i++) {

		//apply vShader
		Vector* temp = new Vector(v[i]->start, v[i]->end, v[i]->color);
		temp->start = vShader->ApplyShader(temp->start, g);
		temp->end = vShader->ApplyShader(temp->end, g);

		DrawVector(temp);
	}
}

void DrawVector(Vector* v) {

	float offset, iter;
	iter = 0.001f;
	Vertex* curr = new Vertex();
	curr->color = v->color;
	offset = 0;

	while (offset <= 1) {

		curr->x = Lerp(v->start->x, v->end->x, offset);
		curr->y = Lerp(v->start->y, v->end->y, offset);
		offset += iter;

		DrawVertex(curr);
	}
}

void DrawVertex(Vertex* v) {
	if ((v->x < ORIGINOFFSET_X && v->x > -ORIGINOFFSET_X) && (v->y < ORIGINOFFSET_Y && v->y > -ORIGINOFFSET_Y)) {
		pixels[ConvertCoordinates(v->x, v->y)] = v->color;
	}
}

void DrawPixel(int x, int y, unsigned int c) {
	//check if the coordinates are on the screen; if not, do nothing with the information
	if ((x < ORIGINOFFSET_X && x > -ORIGINOFFSET_X) && (y < ORIGINOFFSET_Y && y > -ORIGINOFFSET_Y)) {
		pixels[ConvertCoordinates(x, y)] = c;
	}
}

int ConvertCoordinates(int x, int y) {
	//apply the origin offset
	x += ORIGINOFFSET_X;
	y += ORIGINOFFSET_Y;

	//translate that to a single index, (0,0) being the bottom left and (maxX, maxY) being top right
	return (WIDTH * ((y - (HEIGHT - 1)) * -1)) + x;
}

float Lerp(float a, float b, float t) {
	return a + t * (b - a);
}