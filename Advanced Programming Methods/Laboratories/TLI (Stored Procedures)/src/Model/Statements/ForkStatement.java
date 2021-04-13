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
        IList<Value> out = state.getOut();
        IDict<StringValue, BufferedReader> fileTable = state.getFileTable();
        IHeap<Integer, Value> heap = state.getHeap();

        IStack<IStatement> newStack = new Stack<>();
        IStack<IDict<String, Value>> newSymTableStack_reversed = new Stack<>();

        for (IDict<String, Value> currSymTable: state.getSymTableStack().getContent()) {
            IDict<String, Value> newSymTable = new Dict<>();
            for(Map.Entry<String, Value> entry : currSymTable.getContent().entrySet()) {
                String key = entry.getKey();
                Value value = entry.getValue();
                newSymTable.add(key, value.deepCopy());
            }
            newSymTableStack_reversed.push(newSymTable);
        }

        IStack<IDict<String, Value>> newSymTableStack = new Stack<>();

        for (IDict<String, Value> currSymTable: newSymTableStack_reversed.getContent()) {
            newSymTableStack.push(currSymTable);
        }

        return new ProgramState(newStack, newSymTableStack, out, statement, fileTable, heap, state.getId() * 10, state.getProcTable());
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
