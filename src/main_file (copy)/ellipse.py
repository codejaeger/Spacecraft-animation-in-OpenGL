import math

a = 5.0
b = 4.5

print(81)
theta = 0.0

while(theta<=2*math.pi):
    print(a*math.cos(theta),end=' ')
    print(0,end=' ')
    print(b*math.sin(theta))
    theta += 2*math.pi/80