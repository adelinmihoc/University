package Model.ADTs;


import java.util.LinkedList;


public class List<T> implements IList<T> {
    LinkedList<T> list;

    public List() {
        this.list = new LinkedList<>() {
        };
    }

    @Override
    public String toString() {
        return list.toString();
    }

    @Override
    public T get(int pos) {
        return list.get(pos);
    }

    @Override
    public void set(int pos, T elem) {
        list.set(pos, elem);
    }

    @Override
    public LinkedList<T> getList() {
        return list;
    }

    @Override
    public void add(T v) {
        list.add(v);
    }

    @Override
    public T pop() {
        T r = list.peek();
        list.remove();
        return r;
    }
}
