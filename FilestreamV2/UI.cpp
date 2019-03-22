#include "pch.h"
#include "UI.h"


UI::UI()
{
}


UI::~UI()
{
}

void UI::Start()
{
	std::cout << "Welcome to XML filestream. Please enter the name of the file to open." << std::endl << std::endl;
}

void UI::Filemode()
{
	std::cout << "Choose how to manipulate the chosen file. [R]ead, [W]rite or [e]xit." << std::endl << std::endl;
}

void UI::XMLMenu()
{
	std::cout << "Choose which operation to perform on the file." << std::endl 
		<< "[L]ist current visible nodes." << std::endl 
		<< "[A]dd a new node from your current position." << std::endl 
		<< "[C]hange current position to one of the visible nodes." << std::endl
		<< "[R]emove current node." << std::endl
		<< "[E]xit." << std::endl << std::endl;
}

void UI::ChangeCurrentNode()
{
	std::cout << "Enter the name of the node to switch to. It must be visible from your current position." << std::endl;
}

std::string UI::GetInput()
{
	std::string toReturn;
	getline(std::cin, toReturn);

	return toReturn;
}
