// TestingDLL.cpp : Defines the exported functions for the DLL.
//

#include "framework.h"
#include "TestingDLL.h"


// This is an example of an exported variable
TESTINGDLL_API int nTestingDLL=0;

// This is an example of an exported function.
TESTINGDLL_API int fnTestingDLL(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CTestingDLL::CTestingDLL()
{
    return;
}


