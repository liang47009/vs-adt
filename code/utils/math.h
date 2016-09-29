#pragma once
class FmVec4 {
public:

	FmVec4() {

	}

	FmVec4(float x, float y, float z, float w) {
		fx = x;
		fy = y;
		fz = z;
		fw = w;
	}

public:
	FmVec4& operator=(const FmVec4& out) {
		fx = out.fx;
		fy = out.fy;
		fz = out.fz;
		fw = out.fw;

		return *this;
	}

private:
	float fx;
	float fy;
	float fz;
	float fw;
};

struct Vertex {
	FmVec4 position;
	FmVec4 color;
};
