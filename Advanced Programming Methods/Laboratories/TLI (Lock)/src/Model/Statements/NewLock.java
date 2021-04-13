package Model.Statements;

import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.ADTs.ILockTable;
import Model.ADTs.IStack;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;

import java.io.IOException;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Lock;

public class NewLock implements IStatement {
    String var;
    private static Lock lock = new ReentrantLock();

    public NewLock(String var) {
        this.var = var;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        lock.lock();
        IStack<IStatement> stack = state.getExeStack();
        IDict<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        ILockTable<Integer> lockTable = state.getLockTable();


        if (symTable.isDefined(var)) {
            Value variableValue = symTable.lookup(var);
            if (variableValue.getType().equals(new IntType())) {
                int addr = lockTable.allocate(-1);
                symTable.update(var, new IntValue(addr));
            } else {
                throw new MyException("Variable not of type int!");
            }
        } else {
            throw new MyException("Variable is not defined!");
        }
        lock.unlock();
        return null;
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "newLock(" + var + ")";
    }
}
