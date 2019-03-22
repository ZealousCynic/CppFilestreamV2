#pragma once
#include "Filestream.h"
#include "UI.h"

//TEST SECTION
#include <rapidxml/rapidxml.hpp>

class Controller
{
public:
	Controller();
	~Controller();

	int Start();

private:

	UI ui;
	Filestream fs;
	rapidxml::xml_node<>* temp;
	
	void Initialize();
	void XMLMenu();
	void XMLAddNode();
	std::string GetInput();
};

