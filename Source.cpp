#include <iostream> 
#include<iomanip>
#include <string>
#include <cctype>
#include <fstream> 
#include <windows.h> //for decoration purpose
#include <chrono> //for decoration purpose
#include <thread> //for decoration purpose
using namespace std;
#define SIZE 20

//Define struct
struct FullName {
	string first_name;
	string last_name;
};
struct Registration {
	FullName name;
	string mobile_number;
	string email;
	string username;
	string password;
};

struct BookingDetails {
	FullName passenger_name;
	int departureFlight;
	string departureDate;
	int departTime;
	int returnFlight;
	string returnDate;
	int returnTime;
};
struct Passenger_Details {
	FullName CheckIn_name;
	string passport_num;
	FullName contact_name;
	string mobile_num;
};
struct CheckIn_Details {
	double total_price;
	string payment_status;
	Passenger_Details passenger_flight[SIZE];
	string checkIn_status;
};

string currentUser;
BookingDetails flight[SIZE];
int noTickets;

//Define function
void menu();
void FlightSchedule();
void registration();
void readUser(Registration users[SIZE], int& userCount);
void payment();
void checkIn(CheckIn_Details& details);
void readPaymentCheckIn(CheckIn_Details& details);
void performBooking();//Perform booking main function
void clearline(string message);//Decoration
void inputPassengerDetails(CheckIn_Details& details, int i);
void printInvoice(CheckIn_Details PassengerInfoList, BookingDetails BookingList[]);
void createPaymentCheckInInvoiceFile(int Num_Passengers);
void readBooking(BookingDetails flight[], int& noTickets);//read booking details from booking file
void editBooking(BookingDetails flight[], int noTickets);//Edit booking main function
void editMenu();//display menu for edit option
void showLoadingBar(string loading_message);
void showLoadingBarInvoice(string loading_message);
bool isAlphaOnly(const string& str);//Validation for only letters
bool isDigitsOnly(const string& str);//Validation for only digits
bool duplicateUsername(const string& username);//Validation for no duplicate username
bool strongPassword(const string& password);//Validation for correct password format
bool isAlphabetOnly(const string& name);//validation for name
bool validDate(const string& date);//validation to see if the date is in correct format
bool returnDate(const string& departDate, const string& returnDate);//validation to check if the return date is in future of depart date
bool isValidMobile(const string& mobile_num);
bool isValidPassportNumber(const string& passport_num);
bool isNotEmpty(const string& input);//validation for empty input for name
bool departBeforeReturn(const string& departDate, const string& returnDate);//validation to check if the depart date after editing is before the return date
bool isValidMobile(const string& mobile_num);
bool isValidPassportNumber(const string& passport_num);
bool isValidName(const string& name);
string validateCardHolder();
string validateSecurityCode();
string validateCardDate();
string validateCardNumber();
string validateBankAccountNumber();
string formattedWord(const string& input);//Format uppercase first letter and after space's letter
string removeSpaces(const string& input);
int login(Registration users[SIZE], int& userCount, string& currentUser);
int validReturnFlight(int departureFlight, int currentReturnFlight);//validation for flight to match destination
int getValidatedIntInput(const string& prompt, int min, int max);
char getYesNoInput(const string& promptMessage);
bool nameIsNotEmpty(const string& input);
void displayHeader();
void ticketBooking();
void editingHeader();
void paymentHeader();

int main() {
	int userCount = 0;
	int contRL = 1;
	int cont = 1;
	int choice;
	Registration users[SIZE];
	readUser(users, userCount);
	do {
		displayHeader();
		cout << "\033[1;36m" << "==================================================================================================================================================" << "\033[0m" << endl;
		cout << "\033[1;34m" << "                                                                     Main menu                                                                    " << "\033[0m" << endl;
		cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
		cout << "\033[1;33m" << "1. Register New User" << "\t\t\t\t\t\t     2. Login" << "\t\t\t\t\t\t\t\t    3. Quit\n" << "\033[0m" << endl;
		cout << "Choice: ";
		//Input to register, login or quit
		cin >> choice;
		cin.ignore();

		//Register New User
		if (choice == 1) {
			system("cls");
			registration();
			readUser(users, userCount);
			displayHeader();
			contRL = getValidatedIntInput("\033[1;36mDo you want to continue register/login? (1 - yes, 2 - no): \033[0m", 1, 2);

			if (contRL == 2) {
				cout << "\033[1;36m" << "\nThank you! Goodbye!" << "\033[0m" << endl;
				return 0;
			}
		}
		//Login 
		else if (choice == 2) {
			int result;
			readUser(users, userCount);
			result = login(users, userCount, currentUser);

			switch (result) {
				//Username and password correct
			case 1:
				contRL = 0;
				Sleep(100);
				break;
				//Username found but wrong password
			case 2:
				Sleep(500);
				cout << "\033[1;31m" << "\nIncorrect password. Please try again.\n" << "\033[0m" << endl;
				break;
				//Password matches someone, but wrong username
			case 3:
				Sleep(500);
				cout << "\033[1;31m" << "\nIncorrect username. Please try again.\n" << "\033[0m" << endl;
				break;
				//Both are not correct
			case 4:
				Sleep(500);
				cout << "\033[1;31m" << "\nIncorrect username and password.Please try again.\n" << "\033[0m" << endl;
				break;
			}

			//Input does not fit requirement and prompt user to register/login again
			if (result == 2 || result == 3 || result == 4) {
				cout << "\033[1;31m" << "If you have not registered, please register first!" << "\033[0m" << endl;
				contRL = getValidatedIntInput("\033[1;36mDo you want to continue register/login? (1 - yes, 2 - no)  : \033[0m", 1, 2);
				//Quit the program
				if (contRL == 2) {
					clearline("Quitting the program. Goodbye!");
					system("cls");
					displayHeader();
					cout << "\033[1;36m" << "\nThank you! Goodbye!" << "\033[0m" << endl;
					return 0;
				}
			}
		}
		//Quit the program
		else if (choice == 3) {
			clearline("Quitting the program. Goodbye!");
			system("cls");
			displayHeader();
			cout << "\033[1;36m" << "\nThank you! Goodbye!" << "\033[0m" << endl;
			return 0;
		}

		//Validation check of input
		else {
			if (cin.fail()) {
				cout << "\033[1;31m" << "Error: Invalid input. Please wait and try again." << "\033[0m" << endl;
				cin.clear();
				Sleep(1000);
				string discard;
				getline(cin, discard);
			}
			else {
				cout << "\033[1;31m" << "Error: Invalid input. Please wait and try again" << "\033[0m" << endl;
				Sleep(1000);
			}
		}
		system("cls");
	} while (contRL == 1);
	do {
		system("cls");
		displayHeader();
		cout << "\033[1;36m" << "==================================================================================================================================================" << "\033[0m" << endl;
		cout << "\033[1;34m" << "                                                                  JSJK Airline Company                                                            " << "\033[0m" << endl;
		cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
		cout << "\033[1;32m" << "                                                                                                               ~ Anyone ~ ~ Anywhere ~ ~ Anytime ~" << "\033[0m" << endl;
		cout << "\033[1;36m" << "\nUsername: " << currentUser << "\n" << "\033[0m" << endl;
		menu();
		int select;
		CheckIn_Details details;
		readBooking(flight, noTickets);
		readPaymentCheckIn(details);
		select = getValidatedIntInput("Choice: ", 1, 6);
		if (select == 1) {
			system("cls");
			displayHeader();
			ticketBooking();
			performBooking();
		}
		else if (select == 2) {
			system("cls");
			displayHeader();
			editingHeader();
			editBooking(flight, noTickets);
		}
		else if (select == 3) {
			system("cls");
			displayHeader();
			paymentHeader();
			if (!ifstream(currentUser + "_Booking.txt")) {
				system("cls");
				displayHeader();
				cout << "\033[1;31m" << "\nNo booking available." << "\033[0m" << endl;
				Sleep(2000);
			}
			else if (details.payment_status == "Paid") {
				system("cls");
				displayHeader();
				cout << "\033[1;31m" << "\nYou have already paid." << "\033[0m" << endl;
				Sleep(2000);
			}
			else {
				payment();
			}
		}
		else if (select == 4) {
			system("cls");
			displayHeader();
			cout << "\033[1;36m" << "==================================================================================================================================================" << "\033[0m" << endl;
			cout << "\033[1;34m" << "                                                                 Check In Flight                                                                  " << "\033[0m" << endl;
			cout << "\033[1;36m" << "==================================================================================================================================================" << "\033[0m" << endl;
			if (!ifstream(currentUser + "_Booking.txt")) {
				system("cls");
				displayHeader();
				cout << "\033[1;31m" << "\nNo booking available." << "\033[0m" << endl;
				Sleep(2000);
			}
			else if (details.payment_status == "Not Paid") {
				system("cls");
				displayHeader();
				cout << "\033[1;31m" << "\nPayment not done yet. Please do your payment. " << "\033[0m" << endl;
				Sleep(2000);

			}
			else if (details.checkIn_status == "Checked") {
				system("cls");
				displayHeader();
				cout << "\033[1;31m" << "\nYou have Checked In" << "\033[0m" << endl;
				Sleep(2000);
			}
			else {
				checkIn(details);
			}
		}
		else if (select == 5) {
			system("cls");
			displayHeader();
			cout << "\033[1;36m" << "==================================================================================================================================================" << "\033[0m" << endl;
			cout << "\033[1;34m" << "                                                                   Print Invoice                                                                  " << "\033[0m" << endl;
			cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
			if (!ifstream(currentUser + "_Booking.txt")) {
				system("cls");
				displayHeader();
				cout << "\033[1;31m" << "No booking available." << "\033[0m" << endl;
				Sleep(2000);
			}
			else if (details.payment_status == "Not Paid") {
				system("cls");
				displayHeader();
				cout << "\033[1;31m" << "Payment not done yet. Please do your payment. " << "\033[0m" << endl;
				Sleep(2000);
			}
			else {
				if (details.checkIn_status == "Not Check") {
					system("cls");
					displayHeader();
					cout << "\033[1;31m" << "Check In Status: Not Checked\t\tPlease check in." << "\033[0m" << endl;
					Sleep(2000);
				}
				else
					printInvoice(details, flight);
			}
		}
		else if (select == 6) {
			clearline("Quitting the program. Goodbye!");
			system("cls");
			displayHeader();
			cout << "\033[1;36m" << "\nThank you! Goodbye!" << "\033[0m" << endl;
			cont = 0;
		}
		else
			cout << "Not available" << endl;

		if (select == 1 || select == 2) {
			if (!ifstream(currentUser + "_Booking.txt")) {
			}
			else
				createPaymentCheckInInvoiceFile(noTickets);
		}
	} while (cont == 1);
	return 0;
}

