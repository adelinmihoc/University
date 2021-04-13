package Model.ADTs;

import java.util.Deque;
import java.util.LinkedList;

public class  Stack<T> implements IStack<T> {
    Deque<T> stack;

    public Stack() {
        this.stack = new LinkedList<>();
    }

    public Stack(Deque<T> content) {
        this.stack = content;
    }

    @Override
    public String toString() {
        if (stack == null) {
            return "{}";
        }
        StringBuilder out = new StringBuilder();
        for (T elem : stack) {
            out.append(elem.toString());
            out.append("\n");
        }
        return out.toString();
    }

    @Override
    public Deque<T> getContent() {
        return stack;
    }

    @Override
    public T pop() {
        return stack.pop();
    }

    @Override
    public void push(T v) {
        stack.addFirst(v);
    }

    @Override
    public boolean isEmpty() {
        return stack.isEmpty();
    }
}
