package Model.ADTs;

import java.util.HashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class BarrierTable<V> implements IBarrierTable<Integer, V> {
    private final AtomicInteger freeLocation;
    private HashMap<Integer, V> table;

    public BarrierTable() {
        this.table = new HashMap<>();
        this.freeLocation = new AtomicInteger(-1);
    }

    @Override
    public synchronized int add(V value) {
        table.put(freeLocation.incrementAndGet(), value);
        return freeLocation.get();
    }

    @Override
    public synchronized V get(Integer key) {
        return table.get(key);
    }

    @Override
    public synchronized void update(Integer key, V value) {
        table.put(key, value);
    }

    @Override
    public synchronized boolean contains(Integer key) {
        return table.containsKey(key);
    }

    @Override
    public synchronized HashMap<Integer, V> getContent() {
        return table;
    }

    @Override
    public synchronized void setContent(HashMap<Integer, V> newContent) {
        table = newContent;
    }

    @Override
    public synchronized String toString() {
        return table.toString();
    }
}
