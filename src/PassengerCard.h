#ifndef PASSENGERCARD_H_
#define PASSENGERCARD_H_

#include "project_utils.h"
#include <string>

/**
 * @brief Class for representing the card of a passenger in the system
 * 
 */
class PassengerCard {

public:
	/**
	 * @brief Card Type enum 
	 * 
	 */
	enum CardType {twentyFive=25,fifty=50,hundred=100};
	/**
	 * @brief Next ID Counter
	 * 
	 * Used to set new ID when PassengerCard object is constructed, incremented every time a 
	 * new PassengerCard object is constructed.
	 * 
	 */
	static id_t currentID;

public:
	/**
	 * @brief Construct a new Passenger Card object
	 * 
	 * @param type Type of the card
	 * @param passengerID ID of the passenger 
	 * @param pName Name of the passenger that owns the card
	 */
	PassengerCard(CardType type, id_t passengerID, std::string pName);

	/**
	 * @brief Get the discount percentage provided by the card
	 * 
	 * @return int Percentag of discount
	 */
	int getDiscount() const;

	/**
	 * @brief Get the Type object
	 * 
	 * @return CardType 
	 */
	CardType getType();

	/**
	 * @brief Get the monthly cost of the card
	 * 
	 * @return uint Monthly cost of the card in cents
	 */
	uint getCost();

	/**
	 * @brief Set the typeof the card
	 * 
	 * @param type 
	 */
	void setType(CardType type);

private:
	/**
	 * @brief ID of the card
	 * 
	 */
	id_t cardID;
	/**
	 * @brief ID of the owner of the card
	 * 
	 */
	id_t passengerID;
	/**
	 * @brief Type of discount provided by the card
	 * 
	 */
	CardType cardType;
	/**
	 * @brief Name of the owner of the card
	 * 
	 */
	std::string passengerName;
};

#endif /* PASSENGERCARD_H_ */
