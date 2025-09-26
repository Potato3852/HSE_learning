#include <iostream>
#include <cstring>

class String{
private:
    char* line;
    int size;
public:
    String(const char* temp=""){
        size = strlen(temp);
        line = new char[size+1];
        strcpy(line, temp);
    }

    String(const String& temp){
        size = temp.size;
        line = new char[size+1];
        strcpy(line, temp.line);
    }

    ~String(){
        delete[] line;
    }

    void changeValue(const char* temp){
        delete[] line;
        line = new char[strlen(temp)+1];
        strcpy(line, temp);
    }

    char* getValue(){
        return line;
    }

};

int main() {
    String s1("Hello");
    String s2 = s1;

    std::cout << s1.getValue() << std::endl;
    s2.changeValue("Privet");
    std::cout << s2.getValue() << std::endl;
}