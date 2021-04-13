package Model.Statements;

import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ADTs.IProcTable;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.Type;
import Model.Values.Value;
import javafx.util.Pair;

import java.io.IOException;
import java.util.List;

public class CallStatement implements IStatement {
    String fname;
    List<Expression> params;

    public CallStatement(String fname, List<Expression> params) {
        this.fname = fname;
        this.params = params;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        IProcTable<String, Pair<List<String>, IStatement>> procTable = state.getProcTable();
        IDict<String, Value> currSymTable = state.getSymTableStack().peek();

        if (procTable.contains(fname)) {
            Pair<List<String>, IStatement> procEntry = procTable.get(fname);

            List<String> proc_params = procEntry.getKey();
            int N1 = params.size();
            int N2 = proc_params.size();

            if (N1 != N2) {
                throw new MyException("Incorrect no. of parameters for the procedure!");
            }

            IDict<String, Value> newSymTable = currSymTable.Iclone();


            for (int i = 0; i < N1; i++) {
                Value eval_exp_i = params.get(i).evaluate(currSymTable, state.getHeap());
                newSymTable.add(proc_params.get(i), eval_exp_i);
            }

            state.getSymTableStack().push(newSymTable);
            state.getExeStack().push(new ReturnStatement());
            state.getExeStack().push(procEntry.getValue());

        } else {
            throw new MyException("Cannot find procedure!");
        }
        return null;
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "[call " + fname + "(" + params + ")]";
    }
}
