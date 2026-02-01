#pragma once

#include <functional>
#include <string>
#include "../../JSONSerializer_WZBJ_Pak.hpp"

using WriteFunction = std::function<void(rapidjson::PrettyWriter<rapidjson::OStreamWrapper>&)>;
using ReadFunction = std::function<void(rapidjson::Document&)>;

class JSONSerializer
{
public:
	// Write into a JSON file
	bool WriteIntoFile(std::string fileName, WriteFunction function);

	// Read from a JSON file
	bool ReadFromFile(std::string fileName, ReadFunction function);

	// Create and Parse rapidjson Document from a JSON file
	rapidjson::Document ReadDocument(std::string fileName);

	// Constructor
	JSONSerializer() {};
	// Destructor
	~JSONSerializer() {};
};

