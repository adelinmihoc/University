package Model.ADTs;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public class LockTable<T> implements ILockTable<T> {
    AtomicInteger freeValue;
    Map<Integer, T> lockTable;

    public LockTable() {
        this.lockTable = new HashMap<>();
        freeValue = new AtomicInteger(0);
    }

    @Override
    public synchronized int allocate(T value) {
        lockTable.put(freeValue.incrementAndGet(), value);
        return freeValue.get();
    }

    @Override
    public synchronized void update(int address, T value) {
        lockTable.put(address, value);
    }

    @Override
    public synchronized Map<Integer, T> getContent() {
        return lockTable;
    }

    @Override
    public synchronized boolean exists(int address) {
        return lockTable.containsKey(address);
    }

    @Override
    public synchronized void setContent(Map<Integer, T> map) {
        lockTable = map;
    }

    @Override
    public synchronized T get(int address) {
        return lockTable.get(address);
    }

    @Override
    public String toString() {
        return lockTable.toString();
    }
}
