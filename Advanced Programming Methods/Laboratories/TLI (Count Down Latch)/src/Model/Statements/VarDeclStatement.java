package Model.Statements;


import Exceptions.MyException;
import Model.ADTs.IDict;
import Model.ProgramState;
import Model.Types.Type;
import Model.Values.Value;


public class VarDeclStatement implements IStatement {
    String name;
    Type type;

    public VarDeclStatement(String name, Type type) {
        this.name = name;
        this.type = type;
    }

    public Type getType() {
        return type;
    }

    @Override
    public String toString() {
        return this.type.toString() + " " + this.name + "; ";
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) {
        typeEnv.add(name, type);
        return typeEnv;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDict<String, Value> symTable = state.getSymTable();

        if (symTable.isDefined(this.name)) {
            throw new MyException("Variable already defined!\n");
        }
        symTable.add(name, type.defaultValue());

        return null;
    }
}