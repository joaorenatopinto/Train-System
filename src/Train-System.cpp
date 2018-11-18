#include "System.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "exceptions/NoSuchPassengerException.h"
#include "exceptions/NoSuchStationException.h"
#include "exceptions/NoSuchTrainException.h"
#include "exceptions/NoSuchTripException.h"
#include "exceptions/TripPastException.h"

using namespace std;

template <class T> bool readVar(T &var) {
	if (!cin.good()) {
		cin.ignore(INT32_MAX, '\n');
		cin.clear();
	}

	bool validInput = false;
	while (!validInput) {
		cin >> var;
		if (!cin.good()) {
			if (cin.eof()) {
				cin.clear();
				cin.ignore(INT32_MAX, '\n');
				cin.clear();
				return true;
			} else {
				cout << "Invalid input, try again - ";
				cin.clear();
				cin.ignore(INT32_MAX, '\n');
				cin.clear();
			}
		} else {
			cin.clear();
			cin.ignore(INT32_MAX, '\n');
			cin.clear();
			validInput = true;
		}
	}
	return false;
}

bool readLine(string &s) {
	if (!cin.good()) {
		cin.ignore(INT32_MAX, '\n');
		cin.clear();
	}

	bool validInput = false;
	while (!validInput) {
		cin.clear();
		getline(cin, s);
		
		if (!cin.good()) {
			if (cin.eof()) {
				cin.clear();
				cin.ignore(INT32_MAX, '\n');
				cin.clear();
				return true;
			} else {
				cin.clear();
			}
		} else {
			validInput = true;
		}
	}
	return false;
}

Date readBirthDate() {
	Date date("01-01-1970 00:00");
	cout << "Birth Date (dd-mm-yyyy) - ";
	bool validDate = true;
	do {
		string dateString;
		readLine(dateString);

		if (dateString.length() != 10) {
			cout << "Date has to be in the exact format (dd-mm-yyyy), try again - ";
			validDate = false;
			continue;
		} 
		dateString += " 00:00";

		try {
			date = Date(dateString);
		} catch (InvalidDateException &e) {
			cout << "The date you entered is not valid, try again - ";
			validDate = false;
			continue;
		}
		validDate = true;
	} while (!validDate);
	return date;
}

Date readDate() {
	Date date("01-01-1970 00:00");
	cout << "Date (dd-mm-yyyy HH:MM) - ";
	bool validDate = true;
	do {
		string dateString;
		readLine(dateString);

		if (dateString.length() != 16) {
			cout << "Date has to be in the exact format (dd-mm-yyyy HH:MM), try again - ";
			validDate = false;
			continue;
		}

		try {
			date = Date(dateString);
		} catch (InvalidDateException &e) {
			cout << "The date you entered is not valid, try again - ";
			validDate = false;
			continue;
		}

		validDate = true;
	} while (!validDate);
	return date;
}

void mainMenu();
bool processCommand(string command);

void createTask();
void createPassenger();
void createCard();
void createStation();
void createTrain();
void createTrip();

void deleteTask();
void searchTask();
void purchaseTask();
void listTask();
void payCard();
void checkCards();
vector<string> splitArgumets(string&);

void loadPassengers();
void loadCards();
void loadStations();
void loadTrains();
void loadTrips();

void savePassengers();
void saveStations();
void saveTrains();
void saveTrips();

void mainMenu() {
	string menuOptions[] = {
		"  1 - Create a new passenger/station/train/trip.",
		"  2 - Delete a passenger/station/train/trip.",
		"  3 - Search for trips.",
		"  4 - Process a ticket purchase.",
		"  5 - List all passengers/stations/trains/trips.",
		"  6 - Process card payment.",
		"  7 - End of month card processing.",
		"100 - exit"
	};
	cout << endl << "Train System Interface" << endl;
	cout << endl;
	for (string s: menuOptions) {
		cout << s << endl;
	}
	cout << endl;
	cout << "Choose what to do - ";
}

//TODO purchase load functions
//TODO purchase save functions

