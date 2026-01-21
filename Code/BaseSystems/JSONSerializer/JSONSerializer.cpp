#include "JSONSerializer.hpp"

#include <iostream>
#include <fstream>

bool JSONSerializer::WriteIntoFile(std::string fileName, WriteFunction function)
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open())
	{
		std::cout << fileName << " could not be opened." << std::endl;
		return false;
	}

	rapidjson::OStreamWrapper osw(ofs);
	rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);

	function(writer);
	return true;
}

bool JSONSerializer::ReadFromFile(std::string fileName, ReadFunction function)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		std::cout << fileName << " could not be opened." << std::endl;
		return false;
	}

	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document doc;
	doc.ParseStream(isw);
	if (!doc.IsObject())
	{
		std::cout << fileName << " is not a valid JSON file" << std::endl;
		return false;
	}

	function(doc);
	return false;
}

rapidjson::Document JSONSerializer::ReadDocument(std::string fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		std::cout << fileName << " could not be opened." << std::endl;
		return nullptr;
	}

	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document doc;
	doc.ParseStream(isw);
	if (!doc.IsObject())
	{
		std::cout << fileName << " is not a valid JSON file" << std::endl;
		return nullptr;
	}
	
	return doc;
}

JSONSerializer::JSONSerializer()
{
}

JSONSerializer::~JSONSerializer()
{
}
