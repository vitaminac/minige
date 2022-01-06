#pragma once
#ifdef MINIGE_EXPORTS
#define SO_API __declspec(dllexport)
#else
#define SO_API __declspec(dllimport)
#endif