void createTask() {
	cout << endl << "Choose what you want to create:" << endl << endl;
	cout << "1 - Passenger" << endl;
	cout << "2 - Passenger Card" << endl;
	cout << "3 - Station" << endl;
	cout << "4 - Train" << endl;
	cout << "5 - Trip" << endl;
	cout << endl;
	cout << "Choice (-1 to return to main menu) - ";

	bool validChoice = false;
	while (!validChoice) {
		int choice;
		if (readVar(choice)) {
			return;
		}
		switch (choice) {
			case -1:
				return;
				break;
			case 1: {
				validChoice = true;
				createPassenger();
				break;
			}
			case 2: {
				validChoice = true;
				createCard();
				break;
			}
			case 3: {
				validChoice = true;
				createStation();
				break;
			}
			case 4: {
				validChoice = true;
				createTrain();
				break;
			}
			case 5: {
				validChoice = true;
				createTrip();
				break;
			}
			default: {
				validChoice = false;
				cout << "Ivalid choice, try again - ";
				break;
			}
		}
	}

}

void createPassenger() {
	string name;
	cout << "Name - ";
	readLine(name);

	Date birthDate = readBirthDate();

	try {
		System::instance.createPassenger(name, birthDate);
	} catch (exception *e) {
		cout << "A problem has ocurred creating passenger:" << endl;
		cout << e->what() << endl;
		return;
	}
 
	cout << "Successfully created passenger." << endl;
}

void createCard() {

	if (System::instance.getPassengers().size() == 0) {
		cout << "There are no passengers to get a card." << endl;
		return;
	}

	Passenger *passenger;
	cout << "Enter the id of the passenger who will own the card - ";
	id_t passengerID;
	readVar(passengerID);
	try {
		passenger = System::instance.getPassenger(passengerID);
	} catch (NoSuchPassengerException &e) {
		cout << "Passenger id does not exist, returning to main menu.";
		return;
	}

	string type;
	cout << "Card type (twenty five/fifty/hundred) - ";
	bool validType = false;
	while (!validType) {
		readLine(type);
		if (type != "twenty five" && type != "fifty" && type != "hundred") {
			cout << "Not a valid type, try again - ";
		} else {
			validType = true;
		}
	}

	try {
		System::instance.createCard(passenger,type);
	} catch (exception *e) {
		cout << "A problem has ocurred creating card:" << endl;
		cout << e->what() << endl;
		return;
	}

	cout << "Successfully created card." << endl;

}

void createStation() {

	cout << "Please enter the name of the station - ";
	string name;
	readLine(name);

	try {
		System::instance.createStation(name);
	} catch (exception *e) {
		cout << "A problem has ocurred creating station:" << endl;
		cout << e->what() << endl;
		return;
	}

	cout << "Successfully created station." << endl;
}

void createTrain() {

	cout << "Please enter the amount of seats in the train - ";
	uint maxSeats;
	readVar(maxSeats);

	try {
		System::instance.createTrain(maxSeats);
	} catch (exception *e) {
		cout << "A problem has ocurred creating train:" << endl;
		cout << e->what() << endl;
		return;
	}

	cout << "Successfully created train." << endl;

}

void createTrip() {

	cout << "Please enter base price of the trip - ";
	uint basePrice;
	readVar(basePrice);

	cout << "Source station ID - ";
	id_t sourceID;
	readVar(sourceID);
	Station *src;
	try {
		src = System::instance.getStation(sourceID);
	} catch (NoSuchStationException &e) {
		cout << "Station ID does not exist, returning to main menu." << endl;
		return;
	}

	cout << "Destination station ID - ";
	id_t destID;
	readVar(destID);
	Station *dest;
	try {
		dest = System::instance.getStation(destID);
	} catch (NoSuchStationException &e) {
		cout << "Station ID does not exist, returning to main menu." << endl;
		return;
	}

	cout << "ID of train that will be doing trip - ";
	id_t trainID;
	readVar(trainID);
	Train *tr;
	try {
		tr = System::instance.getTrain(trainID);
	} catch (NoSuchTrainException &e) {
		cout << "Train ID does not exist, returning to main menu." << endl;
		return;
	}

	cout << "Departure ";
	Date dep = readDate();
	cout << "Arrival ";
	Date arr = readDate();

	try {
		System::instance.createTrip(basePrice, src, dest, tr, dep, arr);
	} catch (exception *e) {
		cout << "A problem has ocurred creating trip:" << endl;
		cout << e->what() << endl;
		return;
	}

	cout << "Successfully created trip." << endl;

}

