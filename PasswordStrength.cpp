// Written by: Arianna Almond
// Presented: 12/8/2025
// Purpose: Checks if the password is strong enough.

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main(){ 
    string password;
    cout <<"Please enter a password: ";
    getline (cin, password);
// Checks if they are all ture or false.
    bool vaildLength = password.length() >= 8;
    bool vaildLowercase = false;
    bool validUpercase = false;
    bool validDidgit = false;
    bool validSpecialchar = false;

    string SpecialChar = "!@#$%^&*()-_=+[]{};:'\",.<>/?";



// Cheaking each character.
// Loop through password
    for (char c : password) {
        if (islower(c)) 
            vaildLowercase = true;

        if (isupper(c)) 
            validUpercase = true;

        if (isdigit(c)) 
            validDidgit = true;

        if (SpecialChar.find(c) != string::npos)// string not found 
            validSpecialchar = true;
    }



   //criteria met
    int strengthCount = 0;
    strengthCount += vaildLength;
    strengthCount += vaildLowercase;
    strengthCount += validUpercase;
    strengthCount += validDidgit;
    strengthCount += validSpecialchar;




    // Output
    cout << "Length is Good: " << (vaildLength ? "Yes" : "No") << endl;
    cout << "Lowercase: " << (vaildLowercase ? "Yes" : "No") << endl;
    cout << "Uppercase: " << (validUpercase ? "Yes" : "No") << endl;
    cout << "Digits: " << (validDidgit ? "Yes" : "No") << endl;
    cout << "Special Character: " << (validSpecialchar ? "Yes" : "No") << endl;



    // Determine password strength
    string rating;

    if (strengthCount <= 2) 
        rating = "Weak";
    else if (strengthCount == 3) 
        rating = "Medium";
    else if (strengthCount == 4) 
        rating = "Strong";
    else 
        rating = "Very Strong";

    cout << "Password Strength: " << rating << endl;

    return 0;
}









