#include <vector>

__declspec(dllexport) int __cdecl decide(int turn, int hatCost, int bookCost, int ballCost, int hatCount, int bookCount, int ballCount)
{
    int total_value = hatCount * hatCost + bookCount * bookCost + ballCount * ballCost;
    
    const int max_hats = 1;
    const int max_books = 2;
    const int max_balls = 3;
    std::vector<int> options;

    for(int h = 0; h <= max_hats; h++) {
        for(int b = 0; b <= max_books; b++) {
            for(int s = 0; s <= max_balls; s++) {
                if((h == 0 && b == 0 && s == 0) || (h == 1 && b == 2 && s == 3)) continue;
                options.push_back(h * 100 + b * 10 + s);
            }
        }
    }

    if(turn % 2 == 0) {
        if(turn == 0 && total_value >= 7) return 200;
        if(turn == 2 && total_value >= 5) return 200;
        if(turn == 4 && total_value > 0) return 200;
    }
    
    if(turn != 5) {
        for(int option : options) {
            int h = option / 100;
            int b = (option / 10) % 10;
            int s = option % 10;
            int value = h * hatCost + b * bookCost + s * ballCost;
            
            if(value >= 6) {
                return option;
            }
        }

        for(int option : options) {
            int h = option / 100;
            int b = (option / 10) % 10;
            int s = option % 10;
            int value = h * hatCost + b * bookCost + s * ballCost;
            
            if(value >= 4) {
                return option;
            }
        }
    }

    int best_option = 0;
    int best_value = 0;
    for(int option : options) {
        int h = option / 100;
        int b = (option / 10) % 10;
        int s = option % 10;
        int value = h * hatCost + b * bookCost + s * ballCost;
        
        if(value > best_value) {
            best_value = value;
            best_option = option;
        }
    }
    
    return best_option;
}