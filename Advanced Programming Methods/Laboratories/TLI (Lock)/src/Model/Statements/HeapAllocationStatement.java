package Model.Statements;


import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.ReferenceType;
import Model.Types.Type;
import Model.Values.ReferenceValue;
import Model.Values.Value;

public class HeapAllocationStatement implements IStatement {
    String varName;
    Expression expression;

    public HeapAllocationStatement(String varName, Expression expression) {
        this.varName = varName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDict<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();

        if (!symTable.isDefined(varName)) {
            throw new MyException("Variable not found!");
        }
        Value expressionValue = this.expression.evaluate(symTable, heap);

        if (!symTable.lookup(varName).getType().equals(new ReferenceType(expressionValue.getType()))) {
            throw new MyException("Variable type should be ReferenceType!");
        }
        ReferenceValue varValue = (ReferenceValue) symTable.lookup(varName);
        ReferenceType varRefType = (ReferenceType) varValue.getType();
        Type varType = varRefType.getInner();

        if (!varType.equals(expressionValue.getType())) {
            throw new MyException("Reference points to different type!");
        }

        int address = heap.add(expressionValue);
        symTable.update(varName, new ReferenceValue(address, expressionValue.getType()));

        return null;
    }

    @Override
    public String toString() {
        return "new(" + varName + "," + expression.toString() + ")";
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        Type typevar = typeEnv.lookup(varName);
        Type typexp = expression.typecheck(typeEnv);
        if (typevar.equals(new ReferenceType(typexp))) {
            return typeEnv;
        } else {
            throw new TypeCheckException("NEW stmt: right hand side and left hand side have different types!");
        }
    }
}
