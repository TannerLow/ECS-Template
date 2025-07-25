#pragma once
#include <Core/System.h>

class Reporter : public System {
public:
	System::entities;

public:
	void report();
};