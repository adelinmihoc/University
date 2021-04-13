package Model.ADTs;


import java.util.HashMap;

public class Heap<V> implements IHeap<Integer, V> {
    private HashMap<Integer, V> heap;
    private int freeAddress = 1;

    public Heap() {
        this.heap = new HashMap<>();
    }

    @Override
    public int add(V value) {
        this.heap.put(freeAddress, value);
        this.freeAddress += 1;
        return freeAddress - 1;
    }

    @Override
    public V get(Integer key) {
        return this.heap.get(key);
    }

    @Override
    public void update(Integer key, V value) {
        this.heap.put(key, value);
    }

    @Override
    public boolean contains(Integer key) {
        return !this.heap.containsKey(key);
    }

    @Override
    public HashMap<Integer, V> getContent() {
        return this.heap;
    }

    @Override
    public void setContent(HashMap<Integer, V> newContent) {
        this.heap = newContent;
    }

    @Override
    public String toString() {
        return heap.toString();
    }
}
