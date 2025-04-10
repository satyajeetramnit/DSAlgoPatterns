def longestUniqueSubstring(s: str) -> str:
    last_index = {}
    l = 0
    max_len = 0
    max_start = 0

    for r, char in enumerate(s):
        # If character is found in the current window, shift the left pointer.
        if char in last_index and last_index[char] >= l:
            l = last_index[char] + 1
        last_index[char] = r

        # Update the maximum window.
        if r - l + 1 > max_len:
            max_len = r - l + 1
            max_start = l

    return s[max_start:max_start + max_len]

# Example usage
s = "abcabcbb"
print("Longest Unique Substring:", longestUniqueSubstring(s))
