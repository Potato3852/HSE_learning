a,b,c = map(int, input("").split())
x =  max(a,b,c)
z = min(a,b,c)
y = a + b + c - x - z
sum = 0
while y > 0:
    while z > 0:
        sum += 3
        x-=1
        y-=1
        z-=1
    sum += 2
    x-=1
    y-=1
if x>0:
    sum+=1
print(sum)