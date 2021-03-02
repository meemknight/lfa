#include <iostream>
#include <stdio.h>

#ifdef PLATFORM_WIN32
#include <Windows.h>
#endif

#undef min
#undef max


int main()
{

#ifdef PLATFORM_WIN32
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	std::cout.sync_with_stdio();
#endif

	std::cout << "test\n";

	int a;
	std::cin >> a;



	std::cin.ignore();
	std::cin.get();
}