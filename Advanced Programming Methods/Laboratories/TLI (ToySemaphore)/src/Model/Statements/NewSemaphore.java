package Model.Statements;

import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.*;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class NewSemaphore implements IStatement {
    String var;
    Expression exp1;
    Expression exp2;
    private static final Lock lock = new ReentrantLock();

    public NewSemaphore(String var, Expression exp1, Expression exp2) {
        this.var = var;
        this.exp1 = exp1;
        this.exp2 = exp2;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        lock.lock();
        IDict<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        ISemaphoreTable<Integer, Triplet<Integer, List<Integer>, Integer>> semaphoreTable = state.getSemaphoreTable();

        if (exp1.evaluate(symTable, heap).getType().equals(new IntType())) {
            if (exp2.evaluate(symTable, heap).getType().equals(new IntType())) {
                IntValue number1 = (IntValue) exp1.evaluate(symTable, heap);
                IntValue number2 = (IntValue) exp2.evaluate(symTable, heap);

                if (symTable.isDefined(var)) {
                    Triplet<Integer, List<Integer>, Integer> val = new Triplet<>(number1.getValue(), new ArrayList<>(), number2.getValue());
                    int newLocation = semaphoreTable.add(val);
                    symTable.update(var, new IntValue(newLocation));
                } else {
                    throw new MyException("Variable is not defined!");
                }

            } else {
                throw new MyException("Expression2 must have IntType!");
            }
        } else {
            throw new MyException("Expression1 must have IntType!");
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
        return "newSemaphore(" + var + "," + exp1.toString() + "," + exp2.toString() + ")";
    }
}
