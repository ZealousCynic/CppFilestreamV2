#pragma once
#include <string>
#include <iostream>

class UI
{
public:
	UI();
	~UI();

	void Start();
	std::string GetInput();
	void Filemode();
	void XMLMenu();
	void ChangeCurrentNode();
};

