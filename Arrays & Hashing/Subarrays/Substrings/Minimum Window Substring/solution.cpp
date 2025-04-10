#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

string minWindow(string s, string t) {
    if (s.empty() || t.empty())
        return "";

    // Dictionary to store counts of characters in t
    unordered_map<char, int> dictT;
    for (char c : t)
        dictT[c]++;

    // Number of unique characters in t that must be present in the window
    int required = dictT.size();

    // Sliding window counters
    unordered_map<char, int> windowCounts;
    int formed = 0;

    // (window length, left, right)
    int minLen = INT_MAX, minLeft = 0;

    int l = 0;
    // Expand the window with right pointer
    for (int r = 0; r < s.size(); r++) {
        char c = s[r];
        windowCounts[c]++;
        
        if (dictT.count(c) && windowCounts[c] == dictT[c])
            formed++;

        // Try to contract the window till the point it's no longer 'desirable'
        while (l <= r && formed == required) {
            // Update smallest window if smaller found
            if (r - l + 1 < minLen) {
                minLen = r - l + 1;
                minLeft = l;
            }
            
            char d = s[l];
            windowCounts[d]--;
            if (dictT.count(d) && windowCounts[d] < dictT[d])
                formed--;
            l++;
        }
    }
    
    return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
}

int main() {
    string s = "ADOBECODEBANC", t = "ABC";
    cout << "Minimum Window Substring: " << minWindow(s, t) << endl;
    return 0;
}
