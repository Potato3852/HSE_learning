#include <iostream>
#include <mutex>
#include <functional>

std::function<int()> generateIDS() {
    class IDGenerator;
    static IDGenerator* orig;
    static std::mutex mtx;

    class IDGenerator{
    private:
        IDGenerator() {}
        IDGenerator(const IDGenerator&) = delete;
        IDGenerator& operator=(const IDGenerator&) = delete;
        ~IDGenerator() {};
    public:
        static int& getLastID(){
            static int value = 0;
            return value;
        }

        int getNextID(){
            std::lock_guard<std::mutex> lock(mtx);
            return ++getLastID();
        }

        static IDGenerator* create(){
            if(orig == nullptr){
                orig = new IDGenerator();
            }
            return orig;
        }
    };

    IDGenerator* generator = IDGenerator::create();
    return [generator]() -> int{
        return generator->getNextID();
    };
}

int main(){
    auto gen = generateIDS();
    std::cout << gen() << std::endl;
    std::cout << gen() << std::endl;
    
    return 0;
}