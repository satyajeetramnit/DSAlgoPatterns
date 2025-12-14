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

if __name__ == "__main__":
    sol = Solution()
    accounts = [
        ["John","johnsmith@mail.com","john_newyork@mail.com"],
        ["John","johnsmith@mail.com","john00@mail.com"],
        ["Mary","mary@mail.com"],
        ["John","johnnybravo@mail.com"]
    ]
    res = sol.accountsMerge(accounts)
    for r in res:
        print(r)
