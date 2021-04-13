package Model.Values;

import Model.Types.ReferenceType;
import Model.Types.Type;


public class ReferenceValue implements Value {
    int address;
    Type locationType;

    public ReferenceValue(int address, Type locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    public int getAddress() {
        return this.address;
    }

    @Override
    public Type getType() {
        return new ReferenceType(locationType);
    }

    @Override
    public String toString() {
        return "RefVal(" + this.address + "," + locationType + ")";
    }

    @Override
    public Value deepCopy() {
        return new ReferenceValue(address, locationType);
    }
}
