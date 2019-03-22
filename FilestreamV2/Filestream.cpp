#include "pch.h"
#include "Filestream.h"


//TEST SECTION

#include <iostream>
//

//PLANS FOR REFACTORING
//
//+ MODIFY FUNCTIONS TO RETURN VALUES
//+ USE RETURN VALUES IN UI TO PRINT TO SCREEN
//


//TO ADD
//
//MODIFY NODE
//NODE ATTRIBUTES
//

Filestream::Filestream()
{
}


Filestream::~Filestream()
{
}

void Filestream::Filepick(std::string input)
{
	//I could proabably just tell the constructor to expect a string argument and to point to that as file.
	//Might cause issues with lifetime of string.
	//Get/set as alternative.
	file = input;
}

void Filestream::Read()
{
	fs.open(file, std::ios::in);

	//Call assign because the vector is already constructed.
	buffer.assign((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());

	//Add \0 to the end of the vector.
	buffer.push_back('\0');

	//Tell doc to parse the vector, using 0 as a the terminator. I think.
	doc.parse<0>(&buffer[0]);

	if (currentNode = nullptr)
		currentNode = doc.first_node();

	fs.close();
}

//Overloaded function for adding nodes - with and without values assigned.
void Filestream::AddNode(std::string name)
{
	rapidxml::xml_node<>* toAdd = doc.allocate_node(rapidxml::node_element, name.c_str());
	if (currentNode != nullptr)
		currentNode->append_node(toAdd);
	else
		doc.append_node(toAdd);

	Save();
}

void Filestream::AddNode(std::string name, std::string value)
{
	rapidxml::xml_node<>* toAdd = doc.allocate_node(rapidxml::node_element, name.c_str(), value.c_str());
	if (currentNode != nullptr)
	{
		currentNode->append_node(toAdd);
	}
	else
	{
		doc.append_node(toAdd);
	}

	Save();
}

//Overloaded function for adding attributes to nodes, with and without values.
void Filestream::AddAttribute(std::string* name)
{
	rapidxml::xml_attribute<>* toAdd = doc.allocate_attribute(name->c_str());
	if (currentNode != nullptr)
		currentNode->append_attribute(toAdd);
}

void Filestream::AddAttribute(std::string* name, std::string* value)
{
	rapidxml::xml_attribute<>* toAdd = doc.allocate_attribute(name->c_str(), value->c_str());
	if (currentNode != nullptr)
		currentNode->append_attribute(toAdd);
}

void Filestream::ModifyAttribute(std::string* name, std::string* value)
{
	//Attribute values are not mutable - insert new attribute, delete the old?
	if (currentNode == nullptr)
		return;

	rapidxml::xml_attribute<>* toModify;
	if (currentNode->first_attribute(name->c_str()))
		toModify = currentNode->first_attribute(name->c_str());
}

//Check if the attribute exists - if it does, remove it (first_attribute returns the needed pointer).
void Filestream::RemoveAttribute(std::string* name)
{
	if (currentNode == nullptr)
		return;

	if (currentNode->first_attribute(name->c_str()))
	{
		currentNode->remove_attribute(currentNode->first_attribute(name->c_str()));
	}
}

//Assign a temporary node. Set current node to parent. Remove temporary node.
void Filestream::RemoveNode()
{
	rapidxml::xml_node<>* toRemove = currentNode;
	currentNode = currentNode->parent();
	currentNode->remove_node(toRemove);

	Save();
}

void Filestream::ChangeCurrentNode(std::string * input)
{
	if (!currentNode)
		currentNode = doc.first_node();
	std::cout << currentNode->name() << '>' << std::endl << std::endl;

	PrintFamily();

	currentNode = SearchNode(input);
	std::cout << "New location: " << currentNode->name() << std::endl << std::endl;
}

void Filestream::PrintXMLNodes(rapidxml::xml_node<>* toPrint)
{
	for (toPrint; toPrint; toPrint = toPrint->next_sibling())
	{
		std::cout << toPrint->name() << " " << toPrint->value() << std::endl;

		if (toPrint->first_node())
			PrintXMLNodes(toPrint->first_node());
	}
}

//LOTS of if/elseif comparisons against string values. Return node with matching name, if no match, return to document root.
rapidxml::xml_node<>* Filestream::SearchNode(std::string* toSearch)
{
	std::string toCompare = currentNode->parent()->name();

	if (currentNode->first_node(toSearch->c_str()))
		return currentNode->first_node(toSearch->c_str());
	else if (currentNode->next_sibling(toSearch->c_str()))
		return currentNode->next_sibling(toSearch->c_str());
	else if (currentNode->previous_sibling(toSearch->c_str()))
		return currentNode->previous_sibling(toSearch->c_str());
	else if (toCompare.compare(toSearch->c_str()) == 0)
		return currentNode->parent();
	std::cout << std::endl << std::endl << "\t\t\tError: Current node set to document root." << std::endl << std::endl;
	return doc.first_node();
}

//Create an out-file-stream, passing in file path to the constructor. If it succeeds, write doc to file.
void Filestream::Save()
{
	std::ofstream outFile(file);

	if (outFile)
	{
		outFile << doc;
		outFile.close();

		Read();
	}
}

//PRINT FUNCTIONS
//NEEDS REFACTORING TO RETURN STRING VALUES TO CONTROLLER.

void Filestream::PrintParent()
{
	std::cout << currentNode->parent()->name() << std::endl;
}

void Filestream::PrintSiblings()
{
	for (rapidxml::xml_node<>* temp = currentNode; temp; temp = temp->next_sibling())
		std::cout << '\t' << temp->name() << std::endl;
}

void Filestream::PrintChildren()
{
	for (rapidxml::xml_node<>* temp = currentNode->first_node(); temp; temp = temp->next_sibling())
		std::cout << "\t\t" << temp->name() << std::endl;
}

void Filestream::PrintFamily()
{
	if (currentNode == nullptr)
		currentNode = doc.first_node();

	PrintParent();
	for (rapidxml::xml_node<>* temp = currentNode->parent()->first_node(); temp; temp = temp->next_sibling())
	{
		temp == currentNode ? std::cout << '\t' << '>' << temp->name() << std::endl : std::cout << '\t' << temp->name() << std::endl;
		if (temp == currentNode)
			PrintChildren();
	}
	std::cout << '\n';
}