#include <stdio.h>
#include <stdlib.h>

struct Point {
    int x; 
    int y; 
};

struct Circle {
    int radius; 
    struct Point center; 
};

int Concentric(struct Circle circle1, struct Circle circle2) {
    return (circle1.center.x == circle2.center.x) && (circle1.center.y == circle2.center.y);
}

int Peresek(struct Circle circle1, struct Circle circle2) {
    int dx = circle1.center.x - circle2.center.x;
    int dy = circle1.center.y - circle2.center.y;
    int dist = dx * dx + dy * dy;
    int radiusSum = circle1.radius + circle2.radius;
    return dist < (radiusSum * radiusSum);
}

int Peresek3(struct Circle circle1, struct Circle circle2, struct Circle circle3) {
    return Peresek(circle1, circle2) && Peresek(circle2, circle3) && Peresek(circle3, circle1);
}

int main() {
    int size = 5;
    int array[5][3] = {{1, 0, 1}, {2, 2, 0}, {2, 2, 2}, {3, 2, -6}, {1, 2, -6}};
    
    int flag1 = 0;
    for(int i = 0; i < size-1; i++)
    {
        for(int j = i + 1; j < size; j++)
        { 
            struct Circle circle1 = {array[i][0], {array[i][1], array[i][2]}};
            struct Circle circle2 = {array[j][0], {array[j][1], array[j][2]}};
            if(Concentric(circle1, circle2))
                flag1++;
        }
    }
    printf("Concentric: %s\n", flag1 > 0 ? "Yes" : "No");

    int flag2 = 0;
    for(int i = 0; i < size; i++)
    {
        for(int j = i+1; j < size-1; j++)
        {
            for(int k = j+1; k < size-2; k++)
            {
                struct Circle circle1 = {array[i][0], {array[i][1], array[i][2]}};
                struct Circle circle2 = {array[j][0], {array[j][1], array[j][2]}};
                struct Circle circle3 = {array[k][0], {array[k][1], array[k][2]}};
                if(Peresek3(circle1, circle2, circle3))
                {
                    flag2++;
                }
            }
        }
    }
    printf("Peresek: %s\n", flag2 > 0 ? "Yes" : "No");

    return 0;
}
