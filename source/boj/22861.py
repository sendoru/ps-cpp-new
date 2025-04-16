class FileTree:
    def __init__(self):
        self.tree = {"main": set()}
        self.subfile_counts = {}
        self.unique_subfiles = {}

    def add_component(self, parent, child, is_dir):
        if parent not in self.tree:
            self.tree[parent] = set()
        self.tree[parent].add((child, is_dir))
        if is_dir and child not in self.tree:
            self.tree[child] = set()

    def get_dir_contents(self, dir_path):
        dir_path = dir_path.rstrip('/').split('/')
        return self.tree.get(dir_path[-1], None)

    def move_dir_content(self, src, dst):
        src = src.rstrip('/').split('/')
        dst = dst.rstrip('/').split('/')

        for item in self.tree[src[-1]]:
            self.tree[dst[-1]].add(item)
        del self.tree[src[-1]]
        self.tree[src[-2]].remove((src[-1], True))

    def get_subfile_count(self, dir_path):
        dir_path = dir_path.rstrip('/').split('/')[-1]
        if dir_path not in self.subfile_counts:
            self.subfile_counts[dir_path] = 0
            for item in self.tree[dir_path]:
                if not item[1]:
                    self.subfile_counts[dir_path] += 1
                else:
                    self.subfile_counts[dir_path] += self.get_subfile_count(
                        item[0])
        return self.subfile_counts[dir_path]

    def get_unique_subfiles(self, dir_path):
        dir_path = dir_path.rstrip('/').split('/')[-1]
        if dir_path not in self.unique_subfiles:
            self.unique_subfiles[dir_path] = set()
            for item in self.tree[dir_path]:
                if not item[1]:
                    self.unique_subfiles[dir_path].add(item[0])
                else:
                    self.unique_subfiles[dir_path].update(
                        self.get_unique_subfiles(item[0]))
        return self.unique_subfiles[dir_path]


def main():
    n, m = map(int, input().split())
    ft = FileTree()

    for i in range(n + m):
        parenrt, child, is_dir = input().split()
        is_dir = is_dir == "1"
        ft.add_component(parenrt, child, is_dir)

    k = int(input())

    for _ in range(k):
        src, dst = input().split()
        ft.move_dir_content(src, dst)

    q = int(input())
    for _ in range(q):
        dir_path = input()
        subfile_count = ft.get_subfile_count(dir_path)
        unique_subfiles = ft.get_unique_subfiles(dir_path)
        print(subfile_count, len(unique_subfiles))


if __name__ == "__main__":
    main()
