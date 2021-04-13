package Model.Values;

import Model.Types.Type;

public interface Value {
    static String toString(Value value) {
        return value.deepCopy().toString();
    }

    Type getType();

    String toString();

    Value deepCopy();
}
