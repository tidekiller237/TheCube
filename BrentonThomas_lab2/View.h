#pragma once

#include <corecrt_math.h>

#define PI 3.14159265

class View {
public:
	float wMat[4][4];
	float vMat[4][4];
	float tMat[4][4];
	float pMat[4][4];

	View(float z_off, float x_rot) {
		InitWorldMatrix();

		InitTransformationMatrix();
		tMat[1][1] = cos(x_rot * PI / 180);
		tMat[1][2] = -(sin(x_rot * PI / 180));
		tMat[2][1] = sin(x_rot * PI / 180);
		tMat[2][2] = cos(x_rot * PI / 180);
		CalculateTransformation();

		InitTransformationMatrix();
		tMat[3][2] = -z_off;
		CalculateTransformation();


		SetViewMatrix();
	}

	void BuildProjectionMatrix(float vertFov, float aspectRatio, float zNear, float zFar) {
		if (zNear > 0 && zFar > zNear) {

			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					pMat[x][y] = 0;
				}
			}

			/*
			{	Xscale	,		0	,		0								,		0	}
			{	0		,	Yscale	,									0	,		0	}
			{	0		,		0	,	zFar / (zfar - zNear)				,		1	}
			{	0		,		0	,	-(zFar * zNear) / (zFar - zNear)	,		0	}
			*/

			pMat[1][1] = 1 / tan((vertFov / 2) * PI / 180);
			pMat[0][0] = pMat[1][1] * aspectRatio;
			pMat[2][2] = zFar / (zFar - zNear);
			pMat[3][2] = -(zFar * zNear) / (zFar - zNear);
			pMat[2][3] = 1;
		}
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

	void SetViewMatrix() {

		////transpose
		//for (int y = 0; y < 4; y++) {
		//	for (int x = 0; x < 4; x++) {
		//		vMat[y][x] = wMat[x][y];
		//	}
		//}

		float r[4][4];

		//transpose rotation
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				if (x < 3 && y < 3) {
					r[y][x] = wMat[x][y];
				}
				else {
					r[x][y] = wMat[x][y];
				}
			}
		}

		//negate position
		r[3][0] = (-wMat[3][0] * r[0][0]) + (-wMat[3][1] * r[1][0]) + (-wMat[3][2] * r[2][0]);
		r[3][1] = (-wMat[3][0] * r[0][1]) + (-wMat[3][1] * r[1][1]) + (-wMat[3][2] * r[2][1]);
		r[3][2] = (-wMat[3][0] * r[0][2]) + (-wMat[3][1] * r[1][2]) + (-wMat[3][2] * r[2][2]);

		//set matrix
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				vMat[x][y] = r[x][y];
			}
		}

		/*float a2323 = wMat[2][2] * wMat[3][3] - wMat[2][3] * wMat[3][2];
		float a1323 = wMat[2][1] * wMat[3][3] - wMat[2][3] * wMat[3][1];
		float a1223 = wMat[2][1] * wMat[3][2] - wMat[2][2] * wMat[3][1];
		float a0323 = wMat[2][0] * wMat[3][3] - wMat[2][3] * wMat[3][0];
		float a0223 = wMat[2][0] * wMat[3][2] - wMat[2][3] * wMat[3][0];
		float a0123 = wMat[2][0] * wMat[3][1] - wMat[2][1] * wMat[3][0];
		float a2313 = wMat[1][2] * wMat[3][3] - wMat[1][3] * wMat[3][2];
		float a1313 = wMat[1][1] * wMat[3][3] - wMat[1][3] * wMat[3][1];
		float a1213 = wMat[1][1] * wMat[3][2] - wMat[1][2] * wMat[3][1];
		float a2312 = wMat[1][2] * wMat[2][3] - wMat[1][3] * wMat[2][2];
		float a1312 = wMat[1][1] * wMat[2][3] - wMat[1][3] * wMat[2][1];
		float a1212 = wMat[1][1] * wMat[2][2] - wMat[1][2] * wMat[2][1];
		float a0313 = wMat[1][0] * wMat[3][3] - wMat[1][3] * wMat[3][0];
		float a0213 = wMat[1][0] * wMat[3][2] - wMat[1][2] * wMat[3][0];
		float a0312 = wMat[1][0] * wMat[2][3] - wMat[1][3] * wMat[2][0];
		float a0212 = wMat[1][0] * wMat[2][2] - wMat[1][2] * wMat[2][0];
		float a0113 = wMat[1][0] * wMat[3][1] - wMat[1][1] * wMat[3][0];
		float a0112 = wMat[1][0] * wMat[2][1] - wMat[1][1] * wMat[2][0];

		float det = wMat[0][0] *
			(wMat[1][1] * a2323 - wMat[1][2] * a1323 + wMat[1][3] * a1223)
			- wMat[0][1] * 
			(wMat[1][0] * a2323 - wMat[1][2] * a0323 + wMat[1][3] * a0223)
			+ wMat[0][2] *
			(wMat[1][0] * a1323 - wMat[1][1] * a0323 + wMat[1][3] * a0123)
			- wMat[0][3] *
			(wMat[1][0] * a1223 - wMat[1][1] * a0223 + wMat[1][2] * a0123);
		det = 1 / det;

		vMat[0][0] = det * (wMat[1][1] * a2323 - wMat[1][2] * a1323 + wMat[1][3] * a1223);
		vMat[0][1] = det * -(wMat[0][1] * a2323 - wMat[0][2] * a1323 + wMat[0][3] * a1223);
		vMat[0][2] = det * (wMat[0][1] * a2313 - wMat[0][2] * a1313 + wMat[0][3] * a1213);
		vMat[0][3] = det * -(wMat[0][1] * a2312 - wMat[0][2] * a1312 + wMat[0][3] * a1212);
		vMat[1][0] = det * -(wMat[1][0] * a2323 - wMat[1][2] * a0323 + wMat[1][3] * a0223);
		vMat[1][1] = det * (wMat[0][0] * a2323 - wMat[0][2] * a0323 + wMat[0][3] * a0223);
		vMat[1][2] = det * -(wMat[0][0] * a2313 - wMat[0][2] * a0313 + wMat[0][3] * a0213);
		vMat[1][3] = det * (wMat[0][0] * a2312 - wMat[0][2] * a0312 + wMat[0][3] * a0212);
		vMat[2][0] = det * (wMat[1][0] * a1323 - wMat[1][1] * a0323 + wMat[1][3] * a0123);
		vMat[2][1] = det * -(wMat[0][0] * a1323 - wMat[0][1] * a0323 + wMat[0][3] * a0123);
		vMat[2][2] = det * (wMat[0][0] * a1313 - wMat[0][1] * a0313 + wMat[0][3] * a0113);
		vMat[2][3] = det * -(wMat[0][0] * a1312 - wMat[0][1] * a0312 + wMat[0][3] * a0112);
		vMat[3][0] = det * -(wMat[1][0] * a1223 - wMat[1][1] * a0223 + wMat[1][2] * a0123);
		vMat[3][1] = det * (wMat[0][0] * a1223 - wMat[0][1] * a0223 + wMat[0][2] * a0123);
		vMat[3][2] = det * -(wMat[0][0] * a1213 - wMat[0][1] * a0213 + wMat[0][2] * a0113);
		vMat[3][3] = det * (wMat[0][0] * a1212 - wMat[0][1] * a0212 + wMat[0][2] * a0112);*/

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
};