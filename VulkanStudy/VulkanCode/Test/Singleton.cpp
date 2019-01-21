#include "Singleton.h"
#include <iostream>

Singleton * Singleton::ins = 0;
Singleton::Singleton()
{
}


Singleton::~Singleton()
{
}

void Singleton::Log()
{
	std::cout << "hahahahah" << std::endl;
}

Singleton* Singleton::GetInstance()
{
	if (ins == nullptr)
		ins = new Singleton();

	return ins;
}
