def maxSubArray(nums):
    max_sum = nums[0]
    current_sum = 0
    start = end = temp_start = 0
    
    for i in range(len(nums)):
        current_sum += nums[i]
        
        if current_sum > max_sum:
            max_sum = current_sum
            start, end = temp_start, i
        
        if current_sum < 0:
            current_sum = 0
            temp_start = i + 1
    
    print("Subarray:", nums[start:end+1])
    return max_sum

# Example usage
nums = [-2,1,-3,4,-1,2,1,-5,4]
print("Maximum Subarray Sum:", maxSubArray(nums))