/*!************************************************************************
* \file ShopBlessing.hpp
* \author Tai Yang Tat Bryson
* \par DP email: t.yangtatbryson\@digipen.edu
* \par Course: CSD1451-b
* \brief
*   This file implements a ShopBlessing entity as a SoloBehavior object
**************************************************************************/

#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/Combat/Blessing/Blessing.hpp"

/*!***********************************************************************
* \class ShopBlessing
* \brief
*  The SoloBehavior object for ShopBlessings
*************************************************************************/
class ShopBlessing : public SoloBehavior
{
public:
	/*!***********************************************************************
	* \brief
	*  Gets the name of the texture related to the Blessing
	* \return
	*  The name of the texture
	*************************************************************************/
	std::string GetTextureName();
	/*!***********************************************************************
	* \brief
	*  Gets the Blessing related to this ShopBlessing
	* \return
	*  Reference to a unique_ptr<Blessing>
	*************************************************************************/
	std::unique_ptr<Blessing>& GetBlessing();

	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's awake() function
	* \return
	*  void
	*************************************************************************/
	void awake() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's init() function
	* \return
	*  void
	*************************************************************************/
	void init() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's update() function
	* \return
	*  void
	*************************************************************************/
	void update() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's fixedUpdate() function
	* \return
	*  void
	*************************************************************************/
	void fixedUpdate() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's destroy() function
	* \return
	*  void
	*************************************************************************/
	void destroy() override;

	/*!***********************************************************************
	* \brief
	*  Default constructor
	*************************************************************************/
	ShopBlessing();
	/*!***********************************************************************
	* \brief
	*  Default destructor
	*************************************************************************/
	~ShopBlessing();
private:
	// Pointer to the actual Blessing
	std::unique_ptr<Blessing> blessing;
};

