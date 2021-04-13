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

public class Unlock implements IStatement {
    String var;

    public Unlock(String var) {
        this.var = var;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        IStack<IStatement> stack = state.getExeStack();
        IDict<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        ILockTable<Integer> lockTable = state.getLockTable();

        if (symTable.isDefined(var)) {
            if (symTable.lookup(var).getType().equals(new IntType())) {
                IntValue foundIndex = (IntValue) symTable.lookup(var);

                if (!lockTable.exists(foundIndex.getValue())) {
                    throw new MyException("Lock does not exists!");
                }

                if (lockTable.get(foundIndex.getValue()).equals(state.getId())) {
                    lockTable.update(foundIndex.getValue(), -1);
                }

            } else {
                throw new MyException("Var is not of type Int!");
            }
        } else {
            throw new MyException("Var not defined!");
        }

        return null;
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "unlock(" + var + ")";
    }
}
