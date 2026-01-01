input()
a=map(lambda x:(int(x)-1)//2+int(x)%2,input().split())
b=0
for i in a:b^=i
print(['cubelover','koosaga'][b>0])