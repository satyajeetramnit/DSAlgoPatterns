#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int maxSubArray(vector<int>& nums) {
    int max_sum = nums[0], current_sum = 0;
    int start = 0, end = 0, temp_start = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        current_sum += nums[i];
        
        if (current_sum > max_sum) {
            max_sum = current_sum;
            start = temp_start;
            end = i;
        }
        
        if (current_sum < 0) {
            current_sum = 0;
            temp_start = i + 1;
        }
    }
    cout << "Subarray: [";
    for (int i = start; i <= end; i++) {
        cout << nums[i] << (i < end ? ", " : "");
    }
    cout << "]" << endl;
    return max_sum;
}

int main() {
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    cout << "Maximum Subarray Sum: " << maxSubArray(nums) << endl;
    return 0;
}