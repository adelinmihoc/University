package Model.Statements;


import Exceptions.*;
import Model.ADTs.*;
import Model.ProgramState;
import Model.Types.Type;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.util.Map;

public class ForkStatement implements IStatement {
    IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDict<String, Value> symTable = state.getSymTable();
        IList<Value> out = state.getOut();
        IDict<StringValue, BufferedReader> fileTable = state.getFileTable();
        IHeap<Integer, Value> heap = state.getHeap();

        IStack<IStatement> newStack = new Stack<>();
        IDict<String, Value> newSymTable = new Dict<>();

        for(Map.Entry<String, Value> entry : symTable.getContent().entrySet()) {
            String key = entry.getKey();
            Value value = entry.getValue();
            newSymTable.add(key, value.deepCopy());
        }

        return new ProgramState(newStack, newSymTable, out, statement, fileTable, heap, state.getId() * 10);
    }

    @Override
    public String toString() {
        return "fork(" + this.statement.toString() + ")";
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        statement.typecheck(typeEnv.Iclone());
        return typeEnv;
    }
}
