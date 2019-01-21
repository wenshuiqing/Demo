#pragma once
class Singleton
{


private:
	static Singleton* ins;
	Singleton();
	~Singleton();


public:
	void Log();

	static Singleton* GetInstance();
};

