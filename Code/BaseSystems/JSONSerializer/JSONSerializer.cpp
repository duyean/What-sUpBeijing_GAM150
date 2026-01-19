#include "JSONSerializer.hpp"

#include <iostream>
#include <array>

bool JSONSerializer::WriteIntoFile(const char *fileName, WriteFunction function)
{
	FILE* file;
	if (fopen_s(&file, fileName, "w") != 0)
	{
		std::cout << "Cannot open " << fileName << std::endl;
		return false;
	}

	char buffer[MAX_BUFFER_SIZE]{};
	rapidjson::FileWriteStream os(file, buffer, sizeof(buffer));
	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);

	function(writer);
	fclose(file);
	return true;
}

bool JSONSerializer::ReadFromFile(const char* fileName, ReadFunction function)
{
	FILE* file;
	if (fopen_s(&file, fileName, "r") != 0)
	{
		std::cout << "Cannot open " << fileName << std::endl;
		return false;
	}

	char buffer[MAX_BUFFER_SIZE]{};
	rapidjson::FileReadStream is(file, buffer, sizeof(buffer));
	rapidjson::Document doc;
	doc.Parse(buffer);
	if (!doc.IsObject())
	{
		std::cout << fileName << " is not a valid JSON file" << std::endl;
		return false;
	}

	function(doc);
	fclose(file);
	return false;
}

JSONSerializer::JSONSerializer()
{
}

JSONSerializer::~JSONSerializer()
{
}