void deleteTask() {
	cout << "What do you wnat to delete? (passenger/station/train/trip) - ";
	string choice;
	bool validChoice = false;
	while (!validChoice) {
		readLine(choice);
		if (choice == "passenger" || choice == "station" || choice == "train" || choice == "trip") {
			validChoice = true;
		} else {
			cout << "Invalid choice, try again - ";
		}
	}
	cout << "ID - ";
	id_t id;
	readVar(id);
	if (choice == "passenger") {
		System::instance.removePassenger(id);
	} else if (choice == "station") {
		System::instance.removeStation(id);
	} else if (choice == "train") {
		System::instance.removeTrain(id);
	} else {
		System::instance.removeTrip(id);
	}

	cout << "Done." << endl;
	
}

void searchTask() {
	cout << "Specify a source restraint? (y/n) - ";
	bool searchBySrc;
	string choice;
	do {
		readLine(choice);
		if (choice != "y" && choice != "n") {
			cout << "Invalid choice, try again - ";
		} else {
			searchBySrc = choice == "y";
		}
	} while (choice != "y" && choice != "n");

	Station *src = nullptr;
	if (searchBySrc) {
		id_t id;
		cout << "Please input the ID of the source station - ";
		readVar(id);
		try {
			src = System::instance.getStation(id);
		} catch (NoSuchStationException &e) {
			cout << "Station ID does not exist." << endl;
			return;
		}
	}

	cout << "Specify a destination restraint? (y/n) - ";
	bool searchByDest;
	do {
		readLine(choice);
		if (choice != "y" && choice != "n") {
			cout << "Invalid choice, try again - ";
		} else {
			searchByDest = choice == "y";
		}
	} while (choice != "y" && choice != "n");

	Station *dest = nullptr;
	if (searchByDest) {
		id_t id;
		cout << "Please input the ID of the destination station - ";
		readVar(id);
		try {
			dest = System::instance.getStation(id);
		} catch (NoSuchStationException &e) {
			cout << "Station ID does not exist." << endl;
			return;
		}
	}

	cout << "Specify a arrival date restraint? (y/n) - ";
	bool searchByArrivalDate;
	do {
		readLine(choice);
		if (choice != "y" && choice != "n") {
			cout << "Invalid choice, try again - ";
		} else {
			searchByArrivalDate = choice == "y";
		}
	} while (choice != "y" && choice != "n");

	Date arrivalDate("01-01-1970 00:00");
	if (searchByArrivalDate) {
		arrivalDate = readDate();
	}

	vector<Trip*> trips = System::instance.searchTrips(src, dest, searchByArrivalDate, arrivalDate);

	cout << endl;

	if (trips.size() == 0) {
		cout << "There are no trips that match these constraints." << endl;
		return;
	}

	for (Trip *tr: trips) {
		tr->printRow(cout);
		cout << endl;
	}

}

void purchaseTask() {
	cout << "ID of passenger - ";
	Passenger *passenger;
	id_t passengerID;
	readVar(passengerID);
	try {
		passenger = System::instance.getPassenger(passengerID);
	} catch (NoSuchPassengerException &e) {
		cout << "Passenger id does not exist, returning to main menu.";
		return;
	}

	cout << "ID of the trip - ";
	Trip *tr;
	id_t tripID;
	readVar(tripID);
	try {
		tr = System::instance.getTrip(passengerID);
	} catch (NoSuchTripException &e) {
		cout << "Trip id does not exist, returning to main menu.";
		return;
	}

	TicketPurchaseRequest rq(passenger, tr);
	try {
		System::instance.processTicketPurchaseRequest(rq);
	} catch (TripPastException &e) {
		cout << "Trip has already passed." << endl;
		return;
	}

	rq.printInvoice(cout);
	cout << endl;
}

