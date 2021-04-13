package Model.Expressions;

import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.Types.Type;
import Model.Values.Value;

public class VarExpression extends Expression {
    String id;

    public VarExpression(String id) {
        this.id = id;
    }

    @Override
    public Value evaluate(IDict<String, Value> symTable, IHeap<Integer, Value> heap) {
        return symTable.lookup(id);
    }

    @Override
    public String toString() {
        return id;
    }

    @Override
    public Type typecheck(IDict<String, Type> typeEnv) {
        return typeEnv.lookup(id);
    }
}
