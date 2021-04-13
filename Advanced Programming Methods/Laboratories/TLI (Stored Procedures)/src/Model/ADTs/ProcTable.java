package Model.ADTs;

import java.util.HashMap;

public class ProcTable<V> implements IProcTable<String, V> {
    HashMap<String, V> table;

    public ProcTable() {
        this.table = new HashMap<>();
    }

    @Override
    public int add(String name, V value) {
        this.table.put(name, value);
        return 0;
    }

    @Override
    public V get(String key) {
        return table.get(key);
    }

    @Override
    public void update(String key, V value) {
        this.table.put(key, value);
    }

    @Override
    public boolean contains(String key) {
        return table.containsKey(key);
    }

    @Override
    public HashMap<String, V> getContent() {
        return table;
    }

    @Override
    public void setContent(HashMap<String, V> newContent) {
        table = newContent;
    }
}
