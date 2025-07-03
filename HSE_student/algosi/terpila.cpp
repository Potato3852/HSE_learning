#include <vector>
#include <algorithm>

__declspec(dllexport) int __cdecl decide(int turn, int hatCost, int bookCost, int ballCost, int hatCount, int bookCount, int ballCount) {

    const int total_value = hatCount * hatCost + bookCount * bookCost + ballCount * ballCost;
    const int total_items = 10;
    
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

    bool is_our_turn = (turn % 2 == 1);

    if(is_our_turn) {
        struct Option {
            int code;
            int our_value;
            int their_value;
        };
        std::vector<Option> valid_options;
        
        for(int option : options) {
            int h = option / 100;
            int b = (option / 10) % 10;
            int s = option % 10;
            int our_value = h * hatCost + b * bookCost + s * ballCost;
            int their_value = total_items - our_value;
            valid_options.push_back({option, our_value, their_value});
        }
        
        std::sort(valid_options.begin(), valid_options.end(), 
            [](const Option& a, const Option& b) {
                return a.our_value > b.our_value;
            });

        if(turn == 1) {
            for(const auto& opt : valid_options) {
                if(opt.our_value >= 5 && opt.their_value >= 3) {
                    return opt.code;
                }
            }
        } 
        else if(turn == 3) {
            for(const auto& opt : valid_options) {
                if(opt.our_value >= 4 && opt.their_value >= 2) {
                    return opt.code;
                }
            }
        }
        else if(turn == 5) {
            for(const auto& opt : valid_options) {
                if(opt.their_value == 1) {
                    return opt.code;
                }
            }
        }
        
        return valid_options.empty() ? 123 : valid_options[0].code;
    } else {
        float accept_ratio;
        if(turn == 0) 
            accept_ratio = 0.45f;
        else if(turn == 2) 
            accept_ratio = 0.35f;
        else
            accept_ratio = 0.25f;

        if(total_value >= total_items * accept_ratio) {
            return 200;
        }
        if(turn == 4 && total_value > 0) {
            return 200;
        }
        
        return 123;
    }
}