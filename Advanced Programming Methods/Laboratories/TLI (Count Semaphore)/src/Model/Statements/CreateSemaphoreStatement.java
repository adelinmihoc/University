package Model.Statements;

import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.ADTs.ISemaphoreTable;
import Model.ADTs.IStack;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import javafx.util.Pair;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class CreateSemaphoreStatement implements IStatement {
    String var;
    Expression exp1;

    public CreateSemaphoreStatement(String var, Expression exp1) {
        this.var = var;
        this.exp1 = exp1;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        ISemaphoreTable<Integer, Pair<Integer, List<Integer>>> semaphoreTable = state.getSemaphoreTable();
        IStack<IStatement> stack = state.getExeStack();
        IDict<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();

        if (exp1.evaluate(symTable, heap).getType().equals(new IntType())) {
            IntValue number1 = (IntValue) exp1.evaluate(symTable, heap);

            if (symTable.isDefined(var)) {
                if (symTable.lookup(var).getType().equals(new IntType())) {

                    Pair<Integer, List<Integer>> val = new Pair<>(number1.getValue(), new ArrayList<>());
                    int newFreeLocation = semaphoreTable.add(val);
                    symTable.update(var, new IntValue(newFreeLocation));
                } else {
                    throw new MyException("Variable needs to have type Int!");
                }
            } else {
                throw new MyException("Variable not defined!");
            }

        } else {
            throw new MyException("Exp1 needs to have type Int!");
        }


        return null;
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "CreateSemaphoreStatement{}";
    }
}
