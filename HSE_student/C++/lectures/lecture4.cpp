#include <iostream>
#include "rational.cpp"

//класс - пользовательский тип данных, который содержит поля(данные) и методы(функции для работы с полями).
//принципы ООП: инкапсуляция(разделение класса на интерфейс и реализацию), наследование(создание новых классов из уже имеющихся), 
//              полиморфизм(позволяет разным сущностям выполнять одни и те же действия).



int main() {

    Rational r1;
    Rational r2(1, 2);
    Rational r3(5, 10);
    Rational r4(-9, -14);
    Rational r5(3, -6);

    r1.printRational();
    r2.printRational();
    r3.printRational();
    r4.printRational();
    r5.printRational();

}