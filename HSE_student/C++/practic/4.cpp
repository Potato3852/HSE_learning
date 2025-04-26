#include <iostream>
#include <string>
#include <vector>
#include<cmath>
int main() 
{
	int n;
	std::cin >> n;
	std::vector<std::pair<int, int>> a;
	a.push_back({0,0});
	for(int i = 0; i < n; ++i) {
		int x,y;
		std::cin >> x >> y;
		a.push_back({x,y});

	}
	std::vector<std::pair<int, int>> dif;
	
	for(int i = 1; i < n; ++i){
		if(a[i].second > a[i-1].second && a[i].second > a[i+1].second) {
			dif.push_back({a[i].first, a[i].second});
           // std::cout << a[i].first << ' ' << a[i].second << std::endl;
        }
    }
	double result = 0;
	for(int i = 1; i < a.size(); ++i)
	{
		result += sqrt((a[i].second - a[i-1].second) * (a[i].second - a[i-1].second) + (a[i].first - a[i-1].first) * (a[i].first - a[i-1].first));
	}
	for(int i = 1; i < dif.size(); ++i)
	{
		result += sqrt((dif[i].second - dif[i-1].second) * (dif[i].second - dif[i-1].second) + (dif[i].first - dif[i-1].first) * (dif[i].first - dif[i-1].first));
	}
	printf("%.9lf", result);
	return 0;
}