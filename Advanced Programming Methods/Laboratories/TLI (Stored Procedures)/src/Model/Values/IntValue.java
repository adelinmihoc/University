package Model.Values;

import Model.Types.IntType;
import Model.Types.Type;

public class IntValue implements Value{
    int value;

    public IntValue(int value) {
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }

    @Override
    public Type getType() {
        return new IntType();
    }

    public String toString() {
        return Integer.toString(value);
    }

    @Override
    public Value deepCopy() {
        return new IntValue(value);
    }

}
