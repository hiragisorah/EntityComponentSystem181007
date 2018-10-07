#include "engine.h"

int main(void)
{
	ECS::Engine engine;

	engine.Run();

	rewind(stdin);
	getchar();
}