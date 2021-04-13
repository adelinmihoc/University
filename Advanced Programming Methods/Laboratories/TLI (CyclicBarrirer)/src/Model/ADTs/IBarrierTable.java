package Model.ADTs;

import java.util.HashMap;

public interface IBarrierTable<K, V> {
    int add(V value);
    V get(K key);
    void update(K key, V value);
    boolean contains(K key);
    HashMap<K, V> getContent();
    void setContent(HashMap<K, V> newContent);
    String toString();
}
