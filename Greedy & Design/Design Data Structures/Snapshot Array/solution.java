import java.util.ArrayList;
import java.util.List;
import java.util.TreeMap;

class SnapshotArray {
    List<TreeMap<Integer, Integer>> history;
    int snapId;

    public SnapshotArray(int length) {
        history = new ArrayList<>();
        for (int i = 0; i < length; i++) {
            TreeMap<Integer, Integer> map = new TreeMap<>();
            map.put(0, 0);
            history.add(map);
        }
        snapId = 0;
    }
    
    public void set(int index, int val) {
        history.get(index).put(snapId, val);
    }
    
    public int snap() {
        return snapId++;
    }
    
    public int get(int index, int snap_id) {
        return history.get(index).floorEntry(snap_id).getValue();
    }

    public static void main(String[] args) {
        SnapshotArray snapshotArr = new SnapshotArray(3);
        snapshotArr.set(0, 5);
        System.out.println("Snap ID: " + snapshotArr.snap()); // 0
        snapshotArr.set(0, 6);
        System.out.println("Get(0, 0) Expect 5: " + snapshotArr.get(0, 0)); // 5
        snapshotArr.snap();
        System.out.println("Get(0, 1) Expect 6: " + snapshotArr.get(0, 1)); // 6
    }
}
