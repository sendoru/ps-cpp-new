import random as r

arr_old = [[i + 1, i + 3, i + 2, i + 4] for i in range(0, 100000, 4)]
# spread
arr = []
for i in range(0, 100000//4):
    arr.append([arr_old[i][0], arr_old[i][1]])
    arr.append([arr_old[i][2], arr_old[i][3]])

r.shuffle(arr)
arr = [' '.join(map(str, i)) for i in arr]
arr = '\n'.join(arr)
with open('test.txt', 'w') as f:
    f.write("100000 50000\n")
    f.write(arr)
