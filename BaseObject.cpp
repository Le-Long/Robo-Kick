#include "pch.h"
#include "BaseObject.h"
#include "Window.h"

BaseObject::BaseObject()
{
	
}

BaseObject::BaseObject(string pathSet)
{
	BaseObject::path = pathSet;
}

void BaseObject::setPos(int xSet, int ySet)
{
	x = xSet;
	y = ySet;
}

void BaseObject::loadObject()
{
	if (!loadImage(path,x,y))
	{
		printf("Failed to load image!\n");
	}
}

int BaseObject::getWidth()
{
	return width;
}

int BaseObject::getHeight()
{
	return height;
}

BaseObject::~BaseObject()
{
	
}	
