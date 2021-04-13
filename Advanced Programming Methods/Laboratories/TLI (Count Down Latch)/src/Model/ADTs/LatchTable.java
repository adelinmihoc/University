package Model.ADTs;

import java.util.HashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class LatchTable<V> implements ILatchTable<Integer, V> {
    private final AtomicInteger freeLocation;
    private HashMap<Integer, V> table;

    public LatchTable() {
        this.table = new HashMap<>();
        this.freeLocation = new AtomicInteger(0);
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
    public String toString() {
        return table.toString();
    }
}
