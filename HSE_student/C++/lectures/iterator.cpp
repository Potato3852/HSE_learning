#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

template<typename Iterator>
void Advance(Iterator& it, int n) {
    if constexpr (is_same_v<typename iterator_traits<Iterator>::iterator_category, random_access_iterator_tag>)
        it += n;
    else
        for(int i = 0; i < n; ++i)
            ++it;
}

template<typename Container>
class Inserter{
    Container& container;
public:
    Inserter(Container& container) : container(container){}

    Inserter& operator*(){
        return *this;
    }

    Inserter& operator++(){
        return *this;
    }

    typename Container::value_type operator=(typename Container::value_type& value){
        container.push_back(value);
        return container.back();
    }

};

int main(){

    vector<int> v = {1, 2, 3, 4, 5};
    vector<int> v1 = {10, 20, 30};
    
    vector<int>::iterator ptr = v.begin();
    Advance(ptr, 3);
    copy(v1.begin(), v1.end(), Inserter<vector<int>>(v));
    for(auto it : v){
        cout << it << ' ';
    }
}

//InputIterator, OutputIterator - на вершине всех итераторов. используется в качестве входного параметра во многих функциях. *it it++ ==
//ForwardIterator - те же операции, что и у InputIterator. forward_list, unordered_map, unordered_set.
//BidirectionalIterator - те же операции и it--. list, set, map
//RandowAccessIterator - < > <= >= it+-=n и все предыдущие операции. deque
//ContiguosIterator - все, что было + &(*it)+1. vector