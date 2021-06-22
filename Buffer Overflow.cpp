// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <assert.h> 

int main()
{
	std::cout << "Buffer Overflow Example" << std::endl;

	const std::string account_number = "CharlieBrown42";
	// std::string avoids buffer overflow problem
	// also, using std::string is preferred for storing a value
	std::string user_input;

	std::cout << "Enter a value: ";
	std::cin >> user_input;



	std::cout << "You entered: " << user_input << std::endl;
	std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