void listTask() {
	cout << "What to list (passengers/stations/trains/trips) ? ";
	string choice;
	bool validChoice = false;
	while (!validChoice) {
		readLine(choice);
		if (choice == "passengers" || choice == "stations" || choice == "trains" || choice == "trips") {
			validChoice = true;
		} else {
			cout << "Invalid choice, try again - ";
		}
	}
	if (choice == "passengers") {
		System::instance.listPassengers(cout);
	} else if (choice == "stations") {
		System::instance.listStations(cout);
	} else if (choice == "trains") {
		System::instance.listTrains(cout);
	} else {
		System::instance.listTrips(cout);
	}
}

void payCard() {
	cout << "Please enter the ID of the passenger whose card is being paid - ";
	id_t passengerID;
	readVar(passengerID);

	try {
		if (!System::instance.payCard(passengerID)) {
			cout << "Passenger doesn't have a card." << endl;
			return;
		}
	} catch (NoSuchPassengerException &e) {
		cout << "Passenger Id doesn't exists." << endl;
		return;
	}

	cout << "Done." << endl;
}

void checkCards() {
	System::instance.processCards();

	cout << "Done." << endl;
}

vector<string> splitArgumets(string& command) {
	vector<string> v;
	string temp;
	bool isString = false;
	for (const char c: command) {
		if (c == ' ') {
			if (!isString) {
				if (!temp.empty()) {
					v.push_back(temp);
					temp.clear();
				}
			} else {
				temp.push_back(c);
			}
		} else {
			if (c == '\"') {
				if (!isString) {
					isString = true;
				} else {
					v.push_back(temp);
					temp.clear();
					isString = false;
				}
			} else {
				temp.push_back(c);
			}
		}
	}

	if (!temp.empty()) {
		v.push_back(temp);
	}

	return v;
}

void loadPassengers() {
	ifstream passengers("passengers.txt");
	if (passengers.is_open()) {
		string line;
		while (getline(passengers, line)) {
			vector<string> arguments = splitArgumets(line);

			if (arguments.size() != 2) {
				continue;
			}

			try {
				Date birthDate(arguments[1]);
				System::instance.createPassenger(arguments[0], birthDate);
			} catch (exception &e) {
				continue;
			}
		}
		passengers.close();
	}
}

void loadCards() {
	ifstream cards("cards.txt");
	if (cards.is_open()) {
		string line;
		while (getline(cards, line)) {
			vector<string> arguments = splitArgumets(line);

			if (arguments.size() != 2) {
				continue;
			}

			try {
				Passenger *p = System::instance.getPassenger(stoi(arguments[0]));
				System::instance.createCard(p, arguments[1]);
			} catch (exception &e) {
				continue;
			}
		}
		cards.close();
	}
}

void loadStations() {
	ifstream stations("stations.txt");
	string line;
	while (getline(stations, line)) {
		vector<string> arguments = splitArgumets(line);
		if (arguments.size() != 1) {
			continue;
		}

		try {
			System::instance.createStation(arguments[0]);
		} catch (exception &e) {
			continue;
		}
	}
}

void loadTrains() {
	ifstream trains("trains.txt");
	string line;
	while (getline(trains, line)) {
		vector<string> arguments = splitArgumets(line);
		
		if (arguments.size() != 1) {
			continue;
		}

		try {
			System::instance.createTrain(stoi(arguments[0]));
		} catch (exception &e) {
			continue;
		}
	}
}

void loadTrips() {
	ifstream trips("trips.txt");
	string line;
	while (getline(trips, line)) {
		vector<string> arguments = splitArgumets(line);
		if (arguments.size() != 6) {
			continue;
		}

		try {
			Station *src = System::instance.getStation(stoi(arguments[1]));
			Station *dest = System::instance.getStation(stoi(arguments[2]));
			Train *tr = System::instance.getTrain(stoi(arguments[3]));
			Date dep(arguments[4]);
			Date arr(arguments[5]);
			System::instance.createTrip(stoi(arguments[0]), src, dest, tr, dep, arr);
		} catch (exception &e) {
			continue;
		}
	}
}

