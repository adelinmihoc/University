package Model.ADTs;

public class Triplet<T, U, V> {

    private final T first;
    private final U second;
    private final V third;

    public Triplet(T first, U second, V third) {
        this.first = first;
        this.second = second;
        this.third = third;
    }

    public synchronized T getFirst() { return first; }
    public synchronized U getSecond() { return second; }
    public synchronized V getThird() { return third; }

    @Override
    public synchronized String toString() {
        return "<" + first + "," + second + "," + third + ">";
    }
}