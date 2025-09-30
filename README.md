# Exodia
_Text-Based Fantasy RPG with C++ TUI_

**Exodia** is a text-based fantasy role-playing game (RPG) developed in C++ with a Text User Interface (TUI). Designed to immerse players in a rich fantasy world, Exodia offers interactive gameplay through a command-line interface, utilizing SFML for audio to enhance the experience. Players can explore, battle, and progress through a narrative-driven adventure, making it ideal for RPG enthusiasts and developers learning C++ game development.

The primary purpose of Exodia is to provide an engaging, text-based RPG experience while serving as an educational project for practicing C++ programming, TUI design, and audio integration.

## FEATURES
✅ **Interactive Gameplay** – Engage in a fantasy world with exploration, combat, and narrative choices.  
✅ **Text-Based Interface** – Navigate the game via a user-friendly TUI.  
✅ **Audio Integration** – Enhance immersion with sound effects using SFML audio.  

## FUTURE IMPLEMENTATIONS
🚀 **Story Expansion** – Add more quests, characters, and narrative branches.  
🚀 **Game Mechanics** – Implement advanced combat systems and character progression.  
🚀 **Cross-Platform Support** – Ensure compatibility across Windows, Linux, and macOS.  
🚀 **Save/Load System** – Add persistent game state saving.  

## UPDATES
🔄 Core gameplay loop implemented with exploration and basic combat.  
🔄 SFML audio integration for sound effects.  
🔄 TUI optimized for 60x22 console size.  

## PROJECT DETAILS
📌 **Author:** dreyyan  
📌 **Started:** 2025-04-07  
📌 **Finished:** Temporarily discontinued (near-releasable state)  

## TECH STACK
🛠️ **Language:** C++  
🛠️ **Libraries:** SFML (Audio, System)  

## INSTALLATION
### Prerequisites
- C++ compiler (e.g., g++ with MinGW for Windows)
- SFML library installed (version compatible with your system)
- Create a development environment:
  - Windows: Install MinGW and SFML via package manager or manual download.
  - Linux/macOS: Install SFML via package manager (e.g., `sudo apt install libsfml-dev` on Ubuntu).

### Install Dependencies
Download and configure SFML:
- Windows: Follow [SFML setup guide](https://www.sfml-dev.org/tutorials/2.6/start-vc.php).
- Linux: Install via `sudo apt install libsfml-dev` (or equivalent for your distro).
- macOS: Install via `brew install sfml`.

### Compilation
Compile the project using the provided command:
```
g++ -o test main.cpp utility.cpp game.cpp -lsfml-audio -lsfml-system
```

### Verify Installation
Ensure SFML is linked correctly by running the compiled executable. Check for errors related to missing SFML libraries.

## USAGE
### Running the Application
Set the command prompt size to 60x22 for optimal display:
- On Windows: `mode con: cols=60 lines=22`
- On Unix/macOS: Adjust terminal size to 60 columns by 22 rows.

Run the executable in an external console:
- **CMD**:
  ```
  start cmd /k "test.exe"
  ```
- **PowerShell** (edit path to your project):
  ```
  Start-Process "powershell.exe" -ArgumentList "-NoExit", "-Command", "C:\Users\dreyyan\Downloads\code\Projects\Project.5.Exodia\test.exe"
  ```

### Example Workflow
1. **Launch the Game**: Run `test.exe` in the configured console.
2. **Navigate TUI**: Use keyboard inputs to explore, interact with characters, or engage in combat.
3. **Experience Audio**: Hear sound effects during key game events (e.g., battles).

### Configuration
- Ensure the console size is set to 60x22 for proper display.
- Adjust SFML audio settings if needed (e.g., volume) via code or configuration files (if implemented).

## DEBUGGING
For issues, check console output for errors related to SFML audio or game logic. Run with:
```
./test  # Linux/macOS
test.exe  # Windows
```
Report issues via GitHub Issues for detailed troubleshooting.

## PROJECT STRUCTURE
- `main.cpp`: Entry point for the application.
- `utility.cpp`: Helper functions for game logic and TUI rendering.
- `game.cpp`: Core game mechanics and gameplay loop.

## CONTRIBUTING
Contributions are welcome! Fork the repo, make changes, and submit a pull request:
1. Create a feature branch: `git checkout -b feature/new-feature`
2. Commit changes: `git commit -m "Add new feature"`
3. Push: `git push origin feature/new-feature`
4. Open a pull request

Report issues or suggest features via GitHub Issues.

## LICENSE
This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.