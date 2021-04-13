package Model.Statements;

import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ProgramState;
import Model.Types.Type;

import java.io.IOException;

public class ReturnStatement implements IStatement {

    public ReturnStatement() {
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        state.getSymTableStack().pop();
        return null;
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "ReturnStatement{}";
    }
}
