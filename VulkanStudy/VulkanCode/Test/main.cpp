#include <iostream>
#include "Singleton.h"




int main() {



	Singleton* s =  Singleton ::GetInstance();

	s->Log();

	return 0;
}