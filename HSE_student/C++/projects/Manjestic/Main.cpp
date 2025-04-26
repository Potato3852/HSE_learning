#include "Game.hpp"
#include "Field.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <windows.h>
#include <sstream>

void configureConsole() {
    SetConsoleOutputCP(65001);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void printHelp() {
    std::cout << "\n\033[36mCrateMode Commands:\033[0m\n"
              << "  \033[33mX Y\033[0m    - Add cell at position\n"
              << "  \033[33mclear\033[0m  - Clear all cells\n"
              << "  \033[33mdone\033[0m   - Start simulation\n"
              << "  \033[33mhelp\033[0m   - Show this help\n"
              << "  \033[33mexit\033[0m   - Quit program\n\n";
}

void crateMode(Field& field, int width, int height) {
    std::string input;
    int x, y;
    
    printHelp();
    
    while(true) {
        std::cout << "\033[34mCrateMode>\033[0m ";
        std::getline(std::cin, input);
        
        if(input == "done") break;
        if(input == "exit") std::exit(0);
        if(input == "help") {
            printHelp();
            continue;
        }
        if(input == "clear") {
            field = Field(width, height);
            std::cout << "\033[32mField cleared!\033[0m\n";
            continue;
        }
        
        std::istringstream iss(input);
        if(iss >> x >> y) {
            if(x >= 0 && x < width && y >= 0 && y < height) {
                field.getCell(x, y).setState(true);
                std::cout << "\033[32mCell added at (" << x << ", " << y << ")\033[0m\n";
            } else {
                std::cout << "\033[31mInvalid coordinates! "
                          << "Range: [0-" << width-1 << "] [0-" << height-1 << "]\033[0m\n";
            }
        } else {
            std::cout << "\033[31mInvalid command!\033[0m\n";
        }
    }
}

int main() {
    configureConsole();
    
    Game game;
    game.loadFromFile("world.json");
    
    Field field(game.getWidth(), game.getHeight());

    std::cout << "\033[2J\033[?25l";

    std::cout << "\033[H";
    std::cout << "▛▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▜\n";
    std::cout << "▌     Game of Life   ▐\n";
    std::cout << "▙▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▟\n\n";
    std::cout << "1. Solo Mode (Patterns)\n";
    std::cout << "2. Anarchy Mode (Random)\n";
    std::cout << "3. Create Mode (Create cells)\n";
    std::cout << "> Choice [1-3]: ";
    
    int mode;
    std::cin >> mode;

    if(mode == 1) {
        std::cout << "\n\033[36mAvailable Patterns:\033[0m\n";
        std::cout << "1. Glider      4. Gosper Gun\n";
        std::cout << "2. Blinker     5. R-pentomino\n";
        std::cout << "3. Block       6. Spaceship\n";
        std::cout << "7. Beehive     8. Pentadecathlon\n";
        std::cout << "> Select pattern [1-8]: ";
        
        int choice;
        std::cin >> choice;

        std::string patternKey;
        switch(choice) {
            case 1: patternKey = "glider"; break;
            case 2: patternKey = "blinker"; break;
            case 3: patternKey = "block"; break;
            case 4: patternKey = "gosper_glider_gun"; break;
            case 5: patternKey = "r_pentomino"; break;
            case 6: patternKey = "lwss"; break;
            case 7: patternKey = "beehive"; break;
            case 8: patternKey = "pentadecathlon"; break;
            default: patternKey = "glider";
        }

        auto pattern = game.getPattern(patternKey);
        int centerX = game.getWidth()/2;
        int centerY = game.getHeight()/2;
        
        for(auto& pos : pattern) {
            int x = (centerX + pos.x + game.getWidth()) % game.getWidth();
            int y = (centerY + pos.y + game.getHeight()) % game.getHeight();
            if (x < 0) x += game.getWidth();
            if (y < 0) y += game.getHeight();
            field.getCell(x, y).setState(true);
        }
    }
    else if(mode == 2) {
        srand(time(0));
        int numCells = (game.getWidth() * game.getHeight()) / 4;
        std::vector<std::pair<int, int>> positions;

        for (int y = 0; y < game.getHeight(); ++y) {
            for (int x = 0; x < game.getWidth(); ++x) {
                positions.push_back({x, y});
            }
        }

        std::random_shuffle(positions.begin(), positions.end());

        for(int i = 0; i < numCells; ++i) {
            int x = positions[i].first;
            int y = positions[i].second;
            field.getCell(x, y).setState(true);
        }
    } else if(mode == 3) {
        crateMode(field, game.getWidth(), game.getHeight());
    } else {
        std::cout << "Wrong mode. Ending...\n";
        return 1;
    }

    while(true) {
        std::cout << "\033[H";
        system("cls");
        field.printField();
        field.nextGeneration(game);
        usleep(50);
    }

    std::cout << "\033[?25h";
    return 0;
}