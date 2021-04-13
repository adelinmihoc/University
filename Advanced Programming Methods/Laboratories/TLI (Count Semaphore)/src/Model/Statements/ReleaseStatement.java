package Model.Statements;

import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ADTs.ISemaphoreTable;
import Model.ADTs.IStack;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import javafx.util.Pair;

import java.io.IOException;
import java.util.List;

public class ReleaseStatement implements IStatement {
    String var;

    public ReleaseStatement(String var) {
        this.var = var;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        ISemaphoreTable<Integer, Pair<Integer, List<Integer>>> semaphoreTable = state.getSemaphoreTable();
        IStack<IStatement> stack = state.getExeStack();
        IDict<String, Value> symTable = state.getSymTable();

        if (symTable.isDefined(var)) {
            if (symTable.lookup(var).getType().equals(new IntType())) {
                IntValue foundIndex = (IntValue) symTable.lookup(var);

                if (semaphoreTable.contains(foundIndex.getValue())) {
                    Pair<Integer, List<Integer>> entry = semaphoreTable.get(foundIndex.getValue());
                    List<Integer> List1 = entry.getValue();
                    if (List1.contains(state.getId())) {
                        List1.remove((Integer) state.getId());
                    }

                } else {
                    throw new MyException("Index not found in Semaphore Table!");
                }
            } else {
                throw new MyException("Variable needs to have type Int!");
            }
        } else {
            throw new MyException("Variable not declared!");
        }

        return null;
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "ReleaseStatement{}";
    }
}
