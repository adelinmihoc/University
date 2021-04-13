package Model.Statements;

import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.ADTs.ILatchTable;
import Model.ADTs.IStack;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;

import java.io.IOException;

public class NewLatch implements IStatement {
    String var;
    Expression exp;

    public NewLatch(String var, Expression exp) {
        this.var = var;
        this.exp = exp;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        IStack<IStatement> stack = state.getExeStack();
        IDict<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        ILatchTable<Integer, Value> latchTable = state.getLatchTable();

        if (exp.evaluate(symTable, heap).getType().equals(new IntType())) {
            IntValue num1 = (IntValue) exp.evaluate(symTable, heap);

            if (symTable.isDefined(var)) {
                if (symTable.lookup(var).getType().equals(new IntType())) {
                    int newFreeAddress = latchTable.add(num1);
                    symTable.update(var, new IntValue(newFreeAddress));
                } else {
                    throw new MyException("Variable needs to have type Int!");
                }
            } else {
                throw new MyException("Variable not declared!");
            }
        } else {
            throw new MyException("Expression should evaluate to type Int!");
        }

        return null;
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "newLatch(" + var + "," + exp.toString() + ")";
    }
}
