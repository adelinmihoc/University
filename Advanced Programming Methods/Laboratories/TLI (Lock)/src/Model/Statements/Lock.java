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

public class Lock implements IStatement {
    String var;

    public Lock(String var) {
        this.var = var;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        IStack<IStatement> stack = state.getExeStack();
        IDict<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        ILockTable<Integer> lockTable = state.getLockTable();

        if (symTable.isDefined(var)) {
            Value variableValue = symTable.lookup(var);
            if (variableValue.getType().equals(new IntType())) {
                IntValue foundIndex = (IntValue) symTable.lookup(var);

                if (!lockTable.exists(foundIndex.getValue())) {
                    throw new MyException("Lock does not exist!");
                } else {
                    if (lockTable.get(foundIndex.getValue()) == -1) {
                        lockTable.update(foundIndex.getValue(), state.getId());
                    } else {
                        stack.push(this);
                    }
                }
            } else {
                throw new MyException("Variable not of type int!");
            }
        } else {
            throw new MyException("Variable is not defined!");
        }

        return null;
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "lock(" + var + ")";
    }
}
