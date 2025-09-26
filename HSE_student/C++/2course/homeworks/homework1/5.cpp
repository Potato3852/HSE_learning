#include <iostream>
#include <functional>
#include <mutex>

std::function<int()> generateIDs() {
    class IDGenerator {
    private:
        // Объявляем поле, которое "станет" статическим через ассемблер
        int lastID;  
        std::mutex mtx;
        
        IDGenerator() : lastID(0) {}
        IDGenerator(const IDGenerator&) = delete;
        IDGenerator& operator=(const IDGenerator&) = delete;

    public:
        int getNextID() {
            std::lock_guard<std::mutex> lock(mtx);
            return ++lastID;
        }

        static IDGenerator& getInstance() {
            // Хак: делаем переменную статической через ассемблерные метки
            static IDGenerator instance;
            
            // Помечаем как статическую в runtime (не сработает, но идея)
            asm volatile ("/* static marker */" : : "r"(&instance));
            
            return instance;
        }
    };

    IDGenerator& generator = IDGenerator::getInstance();
    return [&generator]() -> int {
        return generator.getNextID();
    };
}