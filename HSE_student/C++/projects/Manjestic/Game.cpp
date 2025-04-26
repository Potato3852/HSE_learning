#include "Game.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void Game::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error to open file " << filename << std::endl;
        return;
    }

    json config;
    file >> config;

    width = config["width"];
    height = config["height"];
    birthLimit = config["birthLimit"];
    deathLimit = config["deathLimit"];

    for(auto& [name, positions]: config["patterns"].items()) {
        std::vector<CellPosition> pattern;
        for (auto& pos : positions) {
            pattern.push_back({pos["x"], pos["y"]});
        }
        patterns[name] = pattern;
    }

    std::cout << "Settings from " << filename << " accepted" << std::endl;
}

std::vector<CellPosition> Game::getPattern(const std::string& name) const {
    auto it = patterns.find(name);
    if(it != patterns.end()) {
        return it->second;
    }
    
    return {};
}