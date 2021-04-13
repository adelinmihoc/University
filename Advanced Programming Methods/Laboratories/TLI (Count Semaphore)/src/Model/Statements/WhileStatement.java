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

public class WhileStatement implements IStatement {
    Expression expression;
    IStatement statement;

    public WhileStatement(Expression expression, IStatement statement) {
        this.expression = expression;
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IStack<IStatement> stack = state.getExeStack();
        IDict<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();

        if (!this.expression.evaluate(symTable, heap).getType().equals(new BoolType())) {
            throw new MyException("Expression value should be BoolValue!");
        }
        BoolValue boolValue = (BoolValue) this.expression.evaluate(symTable, heap);
        if (boolValue.getValue()) {
            stack.push(new WhileStatement(this.expression, this.statement));
            stack.push(this.statement);
        }

        return null;
    }

    @Override
    public String toString() {
        return "While(" + expression.toString() + ") {" + statement.toString() + "}";
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        if (expression.typecheck(typeEnv).equals(new BoolType())) {
            statement.typecheck(typeEnv.Iclone());
            return typeEnv;
        } else {
            throw new TypeCheckException("Condition type needs to be bool!");
        }
    }
}