void savePassengers() {
	ofstream passengers("passengers.txt", ofstream::out | ofstream::trunc);
	ofstream cards("cards.txt", ofstream::out | ofstream::trunc);
	vector<Passenger*> vec = System::instance.getPassengers();
	for (uint i = 0; i < vec.size(); i++) {
		passengers << "\"" << vec[i]->getName() << "\" \"" << vec[i]->getBirthDate().getDateString() << "\"" << endl;
		
		if (vec[i]->getCard() != nullptr) {
			cards << i << " \"";
			switch (vec[i]->getCard()->getType()){
				case PassengerCard::twentyFive:
					cards << "twenty five";
					break;
				case PassengerCard::fifty:
					cards << "fifty";
					break;
				case PassengerCard::hundred:
					cards << "hundred";
					break;
			}
			cards << "\"" << endl;
		}
	}
	passengers.close();
	cards.close();
}

void saveStations() {
	ofstream stations("stations.txt", ofstream::out | ofstream::trunc);
	vector<Station*> vec = System::instance.getStations();
	for(uint i = 0; i < vec.size(); i++) {
		stations << "\"" << vec[i]->getName() << "\"" << endl;
	}
	stations.close();
}

void saveTrains() {
	ofstream trains("trains.txt", ofstream::out | ofstream::trunc);
	vector<Train*> vec = System::instance.getTrains();
	for(uint i = 0; i < vec.size(); i++) {
		trains << vec[i]->getMaxSeats() << endl;
	}
	trains.close();
}

void saveTrips() {
	ofstream trips("trips.txt", ofstream::out | ofstream::trunc);
	vector<Trip*> vec = System::instance.getTrips();

	for (uint i = 0; i < vec.size(); i++) {
		int srcIndex = System::instance.getStationIndex(vec[i]->getSource()->getID());
		int destIndex = System::instance.getStationIndex(vec[i]->getDest()->getID());
		int trainIndex = System::instance.getTrainIndex(vec[i]->getTrain()->getID());
		if (srcIndex == -1 || destIndex == -1 || trainIndex == -1) {
			continue;
		}
		trips << vec[i]->getBasePrice() << " "
		<< srcIndex << " " << destIndex << " " << trainIndex << " "
		<< "\"" << vec[i]->getDepartureDate().getDateString() << "\" \""
		<< vec[i]->getDepartureDate().getDateString() << "\"" << endl;
	}
	trips.close();
}

int main() {

	loadPassengers();
	loadCards();
	loadStations();
	loadTrains();
	loadTrips();
	System::instance.processCards();

	bool programmRunning = true;
	while (programmRunning) {

		mainMenu();

		int choice;
		if (readVar(choice)) {
			programmRunning = false;
			break;
		}

		bool validChoice = false;
		while(!validChoice) {
			switch (choice) {
				case 1:{
					createTask();
					validChoice = true;
					break;
				}
				case 2:{
					deleteTask();
					validChoice = true;
					break;
				}
				case 3:{
					searchTask();
					validChoice = true;
					break;
				}
				case 4:{
					purchaseTask();
					validChoice = true;
					break;
				}
				case 5:{
					listTask();
					validChoice = true;
					break;
				}
				case 6:{
					payCard();
					validChoice = true;
					break;
				}
				case 7:{
					checkCards();
					validChoice = true;
					break;
				}
				case 100:{
					programmRunning=false;
					validChoice = true;
					break;
				}
				default:{
					cout << "Invalid choice, try again - ";
					validChoice = false;
					break;
				}
			}
		}
		if (programmRunning) {
			cout << "Press ENTER to contiune to main menu." << endl;
			getchar();
		}
	}

	System::instance.sortPassengers();
	System::instance.sortStations();
	System::instance.sortTrains();
	System::instance.sortTrips();

	savePassengers();
	saveStations();
	saveTrains();
	saveTrips();

	return 0;
}
