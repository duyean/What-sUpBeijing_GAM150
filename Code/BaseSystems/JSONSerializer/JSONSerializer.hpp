/*!************************************************************************
* \file JSONSerializer.hpp
* \author Tai Yang Tat Bryson
* \par DP email: t.yangtatbryson\@digipen.edu
* \par Course: CSD1451-b
* \brief
*   This file implements functions regarding the reading and writing of JSON files
**************************************************************************/

#pragma once

#include <functional>
#include <string>
#include "../../JSONSerializer_WZBJ_Pak.hpp"

using WriteFunction = std::function<void(rapidjson::PrettyWriter<rapidjson::OStreamWrapper>&)>;
using ReadFunction = std::function<void(rapidjson::Document&)>;

/*!***********************************************************************
* \class JSONSerializer
* \brief
*  Serializer to read and write JSON files
*************************************************************************/
class JSONSerializer
{
public:
	/*!***********************************************************************
	* \brief
	*  Writes into a JSON file depending on the WriteFunction
	* \param[in] fileName
	*  Name of the JSON file to write into
	* \param[in] function
	*  A function for writing into the JSON file
	* \return
	*  If the JSON is successfully written into
	*************************************************************************/
	bool WriteIntoFile(std::string fileName, WriteFunction function);

	/*!***********************************************************************
	* \brief
	*  Reads from a JSON file and inserts depending on the ReadFunction
	* \param[in] fileName
	*  Name of the JSON file to read from
	* \param[in] function
	*  A function for reading from the JSON file
	* \return
	*  If the JSON is successfully read from
	*************************************************************************/
	bool ReadFromFile(std::string fileName, ReadFunction function);

	/*!***********************************************************************
	* \brief
	*  Creates and parses a rapidjson Document from a JSON file
	* \param[in] fileName
	*  Name of the JSON file to parse
	* \return
	*  The JSON file as a rapidjson::Document
	*************************************************************************/
	rapidjson::Document ReadDocument(std::string fileName);

	/*!***********************************************************************
	* \brief
	*  Default constructor
	*************************************************************************/
	JSONSerializer() {};
	/*!***********************************************************************
	* \brief
	*  Default destructor
	*************************************************************************/
	~JSONSerializer() {};
};

