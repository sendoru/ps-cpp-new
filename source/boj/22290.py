from math import gcd

def P1(x1,y1,x2,y2,x3,y3):
    def sub(x1,y1,x2,y2):
        xdiff = abs(x1-x2)
        ydiff = abs(y1-y2)
        return gcd(xdiff,ydiff)

    return sub(x1,y1,x2,y2) + sub(x2,y2,x3,y3) + sub(x3,y3,x1,y1)