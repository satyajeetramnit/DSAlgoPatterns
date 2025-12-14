# Accounts Merge

## 🧩 Problem Statement
Given a list of `accounts` where each element `accounts[i]` is a list of strings, where the first element `accounts[i][0]` is a name, and the rest of the elements are **emails** representing emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails **sorted in ASCII order**. The accounts themselves can be returned in any order.

### 🔹 Example 1:
#### Input:
```plaintext
accounts = [
  ["John","johnsmith@mail.com","john_newyork@mail.com"],
  ["John","johnsmith@mail.com","john00@mail.com"],
  ["Mary","mary@mail.com"],
  ["John","johnnybravo@mail.com"]
]
```
#### Output:
```plaintext
[
  ["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],
  ["Mary","mary@mail.com"],
  ["John","johnnybravo@mail.com"]
]
```
**Explanation:**
- The first and second John share "johnsmith@mail.com", so they are the same person.
- The third John ("johnnybravo") shares no emails, so he is separate.
- Mary is separate.

## 🔍 Approaches

### 1. Union-Find (Disjoint Set Union)
We can treat each **email** as a node. Relationships are bounded by the account they appear in.
1. **Map Emails to IDs:** Assign a unique integer ID to every unique email address.
2. **Union Accounts:** For each account, union the first email with every other email in that list.
3. **Group by Component:** Iterate through all emails, find their root parent, and group them.
4. **Format Output:** For each group, look up the name (from the original account that introduced the email) and sort the emails.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(NK \log NK)$ or $O(NK \cdot \alpha(N))$ depending on sorting vs Union-Find cost, where $N$ is number of accounts and $K$ is max emails length. Sorting dominates final output.
- **Space Complexity:** $O(NK)$ to store emails and DSU.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, int> emailToIndex;
        unordered_map<string, string> emailToName;
        int idCount = 0;
        
        for (const auto& account : accounts) {
            string name = account[0];
            for (int i = 1; i < account.size(); ++i) {
                if (emailToIndex.find(account[i]) == emailToIndex.end()) {
                    emailToIndex[account[i]] = idCount++;
                    emailToName[account[i]] = name;
                }
            }
        }
        
        DSU dsu(idCount);
        
        for (const auto& account : accounts) {
            int firstIdx = emailToIndex[account[1]];
            for (int i = 2; i < account.size(); ++i) {
                dsu.unite(firstIdx, emailToIndex[account[i]]);
            }
        }
        
        unordered_map<int, vector<string>> components;
        for (auto& pair : emailToIndex) {
            string email = pair.first;
            int idx = pair.second;
            int root = dsu.find(idx);
            components[root].push_back(email);
        }
        
        vector<vector<string>> result;
        for (auto& pair : components) {
            vector<string> emailList = pair.second;
            sort(emailList.begin(), emailList.end());
            emailList.insert(emailList.begin(), emailToName[emailList[0]]);
            result.push_back(emailList);
        }
        
        return result;
    }
};
```

### Python
```python
from typing import List
from collections import defaultdict

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
        
    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)
        if rootX != rootY:
            self.parent[rootX] = rootY

class Solution:
    def accountsMerge(self, accounts: List[List[str]]) -> List[List[str]]:
        email_to_id = {}
        email_to_name = {}
        id_counter = 0
        
        for acc in accounts:
            name = acc[0]
            for email in acc[1:]:
                if email not in email_to_id:
                    email_to_id[email] = id_counter
                    id_counter += 1
                    email_to_name[email] = name
                    
        dsu = DSU(id_counter)
        
        for acc in accounts:
            first_email_id = email_to_id[acc[1]]
            for email in acc[2:]:
                dsu.union(first_email_id, email_to_id[email])
                
        components = defaultdict(list)
        for email, id_val in email_to_id.items():
            root = dsu.find(id_val)
            components[root].append(email)
            
        result = []
        for root, emails in components.items():
            result.append([email_to_name[emails[0]]] + sorted(emails))
            
        return result
```

### Java
```java
import java.util.*;

class Solution {
    static class DSU {
        int[] parent;
        DSU(int n) {
            parent = new int[n];
            for(int i=0; i<n; i++) parent[i] = i;
        }
        int find(int x) {
            if(parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }
        void union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if(rootX != rootY) {
                parent[rootX] = rootY;
            }
        }
    }

    public List<List<String>> accountsMerge(List<List<String>> accounts) {
        Map<String, Integer> emailToIndex = new HashMap<>();
        Map<String, String> emailToName = new HashMap<>();
        int idCount = 0;
        
        for (List<String> account : accounts) {
            String name = account.get(0);
            for (int i = 1; i < account.size(); i++) {
                String email = account.get(i);
                if (!emailToIndex.containsKey(email)) {
                    emailToIndex.put(email, idCount++);
                    emailToName.put(email, name);
                }
            }
        }
        
        DSU dsu = new DSU(idCount);
        
        for (List<String> account : accounts) {
            int firstIdx = emailToIndex.get(account.get(1));
            for (int i = 2; i < account.size(); i++) {
                dsu.union(firstIdx, emailToIndex.get(account.get(i)));
            }
        }
        
        Map<Integer, List<String>> components = new HashMap<>();
        for (String email : emailToIndex.keySet()) {
            int root = dsu.find(emailToIndex.get(email));
            components.putIfAbsent(root, new ArrayList<>());
            components.get(root).add(email);
        }
        
        List<List<String>> result = new ArrayList<>();
        for (List<String> emails : components.values()) {
            Collections.sort(emails);
            emails.add(0, emailToName.get(emails.get(0)));
            result.add(emails);
        }
        
        return result;
    }
}
```

## 🌍 Real-World Analogy
### **Contact De-duplication:**
Your phone has contacts: "John Smith (jsmith@a.com)", "J. Smith (jsmith@a.com, johnny@b.com)", "John S. (johnny@b.com)".
Because they share emails, you know they are all the same "John Smith". You merge them into one contact card.

## 🎯 Summary
✅ **Union-Find:** Ideal for transitivity problems (A=B, B=C => A=C).