//Decoration
void clearline(string message) {
	for (int i = 0; i < 3; ++i) {
		// Show message
		cout << "\033[31m" << message << " \033[0m " << endl;
		Sleep(150);

		// Clear message by moving up and erasing the line
		cout << "\033[A"; // Move cursor up one line
		cout << "\033[K"; // Clear that line
		Sleep(150);
	}
	cout << "\033[31m" << message << " \033[0m " << endl;
	cout << "Press Enter to continue...";
	string dummy;
	getline(cin, dummy); //Avoid mistype of value before enter that will lead to error
	for (int i = 0; i < 3; i++) {
		cout << "\033[A";
		cout << "\033[K";
	}
}

//To ensure input is not empty
bool isNotEmpty(const string& input) {
	for (char ch : input) {
		if (!isspace(ch)) {
			return true;
		}
	}
	return false;
}

//To ensure input only in letters
bool isAlphaOnly(const string& str) {
	for (char ch : str) {
		if (!isalpha(ch) && ch != ' ')
			return false;
	}
	return true;
}

//To enusre input string to have capitalized first letter after space and others in lower case
string formattedWord(const string& input) {
	string result = input;
	bool formatted_word = true;

	for (char& ch : result) {
		if (isalpha(ch)) {
			if (formatted_word)
				ch = toupper(ch);
			else
				ch = tolower(ch);
			formatted_word = false;
		}
		else {
			formatted_word = true;
		}
	}
	return result;
}

//To ensure input only in numbers
bool isDigitsOnly(const string& str) {
	for (char ch : str) {
		if (!isdigit(ch))
			return false;
	}
	return true;
}

//To ensure correct format of mobile number
bool isValidMobileNumber(const string& number) {
	//To ensure input only in numbers
	if (!isDigitsOnly(number)) return false;
	//To ensure format of first two digits
	if (number.substr(0, 2) != "01") return false;
	//To ensure length of mobile number in a correct format
	if (number.substr(0, 3) == "011") {
		return number.length() == 11;
	}
	else {
		return number.length() == 10;
	}
}

//To ensure correct format of email
bool isValidEmail(const string& email) {
	int condition1 = email.find('@');
	int condition2 = email.find('.');
	//The condition requires value before, between and after "@" and "."
	return (condition1 > 0 &&
		condition2 > condition1 + 1 &&
		condition2 < email.length() - 1 &&
		email.find(' ') == string::npos);
}

//To ensure no duplicate username entered
bool duplicateUsername(const string& username) {
	ifstream file("user.txt");
	string line;
	int lineCount = 0;

	while (getline(file, line)) {
		lineCount++;

		if (lineCount % 6 == 5 && line == username) {
			return true;
		}
	}
	return false;
}

//To ensure format of password
bool strongPassword(const string& password) {
	if (password.length() < 8)
		return false;
	bool hasSpecial = false, hasUpper = false, hasDigit = false;

	//The condition is need to have at least one uppercase letter, one digit and one special character
	for (char ch : password) {
		if (ispunct(ch)) hasSpecial = true;
		else if (isupper(ch)) hasUpper = true;
		else if (isdigit(ch)) hasDigit = true;
	}

	return hasUpper && hasDigit && hasSpecial;
}

