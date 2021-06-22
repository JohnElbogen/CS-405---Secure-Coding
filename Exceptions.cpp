// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// custom exception creation
struct CustomException : public std::exception
{
    const char* what() const throw ()
    {
        return "Custom Exception";
    }
};

bool do_even_more_custom_application_logic()
{

    std::cout << "Running Even More Custom Application Logic." << std::endl;
    
    //Throws a standard exception
    throw std::exception("Error Test");

    return true;


}
void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    try{
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }

    }
    // expected to catch the do_even_more_custom_application_logic() exception
    catch (std::exception e) {
        std::cout << "An exception occurred." << e.what() << '\n';
    }

    std::cout << "Leaving Custom Application Logic." << std::endl;
    // throws the custome exception class
    throw (CustomException());

}

float divide(float num, float den)
{
    // no standard exception for divide by zero, but can check for 0 in the denominator and throw an overflow error
    if (den == 0)
        throw std::overflow_error("Divide by zero exception");
    return (num / den);
}

void do_division() noexcept
{

    float result = 0;
    float numerator = 10.0f;
    float denominator = 0;

    // tries and catches, the divide function, and displays the .what() error.
    try { result = divide(numerator, denominator); }
    catch (std::overflow_error e) {
        std::cout << e.what() << " -> ";
    }
    std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
}

int main()
{
    // tries and catches all thrown exceptions
    try {
        std::cout << "Exceptions Tests!" << std::endl;
        do_division();
        do_custom_application_logic();
    }
    catch (CustomException& e) {
        std::cout << "Error Code: " << e.what() << '\n';
    }
    //catches standard exception
    catch (std::exception e) {
        std::cout << "Error Code: " << e.what() << '\n';
    }
    // catches all other cases of exceptions
    catch (...)
    {
        std::cout << "Exception caught of undetermined type\n";
    }
 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
