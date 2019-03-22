#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

class Filestream
{
public:
	Filestream();
	~Filestream();

	//FILE ACCESS
	void Filepick(std::string input);
	void OpenFile();
	void Read();

	//XML FUNCTIONALITY
	void ChangeCurrentNode(std::string* input);
	void AddNode(std::string name);
	void AddNode(std::string name, std::string value);
	void AddAttribute(std::string* name);
	void AddAttribute(std::string* name, std::string* value);
	void ModifyAttribute(std::string* name, std::string* value);
	void RemoveAttribute(std::string* name);
	void RemoveNode();

	//PRINT FUNCTIONS
	void PrintSiblings();
	void PrintChildren();
	void PrintFamily();
	void PrintParent();
	void PrintXMLNodes(rapidxml::xml_node<>* toPrint);

	//CurrentNode is the basis for ALL navigation performed by this application. If it isn't set, navigation breaks.
	rapidxml::xml_node<>* currentNode;

private:
	
	//Filestream for accessing file.
	std::fstream fs;

	//Vector to store the chars read from file - vector is array<char> of varying size.
	std::vector<char> buffer;
	
	//Object to store the XML Document-Object-Model.
	rapidxml::xml_document<> doc;

	//File to open as string.
	std::string file;


	//FUNCTIONS
	rapidxml::xml_node<>* SearchNode(std::string* toSearch);
	void Save();
};

