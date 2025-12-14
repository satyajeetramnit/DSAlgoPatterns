import java.util.ArrayList;
import java.util.List;

class BrowserHistory {
    private List<String> history;
    private int curr, limit;

    public BrowserHistory(String homepage) {
        history = new ArrayList<>();
        history.add(homepage);
        curr = 0;
        limit = 0;
    }
    
    public void visit(String url) {
        curr++;
        if (curr < history.size()) {
            history.set(curr, url);
        } else {
            history.add(url);
        }
        limit = curr;
    }
    
    public String back(int steps) {
        curr = Math.max(0, curr - steps);
        return history.get(curr);
    }
    
    public String forward(int steps) {
        curr = Math.min(limit, curr + steps);
        return history.get(curr);
    }

    public static void main(String[] args) {
        BrowserHistory bh = new BrowserHistory("leetcode.com");
        bh.visit("google.com");
        bh.visit("facebook.com");
        bh.visit("youtube.com");
        System.out.println("Back 1 (Expect facebook.com): " + bh.back(1));
        System.out.println("Back 1 (Expect google.com): " + bh.back(1));
        System.out.println("Forward 1 (Expect facebook.com): " + bh.forward(1));
        bh.visit("linkedin.com");
        System.out.println("Forward 2 (Expect linkedin.com): " + bh.forward(2));
        System.out.println("Back 2 (Expect google.com): " + bh.back(2));
        System.out.println("Back 7 (Expect leetcode.com): " + bh.back(7));
    }
}
