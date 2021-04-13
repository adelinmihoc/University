package Model.Types;

import Model.Values.Value;

public interface Type {
    boolean equals(Type other);
    String toString();
    Value defaultValue();
}