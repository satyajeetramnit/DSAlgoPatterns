import bisect

class SnapshotArray:

    def __init__(self, length: int):
        self.history = [[(0, 0)] for _ in range(length)]
        self.snap_id = 0

    def set(self, index: int, val: int) -> None:
        if self.history[index][-1][0] == self.snap_id:
            self.history[index][-1] = (self.snap_id, val)
        else:
            self.history[index].append((self.snap_id, val))

    def snap(self) -> int:
        self.snap_id += 1
        return self.snap_id - 1

    def get(self, index: int, snap_id: int) -> int:
        idx = bisect.bisect_right(self.history[index], (snap_id, float('inf')))
        return self.history[index][idx - 1][1]

if __name__ == "__main__":
    snapshotArr = SnapshotArray(3)
    snapshotArr.set(0, 5)
    print(f"Snap ID: {snapshotArr.snap()}") # 0
    snapshotArr.set(0, 6)
    print(f"Get(0, 0) Expect 5: {snapshotArr.get(0, 0)}") # 5
    snapshotArr.snap() # 1
    print(f"Get(0, 1) Expect 6: {snapshotArr.get(0, 1)}") # 6
