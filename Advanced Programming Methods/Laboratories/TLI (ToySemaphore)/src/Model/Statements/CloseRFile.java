package Model.Statements;


import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.StringType;
import Model.Types.Type;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFile implements IStatement {
    Expression expression;

    public CloseRFile(Expression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        IDict<String, Value> symTable = state.getSymTable();
        IDict<StringValue, BufferedReader> fileTable = state.getFileTable();
        IHeap<Integer, Value> heap = state.getHeap();

        if (!this.expression.evaluate(symTable, heap).getType().equals(new StringType())) {
            throw new MyException("Expression evaluate type should be StringType!\n");
        } else {
            StringValue filename = (StringValue) this.expression.evaluate(symTable, heap);
            if (!fileTable.isDefined(filename)) {
                throw new MyException("File not found!\n");
            } else {
                BufferedReader buffer = fileTable.lookup(filename);
                buffer.close();
                fileTable.remove(filename);
            }
        }
        return null;
    }

    @Override
    public String toString() {
        return "closeRFile(" + this.expression.toString() + ");";
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        Type typexp = expression.typecheck(typeEnv);
        if (typexp.equals(new StringType())) {
            return typeEnv;
        } else {
            throw new TypeCheckException("Expression needs to be String!");
        }
    }
}

