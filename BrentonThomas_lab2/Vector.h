#pragma once

#include "Vertex.h"

class Vector {
public:
	Vertex* start;
	Vertex* end;
	unsigned int color;

	Vector() {
		start = new Vertex();
		end = new Vertex();
		color = 0;
	}

	Vector(Vertex* s, Vertex* e, unsigned int c) {
		start = s;
		end = e;
		color = c;
	}

	Vector(float sX, float sY, float sZ, float sW, float eX, float eY, float eZ, float eW, unsigned int c) {
		start = new Vertex(sX, sY, sZ, sW, c);
		end = new Vertex(eX, eY, eZ, eW, c);
		color = c;
	}
};