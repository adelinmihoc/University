package Model.Statements;


import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.ADTs.IStack;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.BoolType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.Value;

public class IfStatement implements IStatement {
    Expression expression;
    IStatement thenStatement;
    IStatement elseStatement;

    public IfStatement(Expression expression, IStatement thenStatement, IStatement elseStatement) {
        this.expression = expression;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    @Override
    public String toString() {
        return "IF(" + expression.toString() + ") THEN {" + thenStatement.toString() +
                "} ELSE {" + elseStatement.toString() + "}";
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        Type typexp = expression.typecheck(typeEnv);
        if (typexp.equals(new BoolType())) {
            thenStatement.typecheck(typeEnv.Iclone());
            elseStatement.typecheck(typeEnv.Iclone());
            return typeEnv;
        } else {
            throw new TypeCheckException("The condition IF has not the type bool!");
        }
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IStack<IStatement> stack = state.getExeStack();
        IDict<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();

        if (!expression.evaluate(symTable, heap).getType().equals(new BoolType())) {
            throw new MyException("Expression type needs to be bool!\n");
        } else {
            BoolValue condition = (BoolValue) expression.evaluate(symTable, heap);
            if (condition.getValue()) {
                stack.push(thenStatement);
            } else {
                stack.push(elseStatement);
            }
        }

        return null;
    }
}
