package Model.Statements;

import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ADTs.IStack;
import Model.ProgramState;
import Model.Types.Type;

public class CompoundStatement implements IStatement{
    IStatement first;
    IStatement second;

    @Override
    public String toString() {
        return first.toString() + " | " + second.toString();
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        return second.typecheck(first.typecheck(typeEnv));
    }

    public CompoundStatement(IStatement first, IStatement second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        IStack<IStatement> stack = state.getExeStack();

        stack.push(this.second);
        stack.push(this.first);
        return null;
    }
}