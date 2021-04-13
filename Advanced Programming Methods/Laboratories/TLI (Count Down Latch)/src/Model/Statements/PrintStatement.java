package Model.Statements;


import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.ADTs.IList;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.Type;
import Model.Values.Value;

public class PrintStatement implements IStatement {
    Expression expression;

    public PrintStatement(Expression expression) {
        this.expression = expression;
    }

    public Expression getExpression() {
        return expression;
    }

    @Override
    public String toString() {
        return "Print(" + expression.toString() + "); ";
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        expression.typecheck(typeEnv);
        return typeEnv;
    }


    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDict<String, Value> symTable = state.getSymTable();
        IList<Value> out = state.getOut();
        IHeap<Integer, Value> heap = state.getHeap();

        out.add(this.expression.evaluate(symTable, heap));

        return null;
    }
}

