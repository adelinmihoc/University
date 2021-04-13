package Model.Statements;


import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.Type;
import Model.Values.Value;


public class AssignStatement implements IStatement {
    String id;
    Expression expression;

    public AssignStatement(String id, Expression expression) {
        this.id = id;
        this.expression = expression;
    }

    @Override
    public String toString() {
        return id + " = " + expression.toString() + "; ";
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        Type typevar = typeEnv.lookup(id);
        Type typexp = expression.typecheck(typeEnv);
        if (typevar.equals(typexp)) {
            return typeEnv;
        } else {
            throw new TypeCheckException("Assignment: right hand side and left hand side have different types!");
        }
    }

    public Expression getExpression() {
        return expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDict<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();

        if (symTable.isDefined(id)) {
            Value value = expression.evaluate(symTable, heap);
            Type typeId = (symTable.lookup(id)).getType();
            if (value.getType().equals(typeId)) {
                symTable.update(id, value);
            } else {
                throw new MyException("Declared type and assigned type do not match!\n");
            }
        } else {
            throw new MyException("Variable not declared!\n");
        }
        return null;
    }
}
