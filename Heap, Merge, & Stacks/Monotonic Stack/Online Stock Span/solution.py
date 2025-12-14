class StockSpanner:

    def __init__(self):
        self.stack = [] # (price, span)

    def next(self, price: int) -> int:
        span = 1
        while self.stack and self.stack[-1][0] <= price:
            span += self.stack.pop()[1]
        self.stack.append((price, span))
        return span

if __name__ == "__main__":
    spanner = StockSpanner()
    print(f"100: {spanner.next(100)}") # 1
    print(f"80: {spanner.next(80)}")   # 1
    print(f"60: {spanner.next(60)}")   # 1
    print(f"70: {spanner.next(70)}")   # 2
    print(f"60: {spanner.next(60)}")   # 1
    print(f"75: {spanner.next(75)}")   # 4
    print(f"85: {spanner.next(85)}")   # 6
