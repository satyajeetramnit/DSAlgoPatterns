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

    public static void main(String[] args) {
        Solution sol = new Solution();
        List<List<String>> accounts = new ArrayList<>();
        accounts.add(Arrays.asList("John","johnsmith@mail.com","john_newyork@mail.com"));
        accounts.add(Arrays.asList("John","johnsmith@mail.com","john00@mail.com"));
        accounts.add(Arrays.asList("Mary","mary@mail.com"));
        accounts.add(Arrays.asList("John","johnnybravo@mail.com"));
        
        List<List<String>> res = sol.accountsMerge(accounts);
        for(List<String> acc : res) {
            System.out.println(acc);
        }
    }
}
