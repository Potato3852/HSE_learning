#include <vector>
#include <algorithm>

__declspec(dllexport) int __cdecl decide(int turn, int hatCost, int bookCost, int ballCost, int hatCount, int bookCount, int ballCount)
{
    const int total_value = hatCount * hatCost + bookCount * bookCost + ballCount * ballCost;
    const int max_hats = 1;
    const int max_books = 2;
    const int max_balls = 3;
    
    // Генерация всех возможных вариантов распределения
    std::vector<int> options;
    for (int h = 0; h <= max_hats; h++) {
        for (int b = 0; b <= max_books; b++) {
            for (int s = 0; s <= max_balls; s++) {
                if (h == 0 && b == 0 && s == 0) continue;   // пустое предложение
                if (h == max_hats && b == max_books && s == max_balls) continue; // все предметы
                options.push_back(h * 100 + b * 10 + s);
            }
        }
    }

    // Стратегия для ответа на предложения соперника (четные ходы)
    if (turn % 2 == 0) {
        // Агрессивное принятие в первом раунде
        if (turn == 0 && total_value >= 7) return 200;
        
        // Умеренное принятие в середине игры
        if (turn == 2 && total_value >= 5) return 200;
        
        // Принятие любого положительного предложения в последнем раунде
        if (turn == 4 && total_value > 0) return 200;
    }

    // Стратегия для наших предложений (нечетные ходы)
    struct Option {
        int code;
        int value;
    };
    
    std::vector<Option> valid_options;
    for (int option : options) {
        int h = option / 100;
        int b = (option / 10) % 10;
        int s = option % 10;
        int value = h * hatCost + b * bookCost + s * ballCost;
        valid_options.push_back({option, value});
    }
    
    // Сортировка вариантов по выгодности
    std::sort(valid_options.begin(), valid_options.end(), [](const Option& a, const Option& b) {
        return a.value > b.value;
    });

    // Выбор стратегии в зависимости от номера хода
    if (turn == 1) {
        // Первое предложение: максимально агрессивное
        for (const auto& opt : valid_options) {
            if (opt.value >= 7) return opt.code;  // Требуем максимум
        }
        return valid_options[0].code;  // Лучший доступный вариант
    }
    else if (turn == 3) {
        // Второе предложение: умеренное
        for (const auto& opt : valid_options) {
            if (opt.value >= 5) return opt.code;  // Умеренные требования
        }
        return valid_options[0].code;
    }
    else if (turn == 5) {
        // Последнее предложение: консервативное
        for (const auto& opt : valid_options) {
            if (opt.value >= 4) return opt.code;  // Минимально приемлемое
        }
        // В последнем ходу соглашаемся даже на неидеальный вариант
        return valid_options.empty() ? 132 : valid_options[0].code;
    }

    // Страховка на случай ошибки
    return 123;  // 1 шарик, 2 книги, 3 шапки
}