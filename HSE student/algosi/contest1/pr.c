#include <stdio.h> 
 
int f(int x, int y) 
{ 
 int otv; 
 ((x * y) < 256) ? (otv = (x * y)) : (otv = 255); 
 return otv; 
} 
 
int main() 
{ 
 unsigned int a, b; 
 scanf_s("%d %d", &a, &b); 
  
 const unsigned int MASK1 = 0b00000000000000000000000011111111; 
 const unsigned int MASK2 = 0b00000000000000001111111100000000; 
 const unsigned int MASK3 = 0b00000000111111110000000000000000; 
 const unsigned int MASK4 = 0b11111111000000000000000000000000; 
 int sm, t1; 
 sm = f((a & MASK1), (b & MASK1)) + f((a & MASK2), (b & MASK2)) + f((a & MASK3), (b & MASK3)) + f((a & MASK4), (b & MASK4)); 
 
 printf("%d\n", sm); 
 
 return 0; 
}