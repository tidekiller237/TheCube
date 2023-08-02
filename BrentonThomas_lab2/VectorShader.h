#pragma once

#include "Vector.h"
#include "View.h"

class VectorShader {
public:
	View* view;
	

	VectorShader(View* v) {
		view = v;
	}

	Vertex* ApplyShader(Vertex* v, Cube* cube) {
		Vertex* wVer = new Vertex();
		Vertex* vVer = new Vertex();
		Vertex* pVer = new Vertex();

		wVer->x = v->x * cube->wMat[0][0] + v->y * cube->wMat[1][0] + v->z * cube->wMat[2][0] + v->w * cube->wMat[3][0];
		wVer->y = v->x * cube->wMat[0][1] + v->y * cube->wMat[1][1] + v->z * cube->wMat[2][1] + v->w * cube->wMat[3][1];
		wVer->z = v->x * cube->wMat[0][2] + v->y * cube->wMat[1][2] + v->z * cube->wMat[2][2] + v->w * cube->wMat[3][2];
		wVer->w = v->x * cube->wMat[0][3] + v->y * cube->wMat[1][3] + v->z * cube->wMat[2][3] + v->w * cube->wMat[3][3];

		vVer->x = wVer->x * view->vMat[0][0] + wVer->y * view->vMat[1][0] + wVer->z * view->vMat[2][0] + wVer->w * view->vMat[3][0];
		vVer->y = wVer->x * view->vMat[0][1] + wVer->y * view->vMat[1][1] + wVer->z * view->vMat[2][1] + wVer->w * view->vMat[3][1];
		vVer->z = wVer->x * view->vMat[0][2] + wVer->y * view->vMat[1][2] + wVer->z * view->vMat[2][2] + wVer->w * view->vMat[3][2];
		vVer->w = wVer->x * view->vMat[0][3] + wVer->y * view->vMat[1][3] + wVer->z * view->vMat[2][3] + wVer->w * view->vMat[3][3];

		pVer->x = vVer->x * view->pMat[0][0] + vVer->y * view->pMat[1][0] + vVer->z * view->pMat[2][0] + vVer->w * view->pMat[3][0];
		pVer->y = vVer->x * view->pMat[0][1] + vVer->y * view->pMat[1][1] + vVer->z * view->pMat[2][1] + vVer->w * view->pMat[3][1];
		pVer->z = vVer->x * view->pMat[0][2] + vVer->y * view->pMat[1][2] + vVer->z * view->pMat[2][2] + vVer->w * view->pMat[3][2];
		pVer->w = vVer->x * view->pMat[0][3] + vVer->y * view->pMat[1][3] + vVer->z * view->pMat[2][3] + vVer->w * view->pMat[3][3];

		pVer->x = (pVer->x + 1) * (500 / 2) - 250;
		pVer->y = (1 - pVer->y) * (500 / 2) - 250;

		pVer->x = pVer->x / pVer->w;
		pVer->y = pVer->y / pVer->w;

		return pVer;
	}

	Vertex* ApplyShader(Vertex* v, Grid* grid) {
		Vertex* wVer = new Vertex();
		Vertex* vVer = new Vertex();
		Vertex* pVer = new Vertex();

		wVer->x = v->x * grid->wMat[0][0] + v->y * grid->wMat[1][0] + v->z * grid->wMat[2][0] + v->w * grid->wMat[3][0];
		wVer->y = v->x * grid->wMat[0][1] + v->y * grid->wMat[1][1] + v->z * grid->wMat[2][1] + v->w * grid->wMat[3][1];
		wVer->z = v->x * grid->wMat[0][2] + v->y * grid->wMat[1][2] + v->z * grid->wMat[2][2] + v->w * grid->wMat[3][2];
		wVer->w = v->x * grid->wMat[0][3] + v->y * grid->wMat[1][3] + v->z * grid->wMat[2][3] + v->w * grid->wMat[3][3];

		vVer->x = wVer->x * view->vMat[0][0] + wVer->y * view->vMat[1][0] + wVer->z * view->vMat[2][0] + wVer->w * view->vMat[3][0];
		vVer->y = wVer->x * view->vMat[0][1] + wVer->y * view->vMat[1][1] + wVer->z * view->vMat[2][1] + wVer->w * view->vMat[3][1];
		vVer->z = wVer->x * view->vMat[0][2] + wVer->y * view->vMat[1][2] + wVer->z * view->vMat[2][2] + wVer->w * view->vMat[3][2];
		vVer->w = wVer->x * view->vMat[0][3] + wVer->y * view->vMat[1][3] + wVer->z * view->vMat[2][3] + wVer->w * view->vMat[3][3];

		pVer->x = vVer->x * view->pMat[0][0] + vVer->y * view->pMat[1][0] + vVer->z * view->pMat[2][0] + vVer->w * view->pMat[3][0];
		pVer->y = vVer->x * view->pMat[0][1] + vVer->y * view->pMat[1][1] + vVer->z * view->pMat[2][1] + vVer->w * view->pMat[3][1];
		pVer->z = vVer->x * view->pMat[0][2] + vVer->y * view->pMat[1][2] + vVer->z * view->pMat[2][2] + vVer->w * view->pMat[3][2];
		pVer->w = vVer->x * view->pMat[0][3] + vVer->y * view->pMat[1][3] + vVer->z * view->pMat[2][3] + vVer->w * view->pMat[3][3];

		pVer->x = (pVer->x + 1) * (500 / 2) - 250;
		pVer->y = (1 - pVer->y) * (500 / 2) - 250;

		pVer->x = pVer->x / pVer->w;
		pVer->y = pVer->y / pVer->w;

		return pVer;
	}
};