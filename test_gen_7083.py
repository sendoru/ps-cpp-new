import random as r

arr_old = [[i + 1, i + 3, i + 2, i + 4] for i in range(4, 100000 - 4, 4)]
# spread
arr = []
for i in range(0, 100000//4 - 2):
    arr.append([arr_old[i][0], arr_old[i][1]])
    arr.append([arr_old[i][2], arr_old[i][3]])

# shuffle
r.shuffle(arr)

arr.append([1, 100000 - 3])
arr.append([2, 100000 - 2])
arr.append([3, 100000 - 1])
arr.append([4, 100000])

# shuffle last 10000
temp = arr[-10000:]
r.shuffle(temp)
arr[-10000:] = temp

for i in range(0, 50000, 50):
    if i + 100 < 50000:
        tmp = arr[i:i+100]
        r.shuffle(tmp)
        arr[i:i+100] = tmp
arr = [' '.join(map(str, i)) for i in arr]
arr = '\n'.join(arr)

print("100000\n50000")
print(arr)
