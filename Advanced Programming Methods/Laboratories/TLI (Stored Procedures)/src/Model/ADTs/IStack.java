package Model.ADTs;

import java.util.Deque;

public interface IStack<T> {
    T pop();
    void push(T v);
    boolean isEmpty();
    String toString();
    Deque<T> getContent();
    T peek();
}
