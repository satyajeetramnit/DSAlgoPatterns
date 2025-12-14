interface MountainArrayInterface {
    public int get(int index);
    public int length();
}

// Mock
class MountainArray implements MountainArrayInterface {
    private int[] arr;
    public MountainArray(int[] arr) { this.arr = arr; }
    public int get(int index) { return arr[index]; }
    public int length() { return arr.length; }
}

class Solution {
    public int findInMountainArray(int target, MountainArrayInterface mountainArr) {
        int n = mountainArr.length();
        
        // 1. Find Peak
        int left = 0, right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        int peak = left;
        
        // 2. Search Left
        left = 0; right = peak;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int val = mountainArr.get(mid);
            if (val == target) return mid;
            if (val < target) left = mid + 1;
            else right = mid - 1;
        }
        
        // 3. Search Right
        left = peak + 1; right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int val = mountainArr.get(mid);
            if (val == target) return mid;
            if (val > target) left = mid + 1; 
            else right = mid - 1;
        }
        
        return -1;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] arr1 = {1,2,3,4,5,3,1};
        MountainArray ma1 = new MountainArray(arr1);
        System.out.println("Index of 3: " + sol.findInMountainArray(3, ma1)); // Expected: 2

        int[] arr2 = {0,1,2,4,2,1};
        MountainArray ma2 = new MountainArray(arr2);
        System.out.println("Index of 3: " + sol.findInMountainArray(3, ma2)); // Expected: -1
    }
}
