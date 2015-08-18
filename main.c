#include <stdio.h>

#include "fiber.h"

static Fiber fbrmain, fbrf0, fbrf1;

void f0(void)
{
	printf("<f0-0>\n");
	SwitchFiber(&fbrf0, &fbrmain);
	printf("<f0-1>\n");
	SwitchFiber(&fbrf0, &fbrmain);
}

void f1(void)
{
	printf("#f1-0#\n");
	SwitchFiber(&fbrf1, &fbrmain);
	printf("#f1-1#\n");
	SwitchFiber(&fbrf1, &fbrmain);
}

int main(int argc, char * argv[])
{
	InitMainFiber(&fbrmain);
	InitFiber(&fbrf0, f0);
	InitFiber(&fbrf1, f1);
	printf("@main-0@\n");
	SwitchFiber(&fbrmain, &fbrf0);
	printf("@main-1@\n");
	SwitchFiber(&fbrmain, &fbrf1);
	printf("@main-2@\n");
	SwitchFiber(&fbrmain, &fbrf0);
	printf("@main-3@\n");
	SwitchFiber(&fbrmain, &fbrf1);
	printf("@main-4@\n");
	return 0;
}
