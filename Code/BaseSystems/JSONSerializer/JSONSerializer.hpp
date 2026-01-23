#pragma once

#include <functional>
#include <string>
#include "../../JSONSerializer_WZBJ_Pak.hpp"

typedef std::function<void(rapidjson::PrettyWriter<rapidjson::OStreamWrapper>&)> WriteFunction;
typedef std::function<void(rapidjson::Document&)> ReadFunction;

class JSONSerializer
{
public:
	// Write into a JSON file
	bool WriteIntoFile(std::string fileName, WriteFunction function);
	
	// Read from a JSON file
	bool ReadFromFile(std::string fileName, ReadFunction function);

	// 
	rapidjson::Document ReadDocument(std::string fileName);

	// Constructor
	JSONSerializer() {};
	// Destructor
	~JSONSerializer() {};
};

