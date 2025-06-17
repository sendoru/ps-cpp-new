def get_first_syllable(a):
    for i in range(len(a) - 1):
        if a[i] in "aeiou" and not a[i + 1] in "aeiou":
            return a[:i + 1]
    return ""

def main():
    a = input()
    b = input()

    aa = get_first_syllable(a)
    bb = get_first_syllable(b)

    if aa == "" or bb == "":
        print("no such exercise")
    else:
        print(aa + bb)

if __name__ == "__main__":
    main()
