#pragma once

#include <functional>
#include "../../JSONSerializer_WZBJ_Pak.hpp"

typedef std::function<void(rapidjson::PrettyWriter<rapidjson::FileWriteStream>&)> WriteFunction;
typedef std::function<void(rapidjson::Document&)> ReadFunction;

class JSONSerializer
{
private:
	// Max buffer size
	enum { MAX_BUFFER_SIZE = 2048 };

public:
	// Write into a JSON file
	bool WriteIntoFile(const char *fileName, WriteFunction function);
	
	// Read from a JSON file
	bool ReadFromFile(const char* fileName, ReadFunction function);

	// Constructor
	JSONSerializer();
	// Destructor
	~JSONSerializer();
};

