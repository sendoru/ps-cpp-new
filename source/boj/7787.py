# import sys
# sys.setrecursionlimit(10**7)

# cache={}
# def f(a,b):
#     if a==b:
#         return 0
#     if a==0 or b==0:
#         return 1
#     if a==1 or b==1:
#         return (a+b)%2
#     if a>b:
#         a,b=b,a
#     if a==2:
#         return [3,1,0,2][b%4]
#     if a==3:
#         return [2,0][b%2]
#     if (a,b)in cache:
#         return cache[(a,b)]
#     s = set()
#     i = 1
#     while i*i <= b:
#         if b%i == 0:
#             if i <= a:
#                 s.add(f(a - i, b))
#             if b//i <= a:
#                 s.add(f(a - b//i, b))
#         i += 1
#     i = 1
#     while i*i <= a:
#         if a%i == 0:
#             if i <= b:
#                 s.add(f(a, b - i))
#             if a//i <= b:
#                 s.add(f(a, b - a//i))
#         i += 1
#     r = 0
#     while r in s:
#         r += 1
#     cache[(a,b)] = r
#     return r

# a,b=map(int,input().split())
# print(f"{'BA'[f(a,b)>0]} player wins")

a,b=map(int,input().split())
p,q=0,0
while a%2==0:
    a//=2
    p+=1
while b%2==0:
    b//=2
    q+=1
print(f"{'AB'[p==q]} player wins")