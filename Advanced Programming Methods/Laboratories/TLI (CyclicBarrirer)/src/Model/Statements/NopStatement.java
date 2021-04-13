package Model.Statements;

import Model.ADTs.IDict;
import Model.ProgramState;
import Model.Types.Type;


public class NopStatement implements IStatement {

    @Override
    public String toString() {
        return "NopStatement";
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) {
        return typeEnv;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        return null;
    }
}