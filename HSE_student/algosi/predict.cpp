#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <iomanip>

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
    const bool is_specialized = is_hat_lover || is_book_lover || is_ball_lover;

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
        
        float accept_ratio = is_specialized ? 0.3f : 0.4f;
        accept_ratio *= (1.0f + state.opponent_generosity) / 2.0f;
        accept_ratio *= (1.0f - 0.07f * turn);
        accept_ratio = clamp(accept_ratio, 0.15f, is_specialized ? 0.6f : 0.7f);
        
        if (our_value >= 10 * accept_ratio) {
            return 200;
        }

        if (turn >= 2 && (our_value > 0 || (is_specialized && turn >= 4))) {
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

// Функция симуляции одного боя
std::tuple<int, int, bool, int> simulate_duel(
    int hatCost1, int bookCost1, int ballCost1,
    int hatCost2, int bookCost2, int ballCost2,
    bool player1_starts
) {
    // Сброс состояния
    struct Dummy { ~Dummy() { decide(0, 0, 0, 0, 0, 0, 0); } } dummy;

    int turn = 0;
    int last_offer = -1;
    bool last_was_offer = false;
    bool game_ended = false;
    int player1_score = 0, player2_score = 0;
    int rounds_played = 0;

    while (turn < 6 && !game_ended) {
        rounds_played++;
        const bool is_player1_turn = (player1_starts == (turn % 2 == 0));
        
        if (is_player1_turn) {
            if (last_was_offer) {
                // Игрок1 отвечает на предложение
                int h = last_offer / 100;
                int b = (last_offer / 10) % 10;
                int s = last_offer % 10;
                int response = decide(turn, hatCost1, bookCost1, ballCost1, h, b, s);
                
                if (response == 200) {
                    // Игрок1 принял предложение
                    player1_score = (1 - h) * hatCost1 + (2 - b) * bookCost1 + (3 - s) * ballCost1;
                    player2_score = h * hatCost2 + b * bookCost2 + s * ballCost2;
                    game_ended = true;
                } else {
                    last_was_offer = false;
                }
            } else {
                // Игрок1 делает предложение
                last_offer = decide(turn, hatCost1, bookCost1, ballCost1, 0, 0, 0);
                last_was_offer = true;
            }
        } else {
            if (last_was_offer) {
                // Игрок2 отвечает на предложение
                int h = last_offer / 100;
                int b = (last_offer / 10) % 10;
                int s = last_offer % 10;
                int response = decide(turn, hatCost2, bookCost2, ballCost2, h, b, s);
                
                if (response == 200) {
                    // Игрок2 принял предложение
                    player1_score = h * hatCost1 + b * bookCost1 + s * ballCost1;
                    player2_score = (1 - h) * hatCost2 + (2 - b) * bookCost2 + (3 - s) * ballCost2;
                    game_ended = true;
                } else {
                    last_was_offer = false;
                }
            } else {
                // Игрок2 делает предложение
                last_offer = decide(turn, hatCost2, bookCost2, ballCost2, 0, 0, 0);
                last_was_offer = true;
            }
        }
        
        if (!game_ended) turn++;
    }

    return {player1_score, player2_score, game_ended, rounds_played};
}

int main() {
    // 10 различных комбинаций стоимостей (x, y, z)
    std::vector<std::tuple<std::string, int, int, int>> cost_combinations = {
        {"Сбалансированные", 3, 2, 1},
        {"Любитель шляп", 10, 0, 0},
        {"Любитель книг", 0, 5, 0},
        {"Любитель шариков", 0, 0, 4},
        {"Смешанный тип A", 4, 3, 0},
        {"Смешанный тип B", 2, 4, 0},
        {"Смешанный тип C", 1, 0, 3},
        {"Смешанный тип D", 0, 2, 2},
        {"Смешанный тип E", 5, 1, 1},
        {"Случайные", 2, 3, 1}
    };

    // Статистика
    int total_games = 0;
    int agreements_reached = 0;
    int total_rounds = 0;
    int total_player1_score = 0;
    int total_player2_score = 0;
    int max_player_score = 0;
    int min_player_score = 1000;

    std::cout << "НАЧАЛО ТУРНИРА\n";
    std::cout << "========================================\n";

    // Каждый с каждым (включая себя)
    for (int i = 0; i < cost_combinations.size(); i++) {
        for (int j = 0; j < cost_combinations.size(); j++) {
            for (int start = 0; start < 2; start++) {  // 0 = P1 начинает, 1 = P2 начинает
                auto [name1, h1, b1, s1] = cost_combinations[i];
                auto [name2, h2, b2, s2] = cost_combinations[j];
                bool player1_starts = (start == 0);
                
                auto [score1, score2, ended, rounds] = simulate_duel(
                    h1, b1, s1, h2, b2, s2, player1_starts
                );
                
                total_games++;
                total_rounds += rounds;
                if (ended) agreements_reached++;
                
                total_player1_score += score1;
                total_player2_score += score2;
                
                max_player_score = std::max({max_player_score, score1, score2});
                min_player_score = std::min({min_player_score, score1, score2});
                
                // Выводим детали только для интересных случаев
                if (i == j || !ended || std::abs(score1 - score2) > 5) {
                    std::cout << "Бой #" << total_games << ": " << name1 << " vs " << name2;
                    std::cout << " | Старт: " << (player1_starts ? "P1" : "P2") << "\n";
                    std::cout << "  Раундов: " << rounds << " | ";
                    
                    if (ended) {
                        std::cout << "Соглашение! ";
                        std::cout << "P1: " << score1 << " | P2: " << score2;
                        std::cout << " | Сумма: " << (score1 + score2);
                    } else {
                        std::cout << "Без соглашения";
                    }
                    std::cout << "\n----------------------------------------\n";
                }
            }
        }
    }

    // Итоговая статистика
    std::cout << "\nИТОГИ ТУРНИРА\n";
    std::cout << "========================================\n";
    std::cout << "Всего боев: " << total_games << "\n";
    std::cout << "Достигнуто соглашений: " << agreements_reached << " (" 
              << std::fixed << std::setprecision(1) 
              << (100.0 * agreements_reached / total_games) << "%)\n";
    std::cout << "Среднее количество раундов: " 
              << static_cast<double>(total_rounds) / total_games << "\n";
    std::cout << "Средние очки за бой: P1=" 
              << static_cast<double>(total_player1_score) / total_games
              << " | P2=" << static_cast<double>(total_player2_score) / total_games << "\n";
    std::cout << "Максимальные очки в одном бою: " << max_player_score << "\n";
    std::cout << "Минимальные очки в одном бою: " << min_player_score << "\n";
    std::cout << "Средняя сумма очков за сделку: " 
              << static_cast<double>(total_player1_score + total_player2_score) / agreements_reached << "\n";

    return 0;
}