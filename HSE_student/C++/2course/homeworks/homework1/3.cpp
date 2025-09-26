#include <iostream>
#include <string>
#include <vector>

//Предворительное объявление
class SecurityClearance;
class ConfidentialData;
class AccessLogger;
void attemptAccess(SecurityClearance&, ConfidentialData&, AccessLogger&);

class SecurityClearance{
private:
    int access_level;

public:
    SecurityClearance(int al) : access_level(al) {}
    friend void attemptAccess(SecurityClearance&, ConfidentialData&, AccessLogger&);
};

class ConfidentialData{
private:
    std::string secret;

public:
    ConfidentialData(std::string s) : secret(s) {}
    friend void attemptAccess(SecurityClearance&, ConfidentialData&, AccessLogger&);
};

class AccessLogger{
private:
    int number;
    std::vector<std::pair<int, std::string>> log;
public:
    AccessLogger() {number = 0;}
    friend void attemptAccess(SecurityClearance&, ConfidentialData&, AccessLogger&);
    std::vector<std::pair<int, std::string>> getLogs() const {
        return log;
    }
};

void attemptAccess(SecurityClearance& sc, ConfidentialData& cd, AccessLogger& al){
    int level = sc.access_level;

    if(level >= 3){
        std::cout << "Access to get data: " << cd.secret << std::endl;
        al.number++;
        al.log.push_back({al.number, "level " + std::to_string(level) + " Successful"});
    } else {
        al.number++;
        al.log.push_back({al.number, "level " + std::to_string(level) + " Unsuccessful"});
    }
}

int main(){
    // Минимальная проверка
    SecurityClearance high(4);       // Высокий уровень доступа
    SecurityClearance low(2);        // Низкий уровень доступа
    ConfidentialData secret("Top Secret Information");
    AccessLogger logger;
    
    std::cout << "=== Testing Access Control ===" << std::endl;
    
    // Тестируем высокий уровень
    attemptAccess(high, secret, logger);
    
    // Тестируем низкий уровень  
    attemptAccess(low, secret, logger);
    
    // Проверяем логи через getLogs()
    std::cout << "\n=== Checking Logs ===" << std::endl;
    auto logs = logger.getLogs();
    std::cout << "Total log entries: " << logs.size() << std::endl;
    
    for(const auto& entry : logs){
        std::cout << "ID: " << entry.first << " | " << entry.second << std::endl;
    }
    
    return 0;
}