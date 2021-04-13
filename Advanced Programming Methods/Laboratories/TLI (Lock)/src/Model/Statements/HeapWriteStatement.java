package Model.Statements;


import Exceptions.*;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.ReferenceType;
import Model.Types.Type;
import Model.Values.ReferenceValue;
import Model.Values.Value;


public class HeapWriteStatement implements IStatement {
    String varName;
    Expression expression;

    public HeapWriteStatement(String varName, Expression expression) {
        this.varName = varName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDict<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();

        if (!symTable.isDefined(varName)) {
            throw new MyException("Variable not declared!");
        }
        Value value = this.expression.evaluate(symTable, heap);

        if (!symTable.lookup(varName).getType().equals(new ReferenceType(value.getType()))) {
            throw new MyException("Variable type should be ReferenceType!");
        }
        ReferenceValue referenceValue = (ReferenceValue) symTable.lookup(varName);
        ReferenceType referenceType = (ReferenceType) referenceValue.getType();
        if (heap.contains(referenceValue.getAddress())) {
            throw new MyException("Heap already contains this value!");
        }
        Type varRefType = referenceType.getInner();

        if (!value.getType().equals(varRefType)) {
            throw new MyException("Types do not match!");
        }

        int address = referenceValue.getAddress();
        heap.update(address, value);

        return null;
    }

    @Override
    public String toString() {
        return "wh(" + varName +", " + expression.toString() + ")";
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        if (!typeEnv.isDefined(varName)) {
            throw new TypeCheckException("Variable is not defined!");
        }

        Type typevar = typeEnv.lookup(varName);
        Type typexp = expression.typecheck(typeEnv);

        if (! typevar.equals(new ReferenceType(typexp))) {
            throw new TypeCheckException("Right hand side and left hand side have different types!");
        }

        return typeEnv;
    }
}
