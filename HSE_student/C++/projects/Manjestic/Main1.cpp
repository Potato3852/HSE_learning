#include "Game.hpp"
#include "Field.hpp"
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <sstream>

void printHelp() {
    std::cout << "CrateMode Commands:\n"
              << "X Y - Add cell at position\n"
              << "clear - Clear all cells\n"
              << "done - Start simulation\n"
              << "help - Show this help\n"
              << "exit - Quit program\n\n";
}

void crateMode(Field& field, int width, int height) {
    std::string input;
    int x, y;
    
    printHelp();
    
    while(true) {
        std::cout << "CrateMode> ";
        std::getline(std::cin, input);
        
        if(input == "done") break;
        if(input == "exit") std::exit(0);
        if(input == "help") {
            printHelp();
            continue;
        }
        if(input == "clear") {
            field = Field(width, height);
            std::cout << "Field cleared!";
            continue;
        }
        
        std::istringstream iss(input);
        if(iss >> x >> y) {
            if(x >= 0 && x < width && y >= 0 && y < height) {
                field.getCell(x, y).setState(true);
                std::cout << "Cell added at (" << x << ", " << y << ")\n";
            } else {
                std::cout << "Invalid coordinates! "
                          << "Range: [0-" << width-1 << "] [0-" << height-1 << "\n";
            }
        } else {
            std::cout << "Invalid command!\n";
        }
    }
}

int main() {
    Game game;
    game.loadFromFile("world.json");

    Field field(game.getWidth(), game.getHeight());

    std::cout << "Available modes\n";
    std::cout << "1. Solo mode (choose a pattern)\n";
    std::cout << "2. Anarchy mode (random cells)\n";
    std::cout << "3. Create mode (create cells)\n";
    std::cout << "Your choice: ";

    int mode;
    std::cin >> mode;

    if (mode == 1) {
        std::cout << "\nAvailable patterns:\n";
        std::cout << "1. Glider\n";
        std::cout << "2. Blinker\n";
        std::cout << "3. Block\n";
        std::cout << "4. Gosper Glider Gun\n";
        std::cout << "5. R-pentomino\n";
        std::cout << "6. Beehive\n";
        std::cout << "7. Lightweight Spaceship\n";
        std::cout << "8. Pentadecathlon\n";
        std::cout << "Enter your choice (1-8): ";

        int choice;
        std::cin >> choice;

        std::vector<CellPosition> pattern;
        switch (choice) {
            case 1:
                pattern = game.getPattern("glider");
                break;
            case 2:
                pattern = game.getPattern("blinker");
                break;
            case 3:
                pattern = game.getPattern("block");
                break;
            case 4:
                pattern = game.getPattern("gosper_glider_gun");
                break;
            case 5:
                pattern = game.getPattern("r_pentomino");
                break;
            case 6:
                pattern = game.getPattern("beehive");
                break;
            case 7:
                pattern = game.getPattern("lwss");
                break;
            case 8:
                pattern = game.getPattern("pentadecathlon");
                break;
            default:
                std::cout << "Invalid choice. Using Glider as default.\n";
                pattern = game.getPattern("glider");
                break;
        }
        int centerX = game.getWidth() / 2;
        int centerY = game.getHeight() / 2;
        for (const auto& pos : pattern) {
            int x = (centerX + pos.x) % game.getWidth();
            int y = (centerY + pos.y) % game.getHeight();
            if (x < 0) x += game.getWidth();
            if (y < 0) y += game.getHeight();
            field.getCell(x, y).setState(true);
        }
    } else if(mode == 2) {
        srand(time(0));
        int numCells = (game.getWidth() * game.getHeight()) / 4;
        std::vector<std::pair<int, int>> positions;

        for(int y = 0; y < game.getHeight(); ++y) {
            for(int x = 0; x < game.getWidth(); ++x) {
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
        system("cls");
        field.printField();
        field.nextGeneration(game);
        usleep(200000);
    }

    return 0;
}