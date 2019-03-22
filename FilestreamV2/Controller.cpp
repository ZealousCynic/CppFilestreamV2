#include "pch.h"
#include "Controller.h"

//TEST SECTION

#include <string>
#include <iostream>
#include <map>

#pragma region StringMapping

enum XMLStringValues
{
	AddNode,
	ChangeCurrentNode,
	ListVisibleNodes,
	RemoveNode,
	AddAttribute,
	ModifyAttribute,
	RemoveAttribute,
	evEnd
};

enum MenuStringValues
{
	Read,
	Write,
	End
};

std::map<std::string, XMLStringValues> s_mapXMLMenuStringValues;
std::map<std::string, MenuStringValues> s_mapMenuStringValues;

void Controller::Initialize()
{
	s_mapMenuStringValues["r"] = Read;
	s_mapMenuStringValues["w"] = Write;
	s_mapMenuStringValues["e"] = End;

	s_mapXMLMenuStringValues["a"] = AddNode;
	s_mapXMLMenuStringValues["c"] = ChangeCurrentNode;
	s_mapXMLMenuStringValues["l"] = ListVisibleNodes;
	s_mapXMLMenuStringValues["r"] = RemoveNode;
	s_mapXMLMenuStringValues["e"] = evEnd;
}

#pragma endregion

//

Controller::Controller()
{
	Initialize();
}


Controller::~Controller()
{
}

int Controller::Start()
{
	std::string input;

	ui.Start();
	input = ui.GetInput();
	input.append(".xml");
	fs.Filepick(input);
	fs.Read();

	while (true)
	{
		ui.Filemode();
		input = ui.GetInput();

		switch (s_mapMenuStringValues[input])
		{
		case  Read:
			fs.Read();
			fs.PrintXMLNodes(fs.currentNode);
			break;
		case Write:
			XMLMenu();
			break;
		case End:
			return 0;
		default:
			break;
		}
	}

}

void Controller::XMLMenu()
{
	std::string input;

	while (true)
	{
		ui.XMLMenu();
		input = ui.GetInput();

		switch (s_mapXMLMenuStringValues[input])
		{
		case AddNode:
			XMLAddNode();
			break;
		case ChangeCurrentNode:
			ui.ChangeCurrentNode();
			fs.PrintFamily();
			input = ui.GetInput();
			fs.ChangeCurrentNode(&input);
			break;
		case ListVisibleNodes:
			fs.PrintFamily();
			break;
		case RemoveNode:
			fs.RemoveNode();
			break;
		case evEnd:
			return;
		default:
			break;
		}
	}
}

std::string Controller::GetInput()
{
	return ui.GetInput();
}

void Controller::XMLAddNode()
{
	std::string input;
	std::string toAddName;
	std::string toAddValue;

	input = ui.GetInput();
	if (input != "")
	{
		toAddName = input;

		input = ui.GetInput();

		if (input != "")
		{
			toAddValue = input;
			fs.AddNode(toAddName, toAddValue);
		}
		else
			fs.AddNode(toAddName);
	}
}
