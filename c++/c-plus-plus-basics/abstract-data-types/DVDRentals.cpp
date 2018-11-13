/*
Title: DVDRentals.cpp
Description: Manages DVD rentals in a “video” rental store. Creates an abstract data 
	     type that represents a DVD in this store. Considers all the data and 
	     operations necessary for the DVD type to work well within a rental 
	     management system. Includes a print() member function that displays all the
	     information about the DVD. Creates an array of 10 DVD instances and fills them 
	     using information read from a test input file. Displays the DVD information.
Date: February 16th, 2015
Author: Dan Bonham
Version: 1.0
Copyright: 2015 Daniel R. Bonham
*/

// Program written exclusively through the use of "Thinking in C++" by Bruce Eckel
#include <fstream> // File stream declarations
#include <iostream> // Stream declarations
#include <string> // String usage
using namespace std;

struct DVD {
	string title; // stores DVD title
	string rating; // stores DVD rating
	float length; // stores DVD length
	string genre; // stores DVD genre
	string type; // stores DVD type
	float price; // stores DVD rental price
	string status; // stores DVD rental status
	string customer; // stores DVD rental customer
	string dueDate; // stores DVD rental due date
	long barcode; // stores DVD barcode
	//Initializes DVD information with that provided or with the default value
	void initialize(string ti = "N/A", string ra = "N/A", float le = 0, 
					string ge = "N/A", string ty = "N/A", float pr = 0,
					string st = "N/A", string cu = "N/A", 
					string du = "N/A", long ba = 0);
	void print(); // function will display DVD information
	void rentDVD(string cu); // function will be used to rent an available DVD
	void returnDVD(); // function will be used to return a rented DVD
	void cleanup(); // deletes DVD object
};


void DVD::initialize(string ti, string ra, float le, string ge, 
					 string ty, float pr, string st, string cu, 
					 string du, long ba) {
	title = ti; // sets title to that provided
	rating = ra; // sets rating to that provided
	length = le; // sets length to that provided
	genre = ge; // sets genre to that provided
	type = ty; // sets type to that provided
	price = pr; // sets price to that provided
	status = st; // sets status to that provided
	customer = cu; // sets customer to that provided
	dueDate = du; // sets dueDate to that provided
	barcode = ba; // sets barcode to that provided
}

// Displays all DVD information
void DVD::print() {
	cout << "Title: " << title << endl;
	cout << "Rating: " << rating << endl;
	cout << "Length: " << length << " hrs" << endl;
	cout << "Genre: " << genre << endl;
	cout << "Type: " << type << endl;
	cout << "Price: $" << price << endl;
	cout << "Status: " << status << endl;
	cout << "Customer: " << customer << endl;
	cout << "Due Date: " << dueDate << endl;
	cout << "Barcode: " << barcode << "\n" << endl;
}

void DVD::rentDVD(string cu) {
	if(status == "In-stock") { // checks if DVD to be rented in in-stock
		status = "Rented"; // updates status to that of rented
		customer = cu; // updates customer to one renting DVD
		dueDate = "02/20/2015"; // sets new due date
		cout << title << " has been rented.\n" << endl; // acknowledges rental
	} else // displays that the DVD wished to be rented is not in-stock
		cout << "Sorry, " << title << " is not currently in-stock.\n" << endl;
}

void DVD::returnDVD() {
	if(status == "Rented") { // checks if DVD is currently rented
		status = "In-stock"; // changes status to in-stock
		customer = "N/A"; // resets customer information to reflect return
		dueDate = "N/A"; // resets dueDate to reflect return
		cout << title << " is now in-stock.\n" << endl; // acknowledges return
	} else // displays that the DVD trying to be returned is already in stock
		cout << "Sorry, " << title << " is already in-stock.\n" << endl;
}

void DVD::cleanup() {
	delete this; // deletes DVD
}

int main() {
	DVD dvds[10]; // creates array of 10 abstract data types DVD
	ifstream file("DVDRentalList.txt"); // opens file with test data
	// variables necessary to read information from file
	string title, rating, genre, type, status, customer, dueDate;
	float price, length;
	long barcode;
	for(int i = 0; i < 10; i++) { // loops through to initialize DVD array
		file >> title; // reads/stores title of current DVD read from file
		file >> rating; // reads/stores rating of current DVD read from file
		file >> length; // reads/stores length of current DVD read from file
		file >> genre; // reads/stores genre of current DVD read from file
		file >> type; // reads/stores type of current DVD read from file
		file >> price; // reads/stores price of current DVD read from file
		file >> status; // reads/stores status of current DVD read from file
		file >> customer; // reads/stores customer of current DVD read from file
		file >> dueDate; // reads/stores dueDate of current DVD read from file
		file >> barcode; // reads/stores barCode of current DVD read from file
		dvds[i].initialize(title, rating, length, genre, type, price, 
						   status, customer, dueDate, barcode); // initializes each DVD
	}
	for(int i = 0; i < 10; i++)
		dvds[i].print(); // displays information for each DVD in the array
	dvds[8].rentDVD("BonhamD"); // rents an available DVD
	dvds[9].rentDVD("BonhamD"); // attempts to rent a DVD that is not in-stock
	dvds[7].returnDVD(); // returns a rented DVD
	dvds[6].returnDVD(); // attempts to return a DVD that is not rented
	for(int i = 0; i < 10; i++)
		dvds[i].print(); // displays DVD information after manipulations
}