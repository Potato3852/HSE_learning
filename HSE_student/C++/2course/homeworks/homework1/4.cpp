#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>

class BankSecuritySystem{
private:
    class SecurityLogger{
    private:
        std::vector<std::string> logs;

        std::string getTime(){
            time_t now = time(0);
            std::string time = ctime(&now);
            return time;
        }

    public:
        void addLog(std::string text) {
            std::string temp = text + " - " + getTime();
            logs.push_back(temp);
        }

        void getLogs() {
            std::cout << "Current LOGS:" << std::endl;
            int size = logs.size();
            for(int i = 0; i < size; ++i){
                std::cout << i+1 << " " << logs[i] << std::endl;
            }
        }

        int getLogCount() { return logs.size(); }
    };

    class TransactionMonitor{
    private:
        float threshold;
        SecurityLogger& logs;

        bool getStatus(float attempt){
            if(attempt <= threshold) { return true; }
            return false;
        }

    public:
        TransactionMonitor(float threshold, SecurityLogger& logs) : threshold(threshold), logs(logs) {}
        friend class SecurityLogger;

        void logging(float a){
            ++number_of_transactions;
            if(getStatus(a)){
                std::string result = "Good transaction: " + std::to_string(a);
                logs.addLog(result);
            } else {
                std::string result = "Bad transaction: " + std::to_string(a);
                logs.addLog(result);
            }
        }

        void changeThreshold(int a) { threshold = a; std::cout << "new threshold: " << a << std::endl; }
        float getThreshold() const { return threshold; } 
    };

    SecurityLogger logger;
    TransactionMonitor monitor;
    static int number_of_transactions;

public:
    BankSecuritySystem(int treshold = 0) : monitor(treshold, logger) {}

    void report() {
        std::cout << "total transactions: " + std::to_string(number_of_transactions) << std::endl;
        std::cout << "current treshold: " << monitor.getThreshold() << std::endl;
        std::cout << "+++Logger_INFO+++" << std::endl;
        logger.getLogs();
    }

    void transaction(float a) {
        monitor.logging(a);
    }

    friend void fr_void(BankSecuritySystem& bank);
};

void fr_void(BankSecuritySystem& bank){
    std::cout << "Total transactions: " << bank.number_of_transactions << std::endl;
    std::cout << "Threshould: " << bank.monitor.getThreshold() << std::endl;
    std::cout << "Total logs: " << bank.logger.getLogCount() << std::endl;

    std::cout << "Testing..." << std::endl;
    bank.monitor.logging(1);
    bank.monitor.logging(10000000);

    bank.monitor.changeThreshold(1000000);

    bank.monitor.logging(999999);
    bank.monitor.logging(100000000);

    std::cout << "test complited!" << std::endl;
}

int BankSecuritySystem::number_of_transactions = 0;

int main(){
}