#include "syscall.h"

main()
{
	int n;
	for (n = 1; n < 5; ++n)
    {
        Sleep(100000);
		Example(n);
    }
}
