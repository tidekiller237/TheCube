#pragma once

#include "Vector.h"

#define PI 3.14159265

class Cube {
public:
	float wMat[4][4];
	float tMat[4][4];
	Vector* vec[12];
	const int vecSize = 12;
	float height;
	unsigned int color;

	Cube() {
		color = 0;
		height = 1;

		InitWorldMatrix();
		SetVectors();
	}

	Cube(float h, unsigned int c) {
		color = c;
		height = h;

		InitWorldMatrix();
		SetVectors();
	}

	~Cube() {
		for (int i = 0; i < vecSize; i++) {
			delete vec[i];
		}
	}

	void SetPostion(float x, float y, float z) {
		InitTransformationMatrix();
		tMat[3][0] = x;
		tMat[3][1] = y;
		tMat[3][2] = z;
		CalculateTransformation();
	}

	void SetScale() {
		SetScale(height / 2);
	}

	void SetScale(float x, float y, float z) {
		InitTransformationMatrix();
		tMat[0][0] = x;
		tMat[1][1] = y;
		tMat[2][2] = z;
		CalculateTransformation();
	}

	void SetScale(float s) {
		InitTransformationMatrix();
		tMat[0][0] = s;
		tMat[1][1] = s;
		tMat[2][2] = s;
		CalculateTransformation();
	}

	void RotateX(float r) {
		InitTransformationMatrix();
		tMat[1][1] = cos(r * PI / 180);
		tMat[1][2] = -sin(r * PI / 180);
		tMat[2][1] = sin(r * PI / 180);
		tMat[2][2] = cos(r * PI / 180);
		CalculateTransformation();
	}

	void RotateY(float r) {
		InitTransformationMatrix();
		tMat[0][0] = cos(r * PI / 180);
		tMat[0][2] = sin(r * PI / 180);
		tMat[2][0] = -sin(r * PI / 180);
		tMat[2][2] = cos(r * PI / 180);
		CalculateTransformation();
	}

	void RotateZ(float r) {
		InitTransformationMatrix();
		tMat[0][0] = cos(r * PI / 180);
		tMat[0][1] = -sin(r * PI / 180);
		tMat[1][0] = sin(r * PI / 180);
		tMat[1][1] = cos(r * PI / 180);
		CalculateTransformation();
	}

	float GetPosX() {
		return wMat[0][3];
	}

	float GetPosY() {
		return wMat[1][3];
	}

	float GetPosZ() {
		return wMat[2][3];
	}

private:
	void InitWorldMatrix() {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				if (x == y) {
					wMat[x][y] = 1;
				}
				else {
					wMat[x][y] = 0;
				}
			}
		}
	}

	void InitTransformationMatrix() {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				if (x == y) {
					tMat[x][y] = 1;
				}
				else {
					tMat[x][y] = 0;
				}
			}
		}
	}

	void CalculateTransformation() {
		float r[4][4];

		//calculate result
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				float res = 0;
				for (int k = 0; k < 4; k++) {
					res += wMat[i][k] * tMat[k][j];
				}

				r[i][j] = res;
			}
		}

		//save result into wMat
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				wMat[x][y] = r[x][y];
			}
		}
	}

	void SetVectors() {
		Vertex *ver[8];

		float x, y, z, w;

		x = -1;
		y = 1;
		z = -1;
		w = 1;
		ver[0] = new Vertex(x, y, z, w, color);

		x = -1;
		y = -1;
		z = -1;
		ver[1] = new Vertex(x, y, z, w, color);

		x = 1;
		y = 1;
		z = -1;
		ver[2] = new Vertex(x, y, z, w, color);

		x = 1;
		y = -1;
		z = -1;
		ver[3] = new Vertex(x, y, z, w, color);

		x = -1;
		y = 1;
		z = 1;
		ver[4] = new Vertex(x, y, z, w, color);

		x = -1;
		y = -1;
		z = 1;
		ver[5] = new Vertex(x, y, z, w, color);

		x = 1;
		y = 1;
		z = 1;
		ver[6] = new Vertex(x, y, z, w, color);

		x = 1;
		y = -1;
		z = 1;
		ver[7] = new Vertex(x, y, z, w, color);

		vec[0] = new Vector(ver[0], ver[1], color);
		vec[1] = new Vector(ver[0], ver[2], color);
		vec[2] = new Vector(ver[0], ver[4], color);
		vec[3] = new Vector(ver[1], ver[3], color);
		vec[4] = new Vector(ver[1], ver[5], color);
		vec[5] = new Vector(ver[2], ver[6], color);
		vec[6] = new Vector(ver[2], ver[3], color);
		vec[7] = new Vector(ver[3], ver[7], color);
		vec[8] = new Vector(ver[4], ver[5], color);
		vec[9] = new Vector(ver[4], ver[6], color);
		vec[10] = new Vector(ver[7], ver[5], color);
		vec[11] = new Vector(ver[7], ver[6], color);
	}
};