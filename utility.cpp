#include <algorithm>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include "utility.h"

// Music Settings
sf::Music music; // Global from 'playBackgroundMusic'
sf::Music SFX; // Global from 'playSFX'

void displayFormat(size_t length, char symbol) {
    std::string repeated(length, symbol);
    std::cout << repeated;
    delayMs(50);
}

void displaySpacedFormat(size_t length, char symbol) {
    std::string repeated(length, symbol); // create the string with repeated characters
    std::cout << repeated;
    delayMs(50);
    std::cout << '\n';
}

void displayAlternatingFormat(size_t length, char firstSymbol, char secondSymbol) {
    for (size_t i = 0; i < length; ++i) {
        std::cout << (i % 2 == 0 ? firstSymbol : secondSymbol);
    } delayMs(50);
}

void displayBlockFormat(size_t width, size_t height, char symbol) {
    for (size_t i = 0; i < height; ++i) {
        displayFormat(width, symbol);
        std::cout << '\n';
    }
}

void displayBlockSpacedFormat(size_t width, size_t height, char symbol) {
    for (size_t i = 0; i < height; ++i) {
        std::string repeated(width, symbol); // create the string with repeated characters
        std::cout << repeated;
        delayMs(50);
        std::cout << '\n';
    } std::cout << '\n';
}

void displayBorder(size_t height, char symbol) {
    for (int i = 0; i < height; ++i) {
            std::cout << '#';
            std::string repeated(70, ' ');
            std::cout << repeated;
            std::cout << '#';
        std::cout << '\n';
    }
}

void displayHLine(int x, int y, size_t length, char symbol) {
    goTo(x, y);
    for (int i = 0 ; i < length; ++i) {
        std::cout << symbol;
    }
}

void displayVLine(int x, int y, size_t length, char symbol) {
    goTo(x, y);
    for (int i = 0 ; i < length; ++i) {
        std::cout << symbol;
        goTo(x, y + i);
    }
}

void space(size_t n) {
    for (size_t i = 0; i < n; ++i) { std::cout << '\n'; }
}

void delayS(int s) {
    std::this_thread::sleep_for(std::chrono::seconds(s));
}

void delayMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void characterDelayAnimation(std::string stringInput, int ms) {
    for (int i = 0; i < stringInput.length(); ++i) {
        std::cout << stringInput[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
}

void lineDelayAnimation(std::string stringInput, int ms) {
    std::cout << stringInput;
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void pressEnter(std::string process) {
    characterDelayAnimation("Press 'Enter' to " + process + "...", 25);
    std::cin.get();
}

void trim(std::string& stringInput) {
    stringInput.erase(0, stringInput.find_first_not_of(" ")); // Remove leading whitespaces
    stringInput.erase(stringInput.find_last_not_of(" ") + 1); // Remove trailing whitespaces
}

void toLowercase(std::string& stringInput) {
    transform(stringInput.begin(), stringInput.end(), stringInput.begin(), ::tolower);
}

void toUppercase(std::string& stringInput) {
    transform(stringInput.begin(), stringInput.end(), stringInput.begin(), ::toupper);
}

void capitalize(std::string& stringInput) {
    stringInput[0] = toupper(stringInput[0]);
    for (int i = 1; i < stringInput.length(); ++i) {
        stringInput[i] = tolower(stringInput[i]);
    }
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void spinningAnimation(const std::string& toGenerate, int x) {
    char spinner_characters[4] = {'|', '/', '-', '\\'};
    std::cout << "...generating " << toGenerate << " [ ]";
    goTo(1, x);
    for (int i = 0; i < 40; ++i) {
        std::cout << spinner_characters[i % 4];
        delayMs(50);
        goTo(1, x);
    } goTo(1, x + 2); space(1);
}

void loadingBarAnimation(int x) {
    int percentage = 0;
    std::cout << " [          ] " << percentage << '\n';
    for (int i = 0; i < 10; ++i) {
        goTo(1, x);
        std::cout << '#';
    }
}

void centerText(std::string textInput) {
    int consoleWidth = 60;
    int margin = (consoleWidth - textInput.length()) / 2;

    // Display Header
    displayFormat(margin, ' ');
    std::cout << textInput;
    displayFormat(margin, ' ');
}

void hideCursor() {
    std::cout << "\e[?25l";
}
  
void showCursor() {
    std::cout << "\e[?25h";
}

void moveCursor(int up, int down, int right, int left) {
    std::cout << "\033[" << (up >= 0 ? up : 0) << 'A';
    std::cout << "\033[" << (down >= 0 ? down : 0) << 'B';
    std::cout << "\033[" << (right >= 0 ? right : 0) << 'C';
    std::cout << "\033[" << (left >= 0 ? left : 0) << 'D';
}

void goTo(int y, int x) {
    std::cout << "\033[" << x << ';' << y << 'H';
}

void playBackgroundMusic(std::string musicFileName, int volume) {
    // Load music from a file (must remain on disk while playing)
    if (!music.openFromFile("assets/" + musicFileName)) {
        std::cerr << "Error loading music file!" << std::endl;
        return;
    }

    music.setVolume(volume); // Set volume
    music.setLoop(true); // Optional: loop the music
    music.play();
}

void playSFX(std::string musicFileName, int volume) {
    // Load music from a file (must remain on disk while playing)
    if (!SFX.openFromFile("assets/" + musicFileName)) {
        std::cerr << "Error loading music file!" << std::endl;
        return;
    }

    SFX.setVolume(volume); // Set volume
    SFX.play();
}

int getOption(int optionCount, std::string orientation, int length, const int x[], const int y[]) {
  int current = 0;
  char key;

  while (true) {
    for (int i = 0; i < optionCount; ++i) {
      // Left cursor
      goTo(x[i] - 3, y[i]);
      std::cout << (i == current ? ">" : " ");

      // Right cursor
      goTo(x[i] + length, y[i]);
      std::cout << (i == current ? "<" : " ");
    }

    key = _getch();

    // Orientation - Horizontal
    if (orientation == "horizontal") {

        // Play SFX based on key pressed
        if (key == 75 || key == 77) playSFX("navigateOption.wav", 30);
        else playSFX("selectOption.wav", 50);

        if (key == 75) { // Left Arrow
        current = (current - 1 + optionCount) % optionCount;
        } else if (key == 77) { // Right Arrow
        current = (current + 1) % optionCount;
        } else if (key == 13) { // Enter
        break;
        }
    }

    // Orientation - Vertical
    if (orientation == "vertical") {

        // Play SFX based on key pressed
        if (key == 72 || key == 80) playSFX("navigateOption.wav", 30);
        else playSFX("selectOption.wav", 50);

        if (key == 72) { // Up Arrow
        current = (current - 1 + optionCount) % optionCount;
        } else if (key == 80) { // Down Arrow
        current = (current + 1) % optionCount;
        } else if (key == 13) { // Enter
        break;
        }
    }
  }

  return current;
}

std::time_t parseTimestamp(const std::string& timestamp) {
  std::tm tm = {};
  std::istringstream ss(timestamp);
  ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
  return std::mktime(&tm);
}

int getLatestSavefile() {
    std::ifstream file("data/saveFiles.json");
    
    if (!file) {
        std::cerr << "Failed to open saveFiles.json\n";
        return -1;
    }

    json data;
    file >> data;

    std::time_t latestTime = 0;
    int latestIndex = -1;


    for (int i = 0; i < data.size(); ++i) {
        std::string timestamp = data[i]["saveTimestamp"];
        std::time_t t = parseTimestamp(timestamp);
        if (t > latestTime) {
        latestTime = t;
        latestIndex = i;
        }
    }

  return latestIndex;
}