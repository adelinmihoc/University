package Model.Expressions;

import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.Types.Type;
import Model.Values.Value;

public class ConstExpression extends Expression {
    Value value;

    public ConstExpression(Value number) {
        this.value = number;
    }

    @Override
    public Value evaluate(IDict<String, Value> symTable, IHeap<Integer, Value> heap) {
        return value;
    }

    @Override
    public String toString() {
        return this.value.toString();
    }

    @Override
    public Type typecheck(IDict<String, Type> typeEnv) {
        return value.getType();
    }
}
