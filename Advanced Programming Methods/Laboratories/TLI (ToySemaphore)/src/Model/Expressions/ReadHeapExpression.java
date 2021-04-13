package Model.Expressions;

import Exceptions.*;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.Types.ReferenceType;
import Model.Types.Type;
import Model.Values.ReferenceValue;
import Model.Values.Value;

public class ReadHeapExpression extends Expression {
    Expression expression;

    public ReadHeapExpression(Expression expression) {
        this.expression = expression;
    }

    @Override
    public Value evaluate(IDict<String, Value> symTable, IHeap<Integer, Value> heap) throws MyException {
        Value value = this.expression.evaluate(symTable, heap);

        if (!(value instanceof ReferenceValue)) {
            throw new MyException("Expression type should be ReferenceType!");
        }

        ReferenceValue referenceValue = (ReferenceValue) this.expression.evaluate(symTable, heap);
        int address = referenceValue.getAddress();
        if (heap.contains(address)) {
            throw new MyException("Heap address not found!");
        }
        return heap.get(address);
    }

    @Override
    public String toString() {
        return "rH(" + expression.toString() + ")";
    }

    @Override
    public Type typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        Type typ = expression.typecheck(typeEnv);
        if (typ instanceof ReferenceType) {
            ReferenceType reft = (ReferenceType) typ;
            return reft.getInner();
        } else {
            throw new TypeCheckException("The rH argument is not a Ref Type!");
        }
    }
}
