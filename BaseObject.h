#pragma once
#include <string>
using namespace std;

class BaseObject
{
private:
	int x,y;
	int height, width;
	string path;
public:
	BaseObject(string pathSet);
	void setPos(int xSet, int ySet);
	void loadObject();
	int getWidth();
	int getHeight();
	void virtual move() = 0;
	void virtual keyEvent() = 0;
	~BaseObject();
};

