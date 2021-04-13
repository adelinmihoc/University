package Model.Statements;

import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.ADTs.ISemaphoreTable;
import Model.ADTs.Triplet;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;

import java.io.IOException;
import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Release implements IStatement {
    String var;
    private static final Lock lock = new ReentrantLock();

    public Release(String var) {
        this.var = var;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        lock.lock();
        IDict<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        ISemaphoreTable<Integer, Triplet<Integer, List<Integer>, Integer>> semaphoreTable = state.getSemaphoreTable();

        if (symTable.isDefined(var)) {
            if (symTable.lookup(var).getType().equals(new IntType())) {
                IntValue foundIndex = (IntValue) symTable.lookup(var);

                if (semaphoreTable.contains(foundIndex.getValue())) {
                    Triplet<Integer, List<Integer>, Integer> entry = semaphoreTable.get(foundIndex.getValue());
                    List<Integer> List1 = entry.getSecond();
                    if (List1.contains(state.getId())) {
                        List1.remove((Integer) state.getId());
                        /*Triplet<Integer, List<Integer>, Integer> updateEntry = new Triplet<>(N1, List1, N2);
                        semaphoreTable.update(foundIndex.getValue(), updateEntry);*/
                    }

                } else {
                    throw new MyException("Index not in Semaphore Table!");
                }

            } else {
                throw new MyException("Variable needs to have type Int!");
            }
        } else {
            throw new MyException("Variable not declared!");
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
        return "release(" + var + ")";
    }
}