//Registration part
void registration() {
	//Declaration of varaiable
	string first_name, last_name, mobile_number, email, username, password1, password2;
	char confirm, choice;
	int notEqualCount;

	//do-while loop for register again
	do {
		displayHeader();
		cout << "\033[1;36m" << "==================================================================================================================================================" << "\033[0m" << endl;
		cout << "\033[1;34m" << "                                                                     Registration                                                                 " << "\033[0m" << endl;
		cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
		cout << "\033[1;36m" << "Please key in details for registration: \n" << "\033[0m" << endl;
		//do-while loop to ensure input to have no empty space and only in letters before the input being accepted.
		do {
			cout << "First name                                                                                 : ";
			getline(cin, first_name);
			//Show error when input is empty
			if (!isNotEmpty(first_name)) {
				clearline("Error: It cannot be blank. Please try again.");
				continue;
			}
			//Show error when input not only in letters
			if (!isAlphaOnly(first_name)) {
				clearline("Error: Name must contain only letters. Please try again.");
				continue;
			}
			break;
		} while (!isNotEmpty(first_name) || !isAlphaOnly(first_name));
		//Format the input
		first_name = formattedWord(first_name);

		//do-while loop to ensure input to have no empty space and only in letters before the input being accepted.
		do {
			cout << "Last name                                                                                  : ";
			getline(cin, last_name);
			//Show error when input is empty
			if (!isNotEmpty(last_name)) {
				clearline("Error: It cannot be blank. Please try again.");
				continue;
			}
			//Show error when input not only in letters
			if (!isAlphaOnly(last_name)) {
				clearline("Error: Name must contain only letters. Please try again.");
				continue;
			}
			break;
		} while (!isNotEmpty(last_name) || !isAlphaOnly(last_name));
		//Format the input
		last_name = formattedWord(last_name);

		//do-while loop to ensure input only in digits and correct format and length of mobile number before the input being accepted.
		do {
			cout << "Mobile number (01X..)                                                                      : ";
			getline(cin, mobile_number);
			//Show error when input not only in letters
			if (!isDigitsOnly(mobile_number)) {
				clearline("Error: Mobile number must be only in digits.Please try again.");
				continue;
			}
			//Correct format of mobile number
			if (!isValidMobileNumber(mobile_number)) {
				//Show error when input not start with "01"
				if (mobile_number.substr(0, 2) != "01") {
					clearline("Error: Mobile number must start with '01'. Please try again.");
					continue;
				}
				//Show error when input with "011" not in 11 digits
				if (mobile_number.substr(0, 3) == "011" && mobile_number.length() != 11) {
					clearline("Error: 11 digits needed. Please try again.");
					continue;
				}
				//Show error when input with other than "011" not in 10 digits
				if (mobile_number.substr(0, 3) != "011" && mobile_number.length() != 10) {
					clearline("Error: 10 digits needed. Please try again.");
					continue;
				}
				break;
			}
		} while (!isDigitsOnly(mobile_number) || !isValidMobileNumber(mobile_number));

		//do-while loop to ensure input to have no empty space and correct format of email before the input being accepted.
		do {
			cout << "Email(xx@xx.xx)                                                                            : ";
			getline(cin, email);
			//Show error when input is empty
			if (!isNotEmpty(email)) {
				clearline("Error: It cannot be blank. Please try again.");
				continue;
			}
			//Show error when input is not in the correct email format
			if (!isValidEmail(email)) {
				clearline("Error: Invalid email format. Please try again.");
				continue;
			}
			break;
		} while (!isNotEmpty(email) || !isValidEmail(email));

		//do-while loop to ensure input to have no empty space, in letters only and no duplicate with existing username before the input being accepted.
		do {
			cout << "Enter your username                                                                        : ";
			getline(cin, username);
			//Show error when input is empty
			if (!isNotEmpty(username)) {
				clearline("Error: It cannot be blank. Please try again.");
				continue;
			}
			//Show error when input is not only in letters
			if (!isAlphaOnly(username)) {
				clearline("Error: Username must contain only letters. Please try again.");
				continue;
			}
			//Show error when input is duplicate with existing username
			if (duplicateUsername(username)) {
				clearline("Error: The username is already exist. Please try entering another username.");
				continue;
			}
			break;
		} while (!isNotEmpty(username) || !isAlphaOnly(username) || duplicateUsername(username));

		//do-while loop to make sure the re-enter password must be less than 3 failed attempts.
		do {
			//do-while loop to ensure password is strong before the input being accepted.
			do {
				cout << "Password (At least 8 characters, including 1 symbol, 1 uppercase letter, and 1 number)     : ";
				getline(cin, password1);
				//Show error when input do not meet the condition to have a strong password
				if (!strongPassword(password1)) {
					clearline("Error: Invalid password format. Please try again.");
				}
			} while (!strongPassword(password1));

			notEqualCount = 0;
			//do-while loop to ensure both password input is the same and re-enter password after mismatch over 3 attempts
			do {
				cout << "Re-enter your password                                                                     : ";
				getline(cin, password2);
				//Show error when input not same with the previous password input
				if (password1 != password2) {
					notEqualCount++;
					clearline("Error: Both passwords do not match. Please try again.");
					//Show erroe when input fail over 3 attempts
					if (notEqualCount == 3) {
						clearline("Error: Too many failed attempts. Please re-enter a new password.");
						break;
					}
				}

			} while (password1 != password2 && notEqualCount < 3);

		} while (notEqualCount == 3);
		cout << endl;
		//do-while loop to ensure registration confirmed
		do {
			cout << "\033[1;36m" << "Confirm to register? (y - yes, n - no): " << "\033[0m";
			cin >> confirm;
			cin.ignore();

			//Confirm to register and save in txt file
			if (confirm == 'y' || confirm == 'Y') {

				clearline("Registration done!");
				ofstream myfile;
				myfile.open("user.txt", ios::app);
				if (myfile.is_open()) {
					myfile << first_name << endl;
					myfile << last_name << endl;
					myfile << mobile_number << endl;
					myfile << email << endl;
					myfile << username << endl;
					myfile << password2 << endl;

					myfile.close();
				}
				else {
				}
				myfile.close();
			}
			//Reject to register 
			else if (confirm == 'n' || confirm == 'N') {
				clearline("Registration cancelled. Please register again.");
				system("cls");

				//do-while loop to ask user to register again or quit the program
				do {
					displayHeader();
					cout << "\033[1;36m" << "Do you want to? (R - Register again, Q - Quit): " << "\033[0m";
					//Input whether need to register again or quit
					cin >> choice;
					cin.ignore();
					//Quit the program
					if (choice == 'q' || choice == 'Q') {
						clearline("Quitting...");
						system("cls");
						return;
					}
					//Register again
					else if (choice == 'r' || choice == 'R') {
						clearline("Connecting back to registration page...");
						break;
					}
					//Show error when invalid input
					else {
						clearline("Error: Invalid choice. Please try again.");
						system("cls");
					}
				} while (choice != 'q' && choice != 'Q' && choice != 'r' && choice != 'R');
			}
			//Show error when invalid input
			else {
				clearline("Error: Invalid choice. Please try again.");
			}
		} while (confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N');

		system("cls");
	} while (confirm == 'n' || confirm == 'N');
}

//Function to read the user details that stored in txt file
void readUser(Registration users[SIZE], int& userCount) {
	string line;
	ifstream myfile("user.txt");
	userCount = 0;

	if (myfile.is_open()) {
		while (getline(myfile, users[userCount].name.first_name) &&
			getline(myfile, users[userCount].name.last_name) &&
			getline(myfile, users[userCount].mobile_number) &&
			getline(myfile, users[userCount].email) &&
			getline(myfile, users[userCount].username) &&
			getline(myfile, users[userCount].password)) {
			userCount++;
		}
		myfile.close();
	}
	else {
	}
}

//Function to ensure the input username and password are matching
int login(Registration users[SIZE], int& userCount, string& currentUser) {
	string inputUserName, inputPassword;
	system("cls");
	displayHeader();
	cout << "\033[1;36m" << "==================================================================================================================================================" << "\033[0m" << endl;
	cout << "\033[1;34m" << "                                                                         Login                                                                    " << "\033[0m" << endl;
	cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
	cout << "Enter your username to login: ";
	getline(cin, inputUserName);
	cout << "Enter your password to login: ";
	getline(cin, inputPassword);
	bool usernameFound = false;
	bool passwordCorrect = false;
	for (int i = 0; i < userCount; ++i) {
		if (users[i].username == inputUserName && users[i].password == inputPassword) {
			currentUser = inputUserName;
			cout << "\033[1;31m" << "\nLogin Successfully!" << "\033[0m" << endl;
			cout << "\033[1;36m" << "\nWelcome, " << currentUser << "!" << "\033[0m" << endl;
			clearline("Redirecting to the login page...");
			return 1; //Username and password correct
		}
		if (users[i].username == inputUserName) {
			usernameFound = true;
		}
		if (users[i].password == inputPassword) {
			passwordCorrect = true;
		}
	}
	//Username found but wrong password
	if (usernameFound) return 2;
	//Password matches someone, but wrong username
	if (passwordCorrect) return 3;
	//Both are not correct
	return 4;
}

void editBooking(BookingDetails flight[], int noTickets) {
	if (noTickets == 0) {//if booking file not found
		cout << "No booking available to edit. Please perform a booking first." << endl;
		Sleep(2000);
		system("cls");
	}
	else {
		char changeName, saveEdit;
		int editChoice;
		bool edited = false; // track if any changes were made

		FlightSchedule();
		cout << "Change Passenger Name(Y-Change Passenger Name / N-Change Booking Details) : ";
		cin >> changeName;
		while (cin.fail() || (changeName != 'y' && changeName != 'Y' && changeName != 'n' && changeName != 'N')) {//if the user want to change the passenger name
			cin.clear();
			cin.ignore(1000, '\n');
			clearline("Operation is invalid. Please try again.");
			cout << "Change Passenger Name(Y-Change Passenger Name / N-Change Booking Details) : ";
			cin >> changeName;
		}
		cin.ignore();

		if (changeName == 'Y' || changeName == 'y') {
			system("cls");
			displayHeader();
			editingHeader();
			cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m" << endl;
			cout << "\033[1;34m" << "                                                               Change Passenger Name                                                              " << "\033[0m" << endl;
			cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------\n" << "\033[0m" << endl;
			string searchname;
			cout << "Enter the First Name of passenger that need to be edit : ";
			getline(cin, searchname);
			while (cin.fail() || !isAlphabetOnly(removeSpaces(searchname)) || !nameIsNotEmpty(searchname))//Validation of Name(Alphabet only) 
			{
				if (!nameIsNotEmpty(searchname))//if input is blank, show error
					clearline("Name cannot be blank");
				else if (!isAlphabetOnly(removeSpaces(searchname)))//name only alphabet is allowed
					clearline("Invalid Name. Only alphabet name is allowed. Please try again ");//show error when invalid
				else
					clearline("Invalid Name. Please try again.");
				cout << "Enter the First Name of passenger that need to be edit : ";
				getline(cin, searchname);
			}
			bool found = false;//predefined the indicator for name matching in the file to see if the user exist in booking
			for (int i = 0; i < noTickets; i++) {
				if (flight[i].passenger_name.first_name == searchname) {
					//New First name input
					cout << "Enter the new First Name                               : ";
					getline(cin, flight[i].passenger_name.first_name);
					while (cin.fail() || !isAlphabetOnly(removeSpaces(flight[i].passenger_name.first_name)) || !nameIsNotEmpty(flight[i].passenger_name.first_name))//Validation of Name(Alphabet only)
					{
						if (!nameIsNotEmpty(flight[i].passenger_name.first_name))//if input blank, error
							clearline("Name cannot be blank");
						else if (!isAlphabetOnly(removeSpaces(flight[i].passenger_name.first_name)))//if name is not alphabet only
							clearline("Invalid Name. Only alphabet name is allowed. Please try again ");//show error when invalid
						else
							clearline("Invalid Name. Please try again.");
						cout << "Enter the new First Name                               : ";
						getline(cin, flight[i].passenger_name.first_name);
					}
					//New Last name input
					cout << "Enter the new Last Name                                : ";
					getline(cin, flight[i].passenger_name.last_name);
					while (cin.fail() || !isAlphabetOnly(removeSpaces(flight[i].passenger_name.last_name)) || !nameIsNotEmpty(flight[i].passenger_name.last_name))//Validation of Name(Alphabet only)
					{
						if (!nameIsNotEmpty(flight[i].passenger_name.last_name))//if input blank,error
							clearline("Name cannot be blank");
						else if (!isAlphabetOnly(removeSpaces(flight[i].passenger_name.last_name)))//if not alphabet only, error
							clearline("Invalid Name. Only alphabet name is allowed. Please try again.");//show error when invalid
						else
							clearline("Invalid Name. Please try again.");
						cout << "Enter the new Last Name                                : ";
						getline(cin, flight[i].passenger_name.last_name);
					}
					found = true;//when user found,let user to edit
					edited = true; // indicator for change made
					break;
				}
			}
			if (!found) {//if user not found in booking file
				cout << "Passenger does not exist in Booking File. Please perform a booking first." << endl;//show error because no booking
				cout << "Press enter again to back to main menu." << endl;
				system("pause");
				system("cls");
				return; // exit early
			}
		}
		else if (changeName == 'N' || changeName == 'n') {//if user dont want to edit booking details
			system("cls");
			displayHeader();
			editingHeader();
			cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m" << endl;
			cout << "\033[1;34m" << "                                                               Change Booking Details                                                             " << "\033[0m" << endl;
			cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------\n" << "\033[0m" << endl;
			editMenu();
			cin >> editChoice;
			cin.ignore();
			cin.clear();
			switch (editChoice) {
			case 1://edit depart flight
				system("cls");
				displayHeader();
				editingHeader();
				cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m" << endl;
				cout << "\033[1;34m" << "                                                              Editing Depature Flight                                                             " << "\033[0m" << endl;
				cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------\n" << "\033[0m" << endl;
				FlightSchedule();
				cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
				cout << "Follow the details of the 1st passenger : " << flight[0].passenger_name.last_name << " " << flight[0].passenger_name.first_name << endl;
				cout << "\nOld Departure Flight : " << flight[0].departureFlight << endl;
				cout << "New Departure Flight : ";
				cin >> flight[0].departureFlight;
				while (cin.fail() || flight[0].departureFlight < 1 || flight[0].departureFlight > 8) {//validation for depart flight
					cin.clear();
					cin.ignore(1000, '\n');
					clearline("Invalid flight. Choose between 1 to 8");//if flight not in range 1-8, show error
					cout << "New Departure Flight : ";
					cin >> flight[0].departureFlight;
				}
				cin.ignore();
				cin.clear();
				edited = true;//indicator to show edit has been made
				break;

			case 2://edit depart date
				system("cls");
				displayHeader();
				editingHeader();
				cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m" << endl;
				cout << "\033[1;34m" << "                                                               Editing Depature Date                                                              " << "\033[0m" << endl;
				cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------\n" << "\033[0m" << endl;
				FlightSchedule();
				cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
				cout << "Follow the details of the 1st passenger : " << flight[0].passenger_name.last_name << " " << flight[0].passenger_name.first_name << endl;
				cout << "\nOld Departure Date : " << flight[0].departureDate << endl;
				cout << "New departure Date : ";
				getline(cin, flight[0].departureDate);
				while (!departBeforeReturn(flight[0].departureDate, flight[0].returnDate) || !isNotEmpty(flight[0].departureDate)) {//validation for depart date edit
					if (!isNotEmpty(flight[0].departureDate))//if input is blank
						clearline("Date must not be empty");//show error
					else if (!departBeforeReturn(flight[0].departureDate, flight[0].returnDate))//if depart date edit is after the return date
						clearline("Invalid Date or Depart Date must be in past of Return Date.");//show date error
					else
						clearline("Invalid Depart Date");
					cout << "New departure Date : ";
					getline(cin, flight[0].departureDate);
				}
				edited = true;//indicator that edit has been made
				break;

			case 3://edit depart time slot
				system("cls");
				displayHeader();
				editingHeader();
				cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m" << endl;
				cout << "\033[1;34m" << "                                                             Editing Depature Time Slot                                                            " << "\033[0m" << endl;
				cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------\n" << "\033[0m" << endl;
				FlightSchedule();
				cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
				cout << "Follow the details of the 1st passenger : " << flight[0].passenger_name.last_name << " " << flight[0].passenger_name.first_name << endl;
				cout << "\nOld Departure Slot : " << flight[0].departTime << endl;
				cout << "New Departure Slot : ";
				cin >> flight[0].departTime;
				while (cin.fail() || flight[0].departTime < 1 || flight[0].departTime > 4) {//validation to check if the depart slot is in range 1-4
					cin.clear();
					cin.ignore(1000, '\n');
					clearline("Invalid Slot.Choose between 1 to 4");//error show when the slot selected is not in range
					cout << "New Departure Slot : ";
					cin >> flight[0].departTime;
				}
				cin.ignore();
				edited = true;//indicator for edit has been made
				break;

			case 4://edit return flight
				system("cls");
				displayHeader();
				editingHeader();
				cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m" << endl;
				cout << "\033[1;34m" << "                                                                Editing Return Date                                                               " << "\033[0m" << endl;
				cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------\n" << "\033[0m" << endl;
				FlightSchedule();
				cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
				cout << "Follow the details of the 1st passenger : " << flight[0].passenger_name.last_name << " " << flight[0].passenger_name.first_name << endl;
				cout << "\nOld Return Flight : " << flight[0].returnFlight << endl;
				cout << "New Return Flight : ";
				cin >> flight[0].returnFlight;
				while (cin.fail() || flight[0].returnFlight < 1 || flight[0].returnFlight > 8) {//validation for the input see if it in range 1-8
					cin.clear();
					cin.ignore(1000, '\n');
					clearline("Invalid flight. Choose between 1 to 8");//show error when flight not in range
					cout << "New Return Flight : ";
					cin >> flight[0].returnFlight;
				}
				cin.ignore();
				edited = true;//indicator that edit has been made
				break;

			case 5://edit return date
				system("cls");
				displayHeader();
				editingHeader();
				cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m" << endl;
				cout << "\033[1;34m" << "                                                               Editing Return Flight                                                              " << "\033[0m" << endl;
				cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------\n" << "\033[0m" << endl;
				FlightSchedule();
				cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
				cout << "Follow the details of the 1st passenger : " << flight[0].passenger_name.last_name << " " << flight[0].passenger_name.first_name << endl;
				cout << "\nOld Return Date : " << flight[0].returnDate << endl;
				cout << "New Return Date : ";
				getline(cin, flight[0].returnDate);
				while (!returnDate(flight[0].departureDate, flight[0].returnDate) || !isNotEmpty(flight[0].returnDate)) {//validation for return date edited
					if (!isNotEmpty(flight[0].returnDate))//validate if the input is blank
						clearline("Return Date must not be Empty.");//show error if the return date is blank
					else if (!returnDate(flight[0].departureDate, flight[0].returnDate))//validate if the return date is before the depart date
						clearline("Invalid Return Date or Return Date must be in future of Depart Date.");//show error if the return date is before depart date
					else
						clearline("Invalid Return Date.");
					cout << "New Return Date : ";
					getline(cin, flight[0].returnDate);
				}
				edited = true;//indicator to show edit has been made
				break;

			case 6://edit return time slot
				system("cls");
				displayHeader();
				editingHeader();
				cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m" << endl;
				cout << "\033[1;34m" << "                                                              Editing Return Time Slot                                                            " << "\033[0m" << endl;
				cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------\n" << "\033[0m" << endl;
				FlightSchedule();
				cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
				cout << "Follow the details of the 1st passenger : " << flight[0].passenger_name.last_name << " " << flight[0].passenger_name.first_name << endl;
				cout << "\nOld Return Slot : " << flight[0].returnTime << endl;
				cout << "New Return Slot : ";
				cin >> flight[0].returnTime;
				while (cin.fail() || flight[0].returnTime < 1 || flight[0].returnTime > 4) {//validate to see if the return timeslot is in range 1-4
					cin.clear();
					cin.ignore(1000, '\n');
					clearline("Invalid Slot. Choose between 1 to 4");//show error if slot is out of range
					cout << "New Return Slot : ";
					cin >> flight[0].returnTime;
				}
				cin.ignore();
				edited = true;//indicator to show edit has been made
				break;

			default:
				clearline("Invalid Choice. You will be take back to the homepage...");//if the user input number that out of range, error show
				break;
			}
		}

		// Only save if something was edited
		if (edited) {//if edit made, ask if the user want to confirm and save
			cout << "\nConfirm Amendment? (Y-Save the Edited Details / N-Quit Editing) : ";
			cin >> saveEdit;
			cin.ignore();
			while (cin.fail() || (saveEdit != 'y' && saveEdit != 'Y' && saveEdit != 'n' && saveEdit != 'N')) {//if the user input is other from y or n
				cin.clear();
				cin.ignore(1000, '\n');
				clearline("Invalid input.Only Y or N is allowed.");//error show for invalid input
				cout << "Confirm Amendment? (Y-Save the Edited Details / N-Quit Editing) : " << endl;
				cin >> saveEdit;
			}

			if (saveEdit == 'Y' || saveEdit == 'y') {//if yes, save the edited details to file
				ofstream myfile(currentUser + "_Booking.txt");
				for (int i = 0; i < noTickets; i++) {
					myfile << flight[i].passenger_name.first_name << endl;
					myfile << flight[i].passenger_name.last_name << endl;
					myfile << flight[0].departureFlight << endl;
					myfile << flight[0].departureDate << endl;
					myfile << flight[0].departTime << endl;
					myfile << flight[0].returnFlight << endl;
					myfile << flight[0].returnDate << endl;
					myfile << flight[0].returnTime << endl;
				}
				myfile.close();
				cout << endl;
				cout << "\033[1;31m" << "Booking detail is updated successfully!" << "\033[0m\n" << endl;
				cout << "Press enter again to back to main menu." << endl;
				system("pause");
				system("cls");
			}
			else if (saveEdit == 'N' || saveEdit == 'n') {//if dont want to save, edit will not be save to file, and exit from the edit menu
				cout << "\033[1;31m" << "Edit has been cancelled." << "\033[0m\n" << endl;
				cout << "Press enter again to back to main menu." << endl;
				system("pause");
				system("cls");
			}
		}
	}
}

void readBooking(BookingDetails flight[], int& noTickets) {
	ifstream myfile;
	myfile.open(currentUser + "_Booking.txt");

	if (myfile.fail()) {//if file is not found
	}
	else {
		noTickets = 0;//indicator when booking file is not found to be use in edit booking
		while (!myfile.eof()) {//while file is found, read the booking details of user
			getline(myfile, flight[noTickets].passenger_name.first_name);
			if (flight[noTickets].passenger_name.first_name == "")
				break;
			getline(myfile, flight[noTickets].passenger_name.last_name);
			myfile >> flight[noTickets].departureFlight;
			myfile.ignore();
			getline(myfile, flight[noTickets].departureDate);
			myfile >> flight[noTickets].departTime;
			myfile.ignore();
			myfile >> flight[noTickets].returnFlight;
			myfile.ignore();
			getline(myfile, flight[noTickets].returnDate);
			myfile >> flight[noTickets].returnTime;
			myfile.ignore();
			noTickets++;
		}
	}
	myfile.close();
}

//Choice 1 function
void performBooking()
{
	char confirmBooking;
	const int maxTickets = 20;

	FlightSchedule();
	cout << "Number of Passenger(s): ";
	cin >> noTickets;
	while (cin.fail() || noTickets <= 0 || noTickets > maxTickets) {
		cin.clear();
		cin.ignore(1000, '\n');
		clearline("Invalid Number of Passenger! Please try again.");
		cout << "Number of Passenger(s): ";
		cin >> noTickets;
	}
	cin.ignore();
	system("cls");
	displayHeader();
	ticketBooking();
	FlightSchedule();

	// Shared flight details input once
	int sharedDepartureFlight, sharedReturnFlight, sharedDepartTime, sharedReturnTime;
	string sharedDepartureDate, sharedReturnDate;

	cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m" << endl;
	cout << "\033[1;34m" << "                                                        Flight Details (Shared by ALL Passengers)                                                 " << "\033[0m" << endl;
	cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------\n" << "\033[0m" << endl;

	// Departure Flight
	cout << "\033[1;36m" << "Number of passenger(s): " << noTickets << "\033[0m\n" << endl;
	cout << "Departure Flight              : ";
	cin >> sharedDepartureFlight;
	while (cin.fail() || sharedDepartureFlight <= 0 || sharedDepartureFlight > 8) {
		cin.clear();
		cin.ignore(1000, '\n');
		clearline("Invalid Departure Flight selection. Please choose flight between 1-8.");
		cout << "Departure Flight              : ";
		cin >> sharedDepartureFlight;
	}
	cin.ignore();

	// Departure Date
	cout << "Date of Departure(DD/MM/YYYY) : ";
	getline(cin, sharedDepartureDate);
	while (!validDate(sharedDepartureDate) || !isNotEmpty(sharedDepartureDate)) {
		if (!isNotEmpty(sharedDepartureDate))
			clearline("Depart Date cannot be empty.");
		else
			clearline("Date entered is invalid. Please try again.");
		cout << "Date of Departure(DD/MM/YYYY) : ";
		getline(cin, sharedDepartureDate);
	}

	// Departure Slot
	cout << "Departure Slot                : ";
	cin >> sharedDepartTime;
	while (cin.fail() || sharedDepartTime <= 0 || sharedDepartTime > 4) {
		cin.clear();
		cin.ignore(1000, '\n');
		clearline("Invalid Selection of Time Slot. Please try again.");
		cout << "Departure Slot                : ";
		cin >> sharedDepartTime;
	}
	cin.ignore();

	// Return Flight
	cout << "Return Flight                 : ";
	cin >> sharedReturnFlight;
	while (cin.fail() || sharedReturnFlight <= 0 || sharedReturnFlight > 8) {
		cin.clear();
		cin.ignore(1000, '\n');
		clearline("Invalid Return Flight. Please choose flight 1-8");
		cout << "Return Flight                 : ";
		cin >> sharedReturnFlight;
	}
	while (!validReturnFlight(sharedDepartureFlight, sharedReturnFlight)) {
		cout << "Invalid Return Flight (does not match destination). Please choose again (1-8): ";
		cin >> sharedReturnFlight;
	}
	cin.ignore();

	// Return Date
	cout << "Return Date(DD/MM/YYYY)       : ";
	getline(cin, sharedReturnDate);
	while (!returnDate(sharedDepartureDate, sharedReturnDate) || !isNotEmpty(sharedReturnDate)) {
		if (!isNotEmpty(sharedReturnDate))
			clearline("Return Date must not be empty.");
		else
			clearline("Invalid Return Date. Note: Return Date must be after Depart Date.");
		cout << "Return Date(DD/MM/YYYY)       : ";
		getline(cin, sharedReturnDate);
	}

	// Return Slot
	cout << "Return Slot                   : ";
	cin >> sharedReturnTime;
	while (cin.fail() || sharedReturnTime <= 0 || sharedReturnTime > 4) {
		cin.clear();
		cin.ignore(1000, '\n');
		clearline("Invalid Return Slot. Please Choose slot between 1-4.");
		cout << "Return Slot                   : ";
		cin >> sharedReturnTime;
	}
	cin.ignore();

	// Individual passenger name input
	for (int i = 0; i < noTickets; i++) {
		system("cls");
		displayHeader();
		ticketBooking();
		cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m" << endl;
		cout << "\033[1;34m" << "                                                             Passenger " << i + 1 << " Name Details                                               " << "\033[0m" << endl;
		cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------\n" << "\033[0m" << endl;

		// First name
		cout << "First name : ";
		getline(cin, flight[i].passenger_name.first_name);
		while (cin.fail() || !isAlphabetOnly(removeSpaces(flight[i].passenger_name.first_name)) || !nameIsNotEmpty(flight[i].passenger_name.first_name)) {
			if (!nameIsNotEmpty(flight[i].passenger_name.first_name))
				cout << "Name cannot be blank" << endl;
			else if (!isAlphabetOnly(removeSpaces(flight[i].passenger_name.first_name)))
				cout << "Invalid Name. Only alphabet name is allowed. Please try again" << endl;
			else
				cout << "Invalid Name. Please try again." << endl;
			cout << "First name :";
			getline(cin, flight[i].passenger_name.first_name);
		}

		// Last name
		cout << "Last name  : ";
		getline(cin, flight[i].passenger_name.last_name);
		while (cin.fail() || !isAlphabetOnly(removeSpaces(flight[i].passenger_name.last_name)) || !nameIsNotEmpty(flight[i].passenger_name.last_name)) {
			if (!nameIsNotEmpty(flight[i].passenger_name.last_name))
				cout << "Name cannot be blank" << endl;
			else if (!isAlphabetOnly(removeSpaces(flight[i].passenger_name.last_name)))
				cout << "Invalid Name. Only alphabet name is allowed. Please try again" << endl;
			else
				cout << "Invalid Name. Please try again." << endl;
			cout << "Last name  : ";
			getline(cin, flight[i].passenger_name.last_name);
		}

		// all passenger shared flight details
		flight[i].departureFlight = sharedDepartureFlight;
		flight[i].departureDate = sharedDepartureDate;
		flight[i].departTime = sharedDepartTime;
		flight[i].returnFlight = sharedReturnFlight;
		flight[i].returnDate = sharedReturnDate;
		flight[i].returnTime = sharedReturnTime;
	}

	// Summary display
	system("cls");
	displayHeader();
	ticketBooking();
	cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m" << endl;
	cout << "\033[1;34m" << "                                                                 Summary of Booking                                                               " << "\033[0m" << endl;
	cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------\n" << "\033[0m" << endl;
	FlightSchedule();
	cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;

	for (int i = 0; i < noTickets; i++) {
		cout << "\033[1;33m" << "Passenger " << i + 1 << " :" << "\033[0m\n" << endl;
		cout << "First Name       : " << flight[i].passenger_name.first_name << endl;
		cout << "Last Name        : " << flight[i].passenger_name.last_name << endl;
		cout << "Departure Flight : " << flight[i].departureFlight << endl;
		cout << "Departure Date   : " << flight[i].departureDate << endl;
		cout << "Departure Slot   : " << flight[i].departTime << endl;
		cout << "Return Flight    : " << flight[i].returnFlight << endl;
		cout << "Return Date      : " << flight[i].returnDate << endl;
		cout << "Return Slot      : " << flight[i].returnTime << endl;
		cout << "\n\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
	}

	// Confirm booking
	while (true) {
		cout << "Confirm booking? (Y- Save Booking/N- Quit Booking): ";
		cin >> confirmBooking;
		cin.ignore();

		if (confirmBooking == 'Y' || confirmBooking == 'y') {
			ofstream myfile;
			myfile.open(currentUser + "_Booking.txt", ios::app);
			if (myfile.fail()) {
				cout << "File failed to open" << endl;
			}
			else {
				for (int i = 0; i < noTickets; i++) {
					myfile << flight[i].passenger_name.first_name << endl;
					myfile << flight[i].passenger_name.last_name << endl;
					myfile << flight[i].departureFlight << endl;
					myfile << flight[i].departureDate << endl;
					myfile << flight[i].departTime << endl;
					myfile << flight[i].returnFlight << endl;
					myfile << flight[i].returnDate << endl;
					myfile << flight[i].returnTime << endl;
				}
				clearline("Booking successfully recorded.");
				myfile.close();
			}
			break;
		}
		else if (confirmBooking == 'N' || confirmBooking == 'n') {
			clearline("Booking is canceled!");
			system("cls");
			displayHeader();
			cout << "\033[1;36m" << "Press enter again to back to main menu." << "\033[0m" << endl;
			break;
		}
		else {
			clearline("Invalid input! Please enter only Y or N.");
		}
	}
	system("cls");
}

//Display function
void FlightSchedule() {
	cout << "\033[1;33m" << "Flight Available : " << "\t\t\tAvailable Departure / Return Time Slots :\n" << "\033[0m" << endl;
	cout << "1. KL - Penang    --> RM200" << "\t\t1. 08:00 A.M." << endl;
	cout << "2. Penang - KL    --> RM200" << "\t\t2. 13:00 P.M." << endl;
	cout << "3. KL - Johor     --> RM200" << "\t\t3. 18:00 P.M." << endl;
	cout << "4. Johor - KL     --> RM200" << "\t\t4. 23:00 P.M." << endl;
	cout << "5. KL - Singapore --> RM250" << endl;
	cout << "6. Singapore - KL --> RM250" << endl;
	cout << "7. KL - Bangkok   --> RM300" << endl;
	cout << "8. Bangkok - KL   --> RM300\n" << endl;
}
void menu() {
	cout << "\033[1;33m" << "1. Book Flight Ticket(s)" << "\t\t\t\t\t 2. Edit Booking" << "\t\t\t\t\t  3. Perform Transaction" << "\033[0m" << endl;
	cout << "\033[1;33m" << "4. Check In Flight" << "\t\t\t\t\t\t 5. Print Invoice" << "\t\t\t\t\t  6. Quit\n" << "\033[0m" << endl;
}
void editMenu() {
	cout << "\033[1;36m" << "Please select the item to amend\n" << "\033[0m" << endl;
	cout << "\033[1;33m" << "1. Departure Flight" << "\t4. Return Flight" << "\033[0m" << endl;
	cout << "\033[1;33m" << "2. Departure Date" << "\t5. Return Date" << "\033[0m" << endl;
	cout << "\033[1;33m" << "3. Departure Slot" << "\t6. Return Slot" << "\033[0m" << endl;

	cout << "\nSelect : ";
}

//Validation for Name, check if the name is only alphabet
bool isAlphabetOnly(const string& name) {
	for (char ch : name) {
		if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))) {
			return false;
		}
	}
	return true;
}

//Validation for Date,check the date format is correct
bool validDate(const string& date) {
	if (date.length() != 10) return false;
	if (date[2] != '/' || date[5] != '/') return false;

	for (int i = 0; i < date.length(); i++) {
		if (i == 2 || i == 5) continue;
		if (!isdigit(date[i])) return false;
	}

	int day = (date[0] - '0') * 10 + (date[1] - '0');//convert dat into integer for comparison and calculation
	int month = (date[3] - '0') * 10 + (date[4] - '0');//convert month to integer for comparison and calculation
	int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');//convert year to integer for comparison and calculation

	if (month < 1 || month > 12) return false;
	if (day < 1 || day > 31) return false;
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;

	bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));

	if (month == 2) {
		if ((isLeap && day > 29) || (!isLeap && day > 28)) return false;
	}
	return true;
}

//to validate is the return date is in future of depart date
bool returnDate(const string& departureDate, const string& returnDate) {
	if (!validDate(returnDate)) {
		return false;
	}
	int departDay = (departureDate[0] - '0') * 10 + (departureDate[1] - '0');//convert day into integer for comparison and calculation
	int departMonth = (departureDate[3] - '0') * 10 + (departureDate[4] - '0');//convert month into integer for comparison and calculation
	int departYear = (departureDate[6] - '0') * 1000 + (departureDate[7] - '0') * 100 + (departureDate[8] - '0') * 10 + (departureDate[9] - '0');//convert year to integer for calculation and comparison
	//do the same operation to return date
	int returnDay = (returnDate[0] - '0') * 10 + (returnDate[1] - '0');
	int returnMonth = (returnDate[3] - '0') * 10 + (returnDate[4] - '0');
	int returnYear = (returnDate[6] - '0') * 1000 + (returnDate[7] - '0') * 100 + (returnDate[8] - '0') * 10 + (returnDate[9] - '0');
	//compare both depart and return date
	if (returnYear > departYear) {
		return true;
	}
	else if (returnYear == departYear) {
		if (returnMonth > departMonth) {
			return true;
		}
		else if (returnMonth == departMonth) {
			if (returnDay > departDay) {
				return true;
			}
		}
	}
	return false;
}

//do the similar validation for depart date to see if it is before the return date
//To validate is the depart date is before return date in editing booking
bool departBeforeReturn(const string& departureDate, const string& returnDate) {
	if (!validDate(departureDate)) {
		//cout << "Invalid Departure Date." << endl;
		return false;
	}
	//integer conversion for component in depart date
	int departDay = (departureDate[0] - '0') * 10 + (departureDate[1] - '0');
	int departMonth = (departureDate[3] - '0') * 10 + (departureDate[4] - '0');
	int departYear = (departureDate[6] - '0') * 1000 + (departureDate[7] - '0') * 100 + (departureDate[8] - '0') * 10 + (departureDate[9] - '0');
	//integer conversion for component in return date
	int returnDay = (returnDate[0] - '0') * 10 + (returnDate[1] - '0');
	int returnMonth = (returnDate[3] - '0') * 10 + (returnDate[4] - '0');
	int returnYear = (returnDate[6] - '0') * 1000 + (returnDate[7] - '0') * 100 + (returnDate[8] - '0') * 10 + (returnDate[9] - '0');
	//compare both depart date and return date to see if the depart date is before return date
	if (departYear < returnYear) {
		return true;
	}
	else if (departYear == returnYear) {
		if (departMonth < returnMonth) {
			return true;
		}
		else if (departMonth == returnMonth) {
			if (departDay < returnDay) {
				return true;
			}
		}
	}
	return false;
}

//Validation for flight mathing
int validReturnFlight(int departFlight, int currentReturnFlight) {
	int adjustedReturnFlight = currentReturnFlight;
	char selection;

	// Adjust return flight number to match pairing
	if (adjustedReturnFlight % 2 != 0) {
		adjustedReturnFlight += 1;
	}
	else {
		adjustedReturnFlight -= 1;
	}

	// If adjusted flight dont match the departure, ask for confirmation
	if (adjustedReturnFlight != departFlight) {
		cout << "Are you sure choosing a return that does not match the depart?" << endl;
		cout << "Please confirm (Y/N)          : ";
		cin >> selection;

		if (selection != 'Y' && selection != 'y') {
			cout << "Return Flight                 : ";
			cin >> currentReturnFlight;

			while (cin.fail() || currentReturnFlight < 1 || currentReturnFlight > 8) {
				cin.clear();
				cin.ignore(1000, '\n');
				clearline("Invalid Return Flight. Please choose flight 1-8");
				cout << "Return Flight                 : ";
				cin >> currentReturnFlight;
			}
		}
	}
	return currentReturnFlight;
}

void readPaymentCheckIn(CheckIn_Details& details) {
	ifstream myfile;
	myfile.open(currentUser + "_paymentCheckIn.txt");
	if (!myfile.is_open()) {
		return;
	}
	else {
		myfile >> details.total_price;
		myfile.ignore();
		getline(myfile, details.payment_status);
		for (int i = 0; i < noTickets; i++) {
			getline(myfile, details.passenger_flight[i].CheckIn_name.first_name);
			getline(myfile, details.passenger_flight[i].CheckIn_name.last_name);
			getline(myfile, details.passenger_flight[i].passport_num);
			getline(myfile, details.passenger_flight[i].contact_name.first_name);
			getline(myfile, details.passenger_flight[i].contact_name.last_name);
			getline(myfile, details.passenger_flight[i].mobile_num);
		}
		getline(myfile, details.checkIn_status);
		myfile.close();
	}
}

//perform payment
void payment() {
	double departticketPrice[9] = { 0, 200, 200, 200, 200, 250, 250, 300, 300 };
	double returnticketPrice[9] = { 0, 200, 200, 200, 200, 250, 250, 300, 300 };
	string departFromTo[9] = { "", "KL - Penang", "Penang - KL", "KL - Johor", "Johor - KL", "KL - Singapore", "KL - Singapore", "KL - Bangkok", "Bangkok - KL" };
	string returnFromTo[9] = { "", "KL - Penang", "Penang - KL", "KL - Johor", "Johor - KL", "KL - Singapore", "KL - Singapore", "KL - Bangkok", "Bangkok - KL" };
	string departClockTime[9] = { "8:00 A.M.", "1:00 P.M.", "6:00 P.M.", "11:00 P.M." };
	string returnClockTime[9] = { "8:00 A.M.", "1:00 P.M.", "6:00 P.M.", "11:00 P.M." };
	//declaration of array to identify ticket price, depart and return location, depart and return time

	BookingDetails flight_details = flight[0]; //initialize array as flight[0] (one of the booking details from the global struct flight)
	double TotalPrice = (departticketPrice[flight_details.departureFlight] + returnticketPrice[flight_details.returnFlight]) * noTickets; //initialize total price of the tickets booked
	char payment, transact;

	cout << "\033[1;36m" << "==================================================================================================================================================" << "\033[0m" << endl;
	cout << "Total Flight Ticket(s) : " << noTickets << endl;
	cout << "Departure Flight       : " << flight_details.departureDate << ", "
		<< departFromTo[flight_details.departureFlight] << ", "
		<< departClockTime[flight_details.departTime] << endl;
	cout << "Return Flight          : " << flight_details.returnDate << ", "
		<< returnFromTo[flight_details.returnFlight] << ", "
		<< returnClockTime[flight_details.returnTime] << endl;
	cout << "Total Payment          : (RM" << departticketPrice[flight_details.departureFlight]
		<< " + RM" << returnticketPrice[flight_details.returnFlight] << ") * "
		<< noTickets << " = RM " << TotalPrice << endl;
	cout << "\033[1;36m" << "==================================================================================================================================================" << "\033[0m" << endl;

	//display booking details to users
	payment = getYesNoInput("Continue for Payment? (y-yes, n-no): "); //perform payment
	system("cls");

	//payment process
	if (payment == 'y' || payment == 'Y') {
		int payment_option;
		do {
			displayHeader();
			paymentHeader();
			cout << "Please choose your payment method:\n" << endl;
			cout << "\033[1;33m" << "1. Credit Card/Debit Card" "\t\t\t\t\t2. Bank Transfer" << "\033[0m\n" << endl;

			payment_option = getValidatedIntInput("Choice: ", 1, 2);

			if (payment_option < 1 || payment_option > 2) {
				clearline("Invalid Option! Please select again.");
			}
			system("cls");
		} while (payment_option < 1 || payment_option > 2);
		if (payment_option == 1) {
			displayHeader();
			paymentHeader();
			cout << "Payment Method            : Credit Card/Debit Card" << endl;
			cout << "Transfer Amount           : RM " << TotalPrice << endl;
			string card_holder = validateCardHolder();
			string card_num = validateCardNumber();
			string card_date = validateCardDate();
			string card_code = validateSecurityCode();
		}
		else if (payment_option == 2) {
			string bank_account;
			int bankname;
			displayHeader();
			paymentHeader();
			cout << "Payment Method            : Bank Transfer" << endl;
			cout << "Transfer Amount           : RM " << TotalPrice << endl;
			cout << "Bank Name                 : 1. JuneBank\t  2. OCCB Bank\t3. Private Bank" << endl;
			bankname = getValidatedIntInput("Choice                    : ", 1, 3);
			bank_account = validateBankAccountNumber();
		}

		//transaction confirmation
		cout << endl;
		transact = getYesNoInput("Confirm Transaction? (y-yes, n-no): ");
		system("cls");
		displayHeader();
		paymentHeader();

		//rewriting paymentCheckIn (change payment_status)
		if (transact == 'Y' || transact == 'y') {
			showLoadingBar("Proccesing Transaction");
			ofstream paymentCheckInfile(currentUser + "_paymentCheckIn.txt");
			paymentCheckInfile << TotalPrice << endl;
			paymentCheckInfile << "Paid" << endl;
			for (int i = 0; i < noTickets * 6; i++) {
				paymentCheckInfile << "NULL" << endl;
			}
			paymentCheckInfile << "Not Check";
			paymentCheckInfile.close();
			cout << "\nTransaction Completed Successfully!" << endl;
			cout << "Payment Status: Paid" << endl;
		}
		else {
			cout << "\nTransaction Cancelled." << endl;
		}
	}
	else {
		displayHeader();
		cout << "\033[1;31m" << "Going back to main menu.." << "\033[0m" << endl;
		Sleep(2000);
	}
}

//validation for card holder name (used in payment())
string validateCardHolder() {
	string card_name;
	bool valid;
	do {
		valid = true;
		cout << "Card Holder Name          : ";
		getline(cin, card_name);
		//check if input is not empty
		if (card_name.length() == 0) {
			clearline("Name cannot be empty. Please re-enter.");

			valid = false;
			continue;
		}
		//check if every elements are not digits
		for (char c : card_name) {
			if (!isalpha(c) && c != ' ') {
				valid = false;
				clearline("Invalid name! Only alphabets and spaces allowed. Please re-enter.");

				break;
			}
		}
	} while (!valid);
	return card_name;
}

// validation for card number (used in payment())
string validateCardNumber() {
	string card_num;
	bool valid;
	do {
		valid = true;
		cout << "Card Number (16 digits)   : ";
		getline(cin, card_num);
		//check if input length = 16 digits
		if (card_num.length() != 16) {
			clearline("Card number must be exactly 16 digits. Please re-enter.");
			valid = false;
			continue;
		}
		//check if every elements are digits
		for (char c : card_num) {
			if (!isdigit(c)) {
				valid = false;
				clearline("Invalid card number! Only digits allowed. Please re-enter.");
				break;
			}
		}
	} while (!valid);
	return card_num;
}

//validation for card date (used in payment())
string validateCardDate() {
	string card_date;
	bool valid;
	do {
		valid = true;
		cout << "Card Valid Date (MM/YYYY) : ";
		getline(cin, card_date);
		//validate card date format
		if (card_date.length() != 7 || card_date[2] != '/') {
			clearline("Invalid format! Must be MM/YYYY. Please re-enter.");
			valid = false;
			continue;
		}

		string month = card_date.substr(0, 2);
		string year = card_date.substr(3, 4);
		// Check if month and year are digits
		if (!isdigit(month[0]) || !isdigit(month[1]) ||
			!isdigit(year[0]) || !isdigit(year[1]) || !isdigit(year[2]) || !isdigit(year[3])) {
			clearline("Invalid date! Month and year must be digits. Please re-enter.");
			valid = false;
			continue;
		}
		int month_num = stoi(month);
		//validate month range 
		if (month_num < 1 || month_num > 12) {
			clearline("Invalid month! Must be between 01 and 12. Please re-enter.");
			valid = false;
		}
	} while (!valid);

	return card_date;
}

//validate card security code (used in payment())
string validateSecurityCode() {
	string security_code;
	bool valid;
	do {
		valid = true;
		cout << "Security Code             : ";
		getline(cin, security_code);
		//validate security code length
		if (security_code.length() != 3) {
			clearline("Invalid security code length! Must be 3 digits. Please re-enter.");
			valid = false;
			continue;
		}
		//check if security code input is all digits
		for (char c : security_code) {
			if (!isdigit(c)) {
				valid = false;
				clearline("Invalid security code! Only digits allowed.Please re - enter.");
				cout << "\r" << string(100, ' ') << "\r";
				break;
			}
		}
	} while (!valid);
	return security_code;
}

//validate bank account number (used in oayment())
string validateBankAccountNumber() {
	string accountNumber;
	bool valid;
	do {
		valid = true;
		cout << "Enter Bank Account Number : ";
		getline(cin, accountNumber);
		//validate bank account format
		if (accountNumber.length() < 10 || accountNumber.length() > 16) {
			clearline("Invalid length! Must be between 10 and 16 digits.");
			valid = false;
			continue;
		}
		//check if every element is digits
		for (char c : accountNumber) {
			if (!isdigit(c)) {
				clearline("Invalid input! Only digits allowed.");
				valid = false;
				break;
			}
		}
	} while (!valid);
	return accountNumber;
}


//decoration - loading bar
void showLoadingBar(string loading_message) {
	cout << loading_message << ": [";
	for (int i = 0; i < 60; ++i) cout << " ";
	cout << "]\r" << loading_message << ": [";
	cout.flush();

	for (int i = 0; i < 60; ++i) {
		cout << "\033[1;32m" << "#" << "\033[0m";
		cout.flush();
		this_thread::sleep_for(chrono::milliseconds(75));
	}
	cout << "] Done!" << endl;
	Sleep(2000);
}

//decoration - loading bar
void showLoadingBarInvoice(string loading_message) {
	cout << loading_message << ": [";
	for (int i = 0; i < 60; ++i) cout << " ";
	cout << "]\r" << loading_message << ": [";
	cout.flush();

	for (int i = 0; i < 60; ++i) {
		cout << "\033[1;32m" << "#" << "\033[0m";
		cout.flush();
		this_thread::sleep_for(chrono::milliseconds(75));
	}
	cout << "] Invoice printed, please check your folder!" << endl;
	Sleep(2000);
}

// General yes/no input validation function (used in payment())
char getYesNoInput(const string& promptMessage) {
	string input;
	do {
		cout << promptMessage;
		getline(cin, input);
		// Check if input is empty
		if (input.empty()) {
			clearline("Input cannot be empty. Please enter Y or N.");
			continue;
		}
		// Check if input is a single valid character
		if (input.length() == 1 && (input[0] == 'y' || input[0] == 'Y' || input[0] == 'n' || input[0] == 'N')) {
			return input[0]; // Valid input
		}
		else {
			clearline("Invalid input. Please enter Y or N.");
		}
	} while (true);
}

//perform check in
void checkIn(CheckIn_Details& details) {
	char checkInConfirmation;
	cout << "\033[33mPayment Status: Paid\033[0m" << endl;
	cout << "\033[33m~Proceed to check in~\033[0m" << endl;
	//perform check in process
	for (int i = 0; i < noTickets; i++) {
		cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m" << endl;
		cout << "\033[1;36m" << "Passenger " << i + 1 << "\033[0m" << endl;
		cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m" << endl;
		do {
			cout << "First Name                                     : ";
			getline(cin, details.passenger_flight[i].CheckIn_name.first_name);
			if (!isValidName(details.passenger_flight[i].CheckIn_name.first_name)) {
				clearline("Invalid first name. Please use letters, spaces, or hyphens only.");
			}
		} while (!isValidName(details.passenger_flight[i].CheckIn_name.first_name));

		do {
			cout << "Last Name                                      : ";
			getline(cin, details.passenger_flight[i].CheckIn_name.last_name);
			if (!isValidName(details.passenger_flight[i].CheckIn_name.last_name)) {
				clearline("Invalid last name. Please use letters, spaces, or hyphens only.");

			}
		} while (!isValidName(details.passenger_flight[i].CheckIn_name.last_name));

		do {
			cout << "Passport Number                                : ";
			getline(cin, details.passenger_flight[i].passport_num);
			if (!isValidPassportNumber(details.passenger_flight[i].passport_num)) {
				clearline("Invalid passport number. It must be 6-9 characters, start with a letter or digit, and the rest digits only.");

			}
		} while (!isValidPassportNumber(details.passenger_flight[i].passport_num));

		//users input contact details
		if (i == 0) {
			inputPassengerDetails(details, i);
		}
		else {
			char reuse;
			reuse = getYesNoInput("Same contact person as previous? (y-yes, n-no) : ");

			if (reuse == 'y' || reuse == 'Y') {

				if (i > 1) {
					int contactChoice;
					string number = to_string(i);
					string output_sentence = "Which same contact person ? (1 to " + number + ")           : ";
					contactChoice = getValidatedIntInput(output_sentence, 1, i);


					details.passenger_flight[i].contact_name = details.passenger_flight[contactChoice - 1].contact_name;
					details.passenger_flight[i].mobile_num = details.passenger_flight[contactChoice - 1].mobile_num;
					cout << "Contact Person First Name                      : " << details.passenger_flight[i].contact_name.first_name << endl;
					cout << "Contact Person Last Name                       : " << details.passenger_flight[i].contact_name.last_name << endl;
					cout << "Contact Person Phone Number                    : " << details.passenger_flight[i].mobile_num << endl;
				}
				else {
					details.passenger_flight[i].contact_name = details.passenger_flight[0].contact_name;
					details.passenger_flight[i].mobile_num = details.passenger_flight[0].mobile_num;
					cout << "Contact Person First Name                      : " << details.passenger_flight[i].contact_name.first_name << endl;
					cout << "Contact Person Last Name                       : " << details.passenger_flight[i].contact_name.last_name << endl;
					cout << "Contact Person Phone Number                    : " << details.passenger_flight[i].mobile_num << endl;
				}
			}
			else {
				inputPassengerDetails(details, i);
			}
		}
		cout << endl;
	}
	cout << "\033[1;36m" << "--------------------------------------------------------------------------------------------------------------------------------------------------" << "\033[0m\m" << endl;

	checkInConfirmation = getYesNoInput("Confirm Check In? (y-yes, n-no): ");

	//rewrite checkInPayment
	if (checkInConfirmation == 'y' || checkInConfirmation == 'Y') {
		system("cls");
		displayHeader();
		showLoadingBar("Processing Information");
		details.checkIn_status = "Checked";
		ofstream checkInPayment;
		checkInPayment.open(currentUser + "_paymentCheckIn.txt");
		checkInPayment << details.total_price << endl;
		checkInPayment << details.payment_status << endl;
		for (int i = 0; i < noTickets; i++) {
			checkInPayment << details.passenger_flight[i].CheckIn_name.first_name << endl;
			checkInPayment << details.passenger_flight[i].CheckIn_name.last_name << endl;
			checkInPayment << details.passenger_flight[i].passport_num << endl;
			checkInPayment << details.passenger_flight[i].contact_name.first_name << endl;
			checkInPayment << details.passenger_flight[i].contact_name.last_name << endl;
			checkInPayment << details.passenger_flight[i].mobile_num << endl;
		}
		checkInPayment << details.checkIn_status;
		checkInPayment.close();
	}
	else {
		cout << "\033[1;36m" << "Going back to main menu..." << "\033[0m\n" << endl;
		Sleep(2000);
	}
}

//validation for mobile_num (used in checkIn())
bool isValidMobile(const string& mobile_num) {
	//validate malaysia mobile number format
	if (mobile_num.length() != 10 && mobile_num.length() != 11)
		return false;
	if (mobile_num.substr(0, 2) != "01")
		return false;
	for (char c : mobile_num) {
		if (!isdigit(c))
			return false;
	}
	return true;
}

//validation for passport number (used in checkIn())
bool isValidPassportNumber(const string& passport_num) {
	//validate Malaysia passport number
	if (passport_num.length() < 6 || passport_num.length() > 9)
		return false;

	if (!isalpha(passport_num[0]) && !isdigit(passport_num[0]))
		return false;

	for (size_t i = 1; i < passport_num.length(); i++) {
		if (!isdigit(passport_num[i])) {
			return false;
		}
	}
	return true;
}

//validation for name (used in checkIn() to validate contact name and passenger name)
bool isValidName(const string& name) {
	if (name.empty())
		return false;

	for (char c : name) {
		if (!isalpha(c) && c != ' ' && c != '-') {
			return false;
		}
	}
	return true;
}

//check in contact details when users do not choose previous contact details
void inputPassengerDetails(CheckIn_Details& details, int i) {
	do {
		cout << "Contact Person First Name                      : ";
		getline(cin, details.passenger_flight[i].contact_name.first_name);
		if (!isValidName(details.passenger_flight[i].contact_name.first_name)) {
			clearline("Invalid first name. Please use letters, spaces, or hyphens only.");

		}
	} while (!isValidName(details.passenger_flight[i].contact_name.first_name));

	do {
		cout << "Contact Person Last Name                       : ";
		getline(cin, details.passenger_flight[i].contact_name.last_name);
		if (!isValidName(details.passenger_flight[i].contact_name.last_name)) {
			clearline("Invalid last name. Please use letters, spaces, or hyphens only.");
		}
	} while (!isValidName(details.passenger_flight[i].contact_name.last_name));
	do {
		cout << "Contact Person Phone Number (e.g., 0123456789) : ";
		getline(cin, details.passenger_flight[i].mobile_num);
		if (!isValidMobile(details.passenger_flight[i].mobile_num)) {
			clearline("Invalid Malaysian mobile number. Please enter a valid number starting with 01 and 10-11 digits long.");
		}
	} while (!isValidMobile(details.passenger_flight[i].mobile_num));
}

//print invoice
void printInvoice(CheckIn_Details PassengerInfoList, BookingDetails BookingList[]) {
	ifstream invoicefile;
	invoicefile.open(currentUser + "_invoice.txt");
	if (!invoicefile) {
		cout << "No Booking Available" << endl;
		invoicefile.close();
	}
	else {
		invoicefile.close();
		ofstream invoicefile;
		invoicefile.open(currentUser + "_invoice.txt");

		invoicefile << "Welcome to JSJK Airline Company" << endl;
		invoicefile << "Departure Flight: " << BookingList[0].departureFlight << endl;
		invoicefile << "Departure Date: " << BookingList[0].departureDate << endl;
		invoicefile << "Departure Slot: " << BookingList[0].departTime << endl;
		invoicefile << "Return Flight: " << BookingList[0].returnFlight << endl;
		invoicefile << "Return Date: " << BookingList[0].returnDate << endl;
		invoicefile << "Return Slot: " << BookingList[0].returnTime << endl;
		invoicefile << endl;

		for (int i = 0; i < noTickets; i++) {
			invoicefile << "Passenger " << i + 1 << endl;
			invoicefile << "Name: " << PassengerInfoList.passenger_flight[i].CheckIn_name.first_name << " " << PassengerInfoList.passenger_flight[i].CheckIn_name.last_name << endl;
			invoicefile << "Passport Number: " << PassengerInfoList.passenger_flight[i].passport_num << endl;
			invoicefile << "Contact Person: " << PassengerInfoList.passenger_flight[i].contact_name.first_name << " " << PassengerInfoList.passenger_flight[i].contact_name.last_name << endl;
			invoicefile << "Contact Person Mobile No: " << PassengerInfoList.passenger_flight[i].mobile_num << endl;
			invoicefile << endl;
		}
		invoicefile.close();
		showLoadingBarInvoice("Printing invoice");
	}
}
//to creat payment check in and invoice file when 1 or 2 is selected
void createPaymentCheckInInvoiceFile(int Num_Passengers) {

	ofstream outfile;
	ofstream outfile1;
	outfile.open(currentUser + "_paymentCheckIn.txt");
	outfile1.open(currentUser + "_invoice.txt");
	double TotalPrice;
	CheckIn_Details PaymentCheckInInfo;
	double departticketPrice[9] = { 0, 200, 200, 200, 200, 250, 250, 300, 300 };
	double returnticketPrice[9] = { 0, 200, 200, 200, 200, 250, 250, 300, 300 };

	PaymentCheckInInfo.payment_status = "Not Paid";
	PaymentCheckInInfo.checkIn_status = "Not Checked";
	TotalPrice = (departticketPrice[flight[0].departureFlight] + returnticketPrice[flight[0].returnFlight]) * noTickets;
	outfile << TotalPrice << endl;
	outfile << PaymentCheckInInfo.payment_status << endl;
	for (int i = 0; i < noTickets * 6; i++) {
		outfile << "NULL" << endl;
	}
	outfile << "Not Checked" << endl;
	outfile.close();
	outfile1.close();
}

//validate int choice input (used in payment() and checkIn())
int getValidatedIntInput(const string& prompt, int min, int max) {
	int value;
	string input;
	while (true) {
		cout << prompt;
		getline(cin, input);
		// Check if input is a valid integer
		bool isValid = true;
		for (char c : input) {
			if (!isdigit(c)) {
				isValid = false;
				break;
			}
		}
		if (isValid && !input.empty()) {
			value = stoi(input);
			if (value >= min && value <= max) {
				return value; // valid input
			}
		}
		clearline("Invalid input. Please enter a number between " + to_string(min) + " and " + to_string(max) + ".");
	}
}

//to see if the name is not empty but still can capture the input when the input is two words contain " "
bool nameIsNotEmpty(const string& input) {
	for (int i = 0; i < input.length(); i++) {
		if (input[i] != ' ') {
			return true;
		}
	}
	return false;
}

//to remove the space in name for validation without integer
string removeSpaces(const string& input) {
	string result = "";
	for (int i = 0; i < input.length(); i++) {
		if (input[i] != ' ') {
			result += input[i];
		}
	}
	return result;
}

//Header Decoration
void displayHeader() {
	cout << "\033[1;33m" << R"(
 ________________________________________________________________________________________________________________________________________________
|   __________________________________________________________________________________________________________________________________________   |
| /   _______  ______  _______  _    __        _      _        _  _                   ______                       __|__                      \  |
| |  |___  __||  ____||___  __|| |  / /       / \    (_)      | |(_)                 |  ____|           ------@--@--(_)--@--@------            | |  
| |      | |  | |____     | |  | |_/ /       / _ \   | | ____ | || | _____   ___     | |      _____  _________  ______  _____  _____  _     _  | |
| |   _  | |  |____  | _  | |  |  _  \      / /_\ \  | ||  __|| || ||  _  | / _ \    | |     |  _  ||  _   _  ||   _  ||  _  ||  _  || |   | | | |
| |  | |_| |   ____| || |_| |  | | \  \    / _____ \ | || |   | || || | | |/ ___/    | |____ | |_| || | | | | ||  |_| || |_| || | | || |___| | | |
| |  |_____|  |______||_____|  |_|  \__\  /_/     \_\|_||_|   |_||_||_| |_|\____|    |______||_____||_| |_| |_||  ____||___/\||_| |_| \____| | | |
| |                                                                                                            |_|                   |_______| | |
| \___________________________________________________________________________________________________________________________________________/  |
|________________________________________________________________________________________________________________________________________________|                                                                                                        
)" << "\033[0m";
}

//Decoration
void ticketBooking() {
	cout << "\033[1;36m" << "==================================================================================================================================================" << "\033[0m" << endl;
	cout << "\033[1;34m" << "                                                                  Ticket Booking                                                                  " << "\033[0m" << endl;
	cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
}

//Decoration
void editingHeader() {
	cout << "\033[1;36m" << "==================================================================================================================================================" << "\033[0m" << endl;
	cout << "\033[1;34m" << "                                                                      Editing                                                                     " << "\033[0m" << endl;
	cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
}

void paymentHeader() {
	cout << "\033[1;36m" << "==================================================================================================================================================" << "\033[0m" << endl;
	cout << "\033[1;34m" << "                                                                      Payment                                                                     " << "\033[0m" << endl;
	cout << "\033[1;36m" << "==================================================================================================================================================\n" << "\033[0m" << endl;
}