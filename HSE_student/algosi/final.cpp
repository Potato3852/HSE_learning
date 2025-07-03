#include <vector>
#include <algorithm>
#include <tuple>
#include <utility>

template<typename T>
T clamp(T value, T min_val, T max_val) {
    if (value < min_val) return min_val;
    if (value > max_val) return max_val;
    return value;
}

__declspec(dllexport) int __cdecl decide(int turn, int hatCost, int bookCost, int ballCost, 
                                        int hatCount, int bookCount, int ballCount) {
    static struct {
        std::vector<int> opponent_offers;
        float opponent_generosity = 0.5f;
        bool we_started = false;
    } state;

    const bool is_hat_lover = (hatCost >= bookCost * 2) && (hatCost >= ballCost * 2);
    const bool is_book_lover = (bookCost >= hatCost * 2) && (bookCost >= ballCost * 2);
    const bool is_ball_lover = (ballCost >= hatCost * 2) && (ballCost >= bookCost * 2);
    const bool Special = is_hat_lover || is_book_lover || is_ball_lover;

    if (turn == 0) {
        state.we_started = (hatCount == 0 && bookCount == 0 && ballCount == 0);
        state.opponent_offers.clear();
        state.opponent_generosity = 0.5f;
    }

    auto is_valid_offer = [](int h, int b, int s) {
        return h >= 0 && h <= 1 && b >= 0 && b <= 2 && s >= 0 && s <= 3;
    };

    const bool is_our_turn = (state.we_started && turn % 2 == 0) || 
                            (!state.we_started && turn % 2 == 1);

    if (!is_our_turn && is_valid_offer(hatCount, bookCount, ballCount)) {
        state.opponent_offers.push_back(hatCount * 100 + bookCount * 10 + ballCount);
        
        if (state.opponent_offers.size() > 1) {
            int last_offer = state.opponent_offers.back();
            int prev_offer = state.opponent_offers[state.opponent_offers.size()-2];
    
            int last_value = (last_offer/100)*hatCost + ((last_offer/10)%10)*bookCost + (last_offer%10)*ballCost;
            int prev_value = (prev_offer/100)*hatCost + ((prev_offer/10)%10)*bookCost + (prev_offer%10)*ballCost;

            state.opponent_generosity = 0.9f * state.opponent_generosity + 
                                      0.1f * (last_value > prev_value ? 1.0f : 0.0f);
            state.opponent_generosity = clamp(state.opponent_generosity, 0.0f, 1.0f);
        }
        
        const int our_value = hatCount * hatCost + bookCount * bookCost + ballCount * ballCost;
        
        float accept_rat = Special ? 0.3f : 0.4f;
        accept_rat *= (1.0f + state.opponent_generosity) / 2.0f;
        accept_rat *= (1.0f - 0.07f * turn);
        accept_rat = clamp(accept_rat, 0.15f, Special ? 0.6f : 0.7f);
        
        if (our_value >= 10 * accept_rat) {
            return 200;
        }

        if (turn >= 2 && (our_value > 0 || (Special && turn >= 4))) {
            return 200;
        }
        
        return 0;
    }

    if (is_our_turn) {
        if (is_hat_lover) {
            if (turn == 0 || turn == 1) return 100;
            
            const int books_to_offer = (turn % 2 == 0) ? 0 : 2;
            const int balls_to_offer = (turn % 3 == 0) ? 0 : 3;
            return 100 + books_to_offer * 10 + balls_to_offer;
        }
        
        if (is_book_lover) {
            if (turn == 0 || turn == 1) return 20; 
            
            const int hats_to_offer = (turn % 2 == 0) ? 0 : 1;
            const int balls_to_offer = (turn % 3 == 0) ? 0 : 3;
            return hats_to_offer * 100 + 20 + balls_to_offer;
        }
        
        if (is_ball_lover) {
            if (turn == 0 || turn == 1) return 3;
            
            const int hats_to_offer = (turn % 2 == 0) ? 0 : 1;
            const int books_to_offer = (turn % 3 == 0) ? 0 : 2;
            return hats_to_offer * 100 + books_to_offer * 10 + 3;
        }

        if (turn == 0 || turn == 1) {
            return 111;
        }

        if (!state.opponent_offers.empty()) {
            return state.opponent_offers.back();
        }

        const int hats[] = {0, 1};
        const int books[] = {0, 1, 2};
        const int balls[] = {0, 1, 2, 3};
        
        int best_offer = 111;
        int best_value = -1;
        
        for (int h : hats) {
            for (int b : books) {
                for (int s : balls) {
                    if ((h == 0 && b == 0 && s == 0) || (h == 1 && b == 2 && s == 3)) continue;
                    
                    const int our_val = h * hatCost + b * bookCost + s * ballCost;
                    
                    if (our_val > best_value) {
                        best_value = our_val;
                        best_offer = h * 100 + b * 10 + s;
                    }
                }
            }
        }
        
        return best_offer;
    }
    
    return 111;
}