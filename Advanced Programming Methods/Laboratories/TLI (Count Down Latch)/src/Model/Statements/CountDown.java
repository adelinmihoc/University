package Model.Statements;

import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.*;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;

import java.io.IOException;

public class CountDown implements IStatement {
    String var;

    public CountDown(String var) {
        this.var = var;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        IDict<String, Value> symTable = state.getSymTable();
        ILatchTable<Integer, Value> latchTable = state.getLatchTable();
        IList<Value> out = state.getOut();


        if (symTable.isDefined(var)) {
            if (symTable.lookup(var).getType().equals(new IntType())) {
                IntValue foundIndex = (IntValue) symTable.lookup(var);

                if (latchTable.contains(foundIndex.getValue())) {
                    IntValue value = (IntValue) latchTable.get(foundIndex.getValue());
                    if (value.getValue() > 0) {
                        latchTable.update(foundIndex.getValue(), new IntValue(value.getValue() - 1));
                    }
                    out.add(new IntValue(state.getId()));

                } else {
                    throw new MyException("Index not found in LatchTable!");
                }

            } else {
                throw new MyException("Variable needs to have type int!");
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
        return "countDown(" + var + ")";
    }
}
