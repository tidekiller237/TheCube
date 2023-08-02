#pragma once
class Vertex {
public:
	float x, y, z, w;
	unsigned int color;

	Vertex() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
		color = 0;
	}

	Vertex(float _x, float _y, float _z, float _w, unsigned int c) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		color = c;
	}
};