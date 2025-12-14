class BrowserHistory:

    def __init__(self, homepage: str):
        self.history = [homepage]
        self.curr = 0

    def visit(self, url: str) -> None:
        self.curr += 1
        self.history = self.history[:self.curr]
        self.history.append(url)

    def back(self, steps: int) -> str:
        self.curr = max(0, self.curr - steps)
        return self.history[self.curr]

    def forward(self, steps: int) -> str:
        self.curr = min(len(self.history) - 1, self.curr + steps)
        return self.history[self.curr]

if __name__ == "__main__":
    bh = BrowserHistory("leetcode.com")
    bh.visit("google.com")
    bh.visit("facebook.com")
    bh.visit("youtube.com")
    print(f"Back 1 (Expect facebook.com): {bh.back(1)}")
    print(f"Back 1 (Expect google.com): {bh.back(1)}")
    print(f"Forward 1 (Expect facebook.com): {bh.forward(1)}")
    bh.visit("linkedin.com")
    print(f"Forward 2 (Expect linkedin.com): {bh.forward(2)}")
    print(f"Back 2 (Expect google.com): {bh.back(2)}")
    print(f"Back 7 (Expect leetcode.com): {bh.back(7)}")
