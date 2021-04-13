package Model.ADTs;

import java.util.LinkedList;

public interface IList<T> {
    void add(T v);
    T pop();
    String toString();
    T get(int pos);
    void set(int pos, T elem);
    LinkedList<T> getList();
}
