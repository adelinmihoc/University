package Model.Statements;

import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import javafx.util.Pair;

import java.io.IOException;
import java.util.ArrayList;

public class NewBarrierStatement implements IStatement {
    String var;
    Expression exp;

    public NewBarrierStatement(String var, Expression exp) {
        this.var = var;
        this.exp = exp;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        Value number = exp.evaluate(state.getSymTable(), state.getHeap());

        if (!number.getType().equals(new IntType())) {
            throw new MyException("Exp must have IntType!");
        }

        IntValue numberVal = (IntValue) number;

        int newFreeLocation = state.getBarrierTable().add(new Pair<>(numberVal.getValue(), new ArrayList<>()));

        if (state.getSymTable().isDefined(var)) {
            state.getSymTable().update(var, new IntValue(newFreeLocation));
        } else {
            state.getSymTable().add(var, new IntValue(newFreeLocation));
        }

        return null;
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "newBarrier(" + var + "," + exp.toString() + ")";
    }
}
