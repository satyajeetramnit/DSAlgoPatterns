class NumArray {
    int[] tree;
    int n;

    public NumArray(int[] nums) {
        n = nums.length;
        if (n > 0) {
            tree = new int[4 * n];
            build(nums, 1, 0, n - 1);
        }
    }

    private void build(int[] nums, int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
        } else {
            int mid = (start + end) / 2;
            build(nums, 2 * node, start, mid);
            build(nums, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    
    public void update(int index, int val) {
        if (n > 0) update(1, 0, n - 1, index, val);
    }

    private void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node, start, mid, idx, val);
            } else {
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    
    public int sumRange(int left, int right) {
        if (n > 0) return query(1, 0, n - 1, left, right);
        return 0;
    }

    private int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int p1 = query(2 * node, start, mid, l, r);
        int p2 = query(2 * node + 1, mid + 1, end, l, r);
        return p1 + p2;
    }

    public static void main(String[] args) {
        int[] nums = {1, 3, 5};
        NumArray obj = new NumArray(nums);
        
        // Test 1
        assert obj.sumRange(0, 2) == 9 : "Test 1 Failed";
        System.out.println("Test 1 Passed");
        
        // Test 2
        obj.update(1, 2);
        
        // Test 3
        assert obj.sumRange(0, 2) == 8 : "Test 3 Failed";
        System.out.println("Test 3 Passed");
    }
}
