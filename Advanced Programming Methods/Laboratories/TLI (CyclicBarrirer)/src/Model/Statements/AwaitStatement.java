package Model.Statements;

import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ProgramState;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import javafx.util.Pair;

import java.io.IOException;
import java.util.List;

public class AwaitStatement implements IStatement {
    String var;

    public AwaitStatement(String var) {
        this.var = var;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {

        if (state.getSymTable().isDefined(var)) {
            IntValue foundIndex = (IntValue) state.getSymTable().lookup(var);

            if (state.getBarrierTable().contains(foundIndex.getValue())) {
                Pair<Integer, List<Integer>> entry = state.getBarrierTable().get(foundIndex.getValue());
                int N1 = entry.getKey();
                List<Integer> List1 = entry.getValue();
                int NL = List1.size();

                System.out.println("N1 = " + N1);
                System.out.println("NL = " + NL);

                if (N1 > NL) {
                    if (!List1.contains(state.getId())) {
                        List1.add(state.getId());
                    }
                    state.getExeStack().push(this);
                }

            } else {
                throw new MyException("Index not found in Barrier table!");
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
        return "await(" + var + ")";
    }
}
