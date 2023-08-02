#pragma once

#include "Vector.h"

#define PI 3.14159265

class Grid {
public:
	float wMat[4][4];
	float tMat[4][4];
	Vector* vec[22];
	const int vecSize = 22;
	float width, depth;
	unsigned int color;

	Grid() {
		color = 0;
		width = 1;
		depth = 1;

		InitWorldMatrix();
		SetVectors();
	}

	Grid(float w, float d, unsigned int c) {
		color = c;
		width = w;
		depth = d;

		InitWorldMatrix();
		SetVectors();
	}
	
	~Grid() {
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
		SetScale(width / 2, 1, depth / 2);
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
		Vertex *ver[40];
		float offset = 0.2; 
		float x, y, z, w;
		y = 0;
		w = 1;

		x = -1;
		z = -1;
		ver[0] = new Vertex(x, y, z, w, color);

		x = 1;
		z = -1;
		ver[10] = new Vertex(x, y, z, w, color);

		x = -1;
		z = 1;
		ver[11] = new Vertex(x, y, z, w, color);

		x = 1;
		z = 1;
		ver[21] = new Vertex(x, y, z, w, color);

		//============================================
		
		x = -1 + (offset * 1);
		z = -1;
		ver[1] = new Vertex(x, y, z, w, color);

		x = -1 + (offset * 2);
		z = -1;
		ver[2] = new Vertex(x, y, z, w, color);

		x = -1 + (offset * 3);
		z = -1;
		ver[3] = new Vertex(x, y, z, w, color);

		x = -1 + (offset * 4);
		z = -1;
		ver[4] = new Vertex(x, y, z, w, color);

		x = 0;
		z = -1;
		ver[5] = new Vertex(x, y, z, w, color);

		x = 1 - (offset * 4);
		z = -1;
		ver[6] = new Vertex(x, y, z, w, color);

		x = 1 - (offset * 3);
		z = -1;
		ver[7] = new Vertex(x, y, z, w, color);

		x = 1 - (offset * 2);
		z = -1;
		ver[8] = new Vertex(x, y, z, w, color);

		x = 1 - (offset * 1);
		z = -1;
		ver[9] = new Vertex(x, y, z, w, color);

		//============================================

		x = -1 + (offset * 1);
		z = 1;
		ver[12] = new Vertex(x, y, z, w, color);

		x = -1 + (offset * 2);
		z = 1;
		ver[13] = new Vertex(x, y, z, w, color);

		x = -1 + (offset * 3);
		z = 1;
		ver[14] = new Vertex(x, y, z, w, color);

		x = -1 + (offset * 4);
		z = 1;
		ver[15] = new Vertex(x, y, z, w, color);

		x = 0;
		z = 1;
		ver[16] = new Vertex(x, y, z, w, color);

		x = 1 - (offset * 4);
		z = 1;
		ver[17] = new Vertex(x, y, z, w, color);

		x = 1 - (offset * 3);
		z = 1;
		ver[18] = new Vertex(x, y, z, w, color);

		x = 1 - (offset * 2);
		z = 1;
		ver[19] = new Vertex(x, y, z, w, color);

		x = 1 - (offset * 1);
		z = 1;
		ver[20] = new Vertex(x, y, z, w, color);

		//============================================

		z = -1 + (offset * 1);
		x = -1;
		ver[22] = new Vertex(x, y, z, w, color);

		z = -1 + (offset * 2);
		x = -1;
		ver[23] = new Vertex(x, y, z, w, color);

		z = -1 + (offset * 3);
		x = -1;
		ver[24] = new Vertex(x, y, z, w, color);

		z = -1 + (offset * 4);
		x = -1;
		ver[25] = new Vertex(x, y, z, w, color);

		z = 0;
		x = -1;
		ver[26] = new Vertex(x, y, z, w, color);

		z = 1 - (offset * 4);
		x = -1;
		ver[27] = new Vertex(x, y, z, w, color);

		z = 1 - (offset * 3);
		x = -1;
		ver[28] = new Vertex(x, y, z, w, color);

		z = 1 - (offset * 2);
		x = -1;
		ver[29] = new Vertex(x, y, z, w, color);

		z = 1 - (offset * 1);
		x = -1;
		ver[30] = new Vertex(x, y, z, w, color);

		//============================================

		z = -1 + (offset * 1);
		x = 1;
		ver[31] = new Vertex(x, y, z, w, color);

		z = -1 + (offset * 2);
		x = 1;
		ver[32] = new Vertex(x, y, z, w, color);

		z = -1 + (offset * 3);
		x = 1;
		ver[33] = new Vertex(x, y, z, w, color);

		z = -1 + (offset * 4);
		x = 1;
		ver[34] = new Vertex(x, y, z, w, color);

		z = 0;
		x = 1;
		ver[35] = new Vertex(x, y, z, w, color);

		z = 1 - (offset * 4);
		x = 1;
		ver[36] = new Vertex(x, y, z, w, color);

		z = 1 - (offset * 3);
		x = 1;
		ver[37] = new Vertex(x, y, z, w, color);

		z = 1 - (offset * 2);
		x = 1;
		ver[38] = new Vertex(x, y, z, w, color);

		z = 1 - (offset * 1);
		x = 1;
		ver[39] = new Vertex(x, y, z, w, color);

		vec[0] = new Vector(ver[0], ver[11], color);
		vec[1] = new Vector(ver[1], ver[12], color);
		vec[2] = new Vector(ver[2], ver[13], color);
		vec[3] = new Vector(ver[3], ver[14], color);
		vec[4] = new Vector(ver[4], ver[15], color);
		vec[5] = new Vector(ver[5], ver[16], color);
		vec[6] = new Vector(ver[6], ver[17], color);
		vec[7] = new Vector(ver[7], ver[18], color);
		vec[8] = new Vector(ver[8], ver[19], color);
		vec[9] = new Vector(ver[9], ver[20], color);
		vec[10] = new Vector(ver[10], ver[21], color);

		vec[11] = new Vector(ver[22], ver[31], color);
		vec[12] = new Vector(ver[23], ver[32], color);
		vec[13] = new Vector(ver[24], ver[33], color);
		vec[14] = new Vector(ver[25], ver[34], color);
		vec[15] = new Vector(ver[26], ver[35], color);
		vec[16] = new Vector(ver[27], ver[36], color);
		vec[17] = new Vector(ver[28], ver[37], color);
		vec[18] = new Vector(ver[29], ver[38], color);
		vec[19] = new Vector(ver[30], ver[39], color);

		vec[20] = new Vector(ver[0], ver[10], color);
		vec[21] = new Vector(ver[11], ver[21], color);
	}
};