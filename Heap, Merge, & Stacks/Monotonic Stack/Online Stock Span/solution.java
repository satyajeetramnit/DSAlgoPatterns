import java.util.Stack;

class StockSpanner {
    Stack<int[]> stack; // {price, span}

    public StockSpanner() {
        stack = new Stack<>();
    }
    
    public int next(int price) {
        int span = 1;
        while (!stack.isEmpty() && stack.peek()[0] <= price) {
            span += stack.pop()[1];
        }
        stack.push(new int[]{price, span});
        return span;
    }

    public static void main(String[] args) {
        StockSpanner spanner = new StockSpanner();
        System.out.println("100: " + spanner.next(100)); // 1
        System.out.println("80: " + spanner.next(80));   // 1
        System.out.println("60: " + spanner.next(60));   // 1
        System.out.println("70: " + spanner.next(70));   // 2
        System.out.println("60: " + spanner.next(60));   // 1
        System.out.println("75: " + spanner.next(75));   // 4
        System.out.println("85: " + spanner.next(85));   // 6
    }
}
