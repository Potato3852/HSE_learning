#include <iostream>
#include <type_traits>
using namespace std;
#include <typeinfo>

//--------------------------------
template<typename T>
struct S{
    using x = int;
};

template<>
struct S<int>{
    static int x;
};

int a;

template<typename T>
void f(){
    typename S<T>::x* a;
};

//--------------------------------

template<typename T, typename U>
struct IsSame{
    constexpr static bool value = false;
};

template<typename T>
struct IsSame<T, T>{
    constexpr static bool value = true;
};

template<typename T, typename U>
constexpr static bool IsSameV = IsSame<T, U>::value;

//-------------------------------

template<typename T>
struct RemoveConst{
    using type = T;
};

template<typename T>
struct RemoveConst<const T>{
    using type = T;
};

template<typename T>
using RemoveConstT = typename RemoveConst<T>::type;

//-------------------------------

template<typename T>
struct RemoveReference{
    using type = T;
};

template<typename T>
struct RemoveReference<T&>{
    using type = T;
};

template<typename T>
using RemoveReferenceT = typename RemoveReference<T>::type;

//-------------------------------

template<bool B, typename T, typename U>
struct Conditional{
    using type = T;
};

template<typename T, typename U>
struct Conditional<false, T, U>{
    using type = U;
};

template<bool B, typename T, typename U>
using ConditionalT = typename Conditional<B, T, U>::type;

//-------------------------------

void print(){}

template<typename Head, typename... Tail>
void print(const Head& head, const Tail&... tail){
    cout << head << endl;
    print(tail...);
}

//-------------------------------

template<typename First, typename Second, typename... Tail>
struct are_same{
    constexpr static bool value = is_same<First, Second>::value && are_same<Second, Tail...>::value;
};

template<typename T, typename U>
struct are_same<T, U>{
    constexpr static bool value = is_same<T, U>::value;
};

template<typename First, typename Second, typename... Tail>
constexpr static bool are_same_v = are_same<First, Second, Tail...>::value;

int main(){
    
    cout << are_same<int, int, int>::value << endl;
    cout << are_same<int, double, int>::value << endl;
    cout << are_same<char, int, int>::value << endl;

}

//Зависимые имена
//Метафункция
//Шаблоны с переменным количеством аргументов - variatic template
//
//Каждое имя переменной и типа должно быть строго определено на этапе компиляции
//Либо имя переменной либо тип данных
//