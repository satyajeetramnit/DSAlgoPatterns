#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class SnapshotArray {
  vector<vector<pair<int, int>>> history;
  int snapId;

public:
  SnapshotArray(int length) {
    history.resize(length);
    for (int i = 0; i < length; ++i) {
      history[i].push_back({0, 0});
    }
    snapId = 0;
  }

  void set(int index, int val) {
    if (history[index].back().first == snapId) {
      history[index].back().second = val;
    } else {
      history[index].push_back({snapId, val});
    }
  }

  int snap() { return snapId++; }

  int get(int index, int snap_id) {
    auto it = upper_bound(history[index].begin(), history[index].end(),
                          make_pair(snap_id, 2000000000));
    return prev(it)->second;
  }
};

int main() {
  SnapshotArray snapshotArr(3);
  snapshotArr.set(0, 5);             // set index 0 to 5
  int snap0 = snapshotArr.snap();    // take a snapshot, return snap_id = 0
  snapshotArr.set(0, 6);             // set index 0 to 6
  int snap1 = snapshotArr.get(0, 0); // Get index 0 at snap 0. Expect 5.

  cout << "Snap ID: " << snap0 << endl;            // 0
  cout << "Get(0, 0) Expect 5: " << snap1 << endl; // 5
  cout << "Get(0, 1) Expect 6 (Current): " << snapshotArr.get(0, 1)
       << endl; // 6 (Wait, snap() incremented ID to 1. But set(0,6) happened
                // AFTER snap 0, so it belongs to snap 1. If we call snap()
                // again, it finalizes snap 1. Currently we are in snap 1.)
  // Technically get(index, snap_id) should be for a finalized snapshot?
  // Problem says "time we took the snapshot with the given snap_id".
  // set() updates current state. snap() finalizes it and increments counter.
  // So if current snapId is 1, set(0, 6) updates for snapId 1.
  // But we haven't called snap() again to return 1.
  // However, get(0, 1) is valid if we assume current state is accessible or if
  // we snap again. Let's snap again to be clean.
  int snap2 = snapshotArr.snap();                                  // returns 1
  cout << "Get(0, 1) Expect 6: " << snapshotArr.get(0, 1) << endl; // 6

  return 0;
}
