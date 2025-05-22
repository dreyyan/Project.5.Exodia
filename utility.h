#ifndef UTILITY_H
#define UTILITY_H

#include <cstddef>
#include <string>
#include <SFML/Audio.hpp>
#include "json.hpp"
using json = nlohmann::json;

// Displays a formatted line within the specified length using the specified symbol
void displayFormat(size_t length, char symbol);

// Displays a formatted line within the specified length using the specified symbol /w newline character
void displaySpacedFormat(size_t length, char symbol);

// Displays a formatted line with alternating symbols within the specified length
void displayAlternatingFormat(size_t length, char firstSymbol, char secondSymbol);

// Displays a formatted block within the specified width and height using the specified symbol
void displayBlockFormat(size_t width, size_t height, char symbol);

// Displays a formatted block within the specified width and height using the specified symbol /w newline character
void displayBlockSpacedFormat(size_t width, size_t height, char symbol);

// Displays a border within the specified height using the specified symbol
void displayBorder(size_t height, char symbol);

// Displays a horizontal line using x and y coordinates within the specified length using the specified symbol
void displayHLine(int x, int y, size_t length, char symbol);

// Displays a vertical line using x and y coordinates within the specified length using the specified symbol
void displayVLine(int x, int y, size_t length, char symbol);

// Outputs a newline escape sequence 'n' times
void space(size_t n);

// Outputs a delay within 'ms' milliseconds
void delayMs(int ms);

// Outputs a delay within 's' seconds
void delayS(int s);

// Displays the specified string character-by-character every 'ms' milliseconds
void characterDelayAnimation(std::string stringInput, int ms);

// Displays the specified string line-by-line every 'ms' milliseconds
void lineDelayAnimation(std::string stringInput, int ms);

// Prompts the user to press enter to continue with the process
void pressEnter(std::string process);

// Trim whitespaces at the front and end of the string
void trim(std::string& stringInput);

// Converts the specified string to lowercase
void toLowercase(std::string& stringInput);

// Converts the specified string to uppercase
void toUppercase(std::string& stringInput);

// Converts the first character of the specified string to uppercase
void capitalize(std::string& stringInput);

// Clears the console screen
void clearScreen();

// Displays a spinning animation at 'x' for a specified string 
void spinningAnimation(const std::string& toGenerate, int x);

// Displays a loading bar animation at 'x'
void loadingBarAnimation(int x);

// Centers the specified text in the console
void centerText(std::string textInput);

// Hide blinking cursor
void hideCursor();

// Show blinking cursor
void showCursor();

// Navigate the CLI using U/D/R/L values by ANSI escape codes
void moveCursor(int up, int down, int right, int left);

// Navigate the CLI using coordinate(x, y) values by ANSI escape codes
void goTo(int y, int x);

// Play a sound effect with the specified filename
void playSFX(std::string musicFileName, int volume);

// Play a looping background music with the specified filename 
void playBackgroundMusic(std::string musicFileName, int volume);

// Prompt user to navigate the console within a specified number of options using 'arrow' & 'enter' keys
int getOption(int optionCount, std::string orientation, int length, const int x[], const int y[]);

// Convert timestamp string to time_t
std::time_t parseTimestamp(const std::string& timestamp);

// Get the latest savefile from 'saveFiles.json'
int getLatestSavefile();

// Generate a random number using the Mersenne Twister Engine
int generateRandomNumber(int maxRange);
#endif