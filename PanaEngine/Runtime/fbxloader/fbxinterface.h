#pragma once

class Mesh;
class FbxInterface
{
public:
	static Mesh* Import(const char *file);
};