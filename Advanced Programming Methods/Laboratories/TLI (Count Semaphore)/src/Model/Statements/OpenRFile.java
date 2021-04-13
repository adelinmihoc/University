package Model.Statements;


import Exceptions.*;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.StringType;
import Model.Types.Type;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;

public class OpenRFile implements IStatement {
    Expression expression;

    public OpenRFile(Expression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDict<String, Value> symTable = state.getSymTable();
        IDict<StringValue, BufferedReader> fileTable = state.getFileTable();
        IHeap<Integer, Value> heap = state.getHeap();

        if (expression.evaluate(symTable, heap).getType().equals(new StringType())) {
            StringValue filename = (StringValue) expression.evaluate(symTable, heap);
            if (fileTable.isDefined(filename)) {
                throw new MyException("File already opened!\n");
            } else {
                try {
                    BufferedReader buffer = new BufferedReader(new InputStreamReader(new FileInputStream(filename.getValue())));
                    fileTable.add(filename, buffer);
                } catch (FileNotFoundException e) {
                    throw new MyException("File not found!\n");
                }
            }
        } else {
            throw new MyException("Expression evaluate type should be StringType!\n");
        }

        return null;
    }

    @Override
    public String toString() {
        return "openRFile(" + this.expression.toString() + ");" ;
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


