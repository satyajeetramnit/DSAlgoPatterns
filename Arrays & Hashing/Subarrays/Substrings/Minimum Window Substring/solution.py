def minWindow(s: str, t: str) -> str:
    if not s or not t:
        return ""
    
    # Frequency map for characters in t
    dict_t = {}
    for char in t:
        dict_t[char] = dict_t.get(char, 0) + 1

    required = len(dict_t)
    l, r = 0, 0
    formed = 0
    window_counts = {}
    
    # (window length, left, right)
    ans = float("inf"), None, None

    while r < len(s):
        char = s[r]
        window_counts[char] = window_counts.get(char, 0) + 1
        
        if char in dict_t and window_counts[char] == dict_t[char]:
            formed += 1

        # Try and contract the window till the condition ceases to be true
        while l <= r and formed == required:
            char = s[l]

            # Save the smallest window
            if r - l + 1 < ans[0]:
                ans = (r - l + 1, l, r)

            window_counts[char] -= 1
            if char in dict_t and window_counts[char] < dict_t[char]:
                formed -= 1

            l += 1    
        r += 1
    
    return "" if ans[0] == float("inf") else s[ans[1] : ans[2] + 1]

# Example usage
s = "ADOBECODEBANC"
t = "ABC"
print("Minimum Window Substring:", minWindow(s, t))
