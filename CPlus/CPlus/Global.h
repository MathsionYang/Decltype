#pragma once
#include <iostream>
// Derived class
#ifdef CPLUS_EXPORTS
#define CPlusAPI  _declspec(dllexport)
#else
#define CPlusAPI  _declspec(dllimport)
#endif // CPlusAPI

// Derived Function
#ifdef CPLUS_EXPORTS
#define CPlusAPI_C extern "C" __declspec(dllexport)
#else
#define CPlusAPI_C extern "C" __declspec(dllimport)
#endif


