#pragma once
// 1. Define the triangle vertices
struct FVertexSimple
{
	float x, y, z;    // Position
	float r, g, b, a; // Color
};

struct FVector
{
	float x, y, z;
	FVector(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {};
};

enum ETypePrimitive
{
	EPT_Triangle,
	EPT_Cube,
	EPT_Sphere,
	EPT_Max,
};
