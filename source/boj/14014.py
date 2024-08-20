of_words = ["of", "to", "into", "onto",
            "above", "below", "from", "by", "is", "at"]


def to_lower(s: str) -> str:
    ret = []
    for c in s:
        if ord(c) >= ord('A') and ord(c) <= ord('Z'):
            ret.append(chr(ord(c) - ord('A') + ord('a')))
        else:
            ret.append(c)

    return ''.join(ret)


def remove_punc(s: str) -> str:
    ret = []
    for c in s:
        if ord(c) >= ord('a') and ord(c) <= ord('z'):
            ret.append(c)
    return ''.join(ret)


def thanos_vowel(s: str) -> str:
    vowel_cnt = 0
    for c in s:
        if c in ('a', 'e', 'i', 'o', 'u'):
            vowel_cnt += 1
    vowel_cnt //= 2

    ret = []
    for c in s:
        if c in ('a', 'e', 'i', 'o', 'u'):
            if vowel_cnt > 0:
                vowel_cnt -= 1
            else:
                ret.append(c)
        else:
            ret.append(c)

    return ''.join(ret)


def convert_world(s: str):
    s = to_lower(s)
    if s in of_words:
        return "of"
    s = remove_punc(s)

    return thanos_vowel(s)


def main():
    n = int(input())
    words = []
    for _ in range(n):
        words.extend(input().split())

    words = list(map(convert_world, words))
    words = [word for word in words if word != '']
    chr_cnt = 0
    for i, word in enumerate(words):
        chr_cnt += len(word)
        if chr_cnt > 20:
            print(word)
            chr_cnt = 0
        else:
            if i == len(words) - 1:
                print(word)
            else:
                print(word, end=' ')


if __name__ == "__main__":
    main()
