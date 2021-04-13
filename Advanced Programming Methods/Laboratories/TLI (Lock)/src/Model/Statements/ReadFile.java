package Model.Statements;


import Exceptions.*;
import Model.ADTs.*;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFile implements IStatement {
    Expression expression;
    String var_name;

    public ReadFile(Expression expression, String var_name) {
        this.expression = expression;
        this.var_name = var_name;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException{
        IDict<String, Value> symTable = state.getSymTable();
        IDict<StringValue, BufferedReader> fileTable = state.getFileTable();
        IHeap<Integer, Value> heap = new Heap<>();

        if (!symTable.isDefined(var_name)) {
            throw new MyException("Variable not declared!\n");
        } else {
            if (!symTable.lookup(var_name).getType().equals(new IntType())) {
                throw new MyException("Variable type should be IntType!\n");
            }

            if (!this.expression.evaluate(symTable, heap).getType().equals(new StringType())) {
                throw new MyException("Expression evaluate type should be StringType!\n");
            } else {
                StringValue filename = (StringValue) this.expression.evaluate(symTable, heap);
                if (!fileTable.isDefined(filename)) {
                    throw new MyException("File not opened!\n");
                } else {
                    BufferedReader buffer = fileTable.lookup(filename);
                    try {
                        String line = buffer.readLine();
                        if (line == null) {
                            symTable.update(var_name, new IntType().defaultValue());
                        } else {
                            symTable.update(var_name, new IntValue(Integer.parseInt(line)));
                        }
                    } catch (IOException e) {
                        throw new MyException("File not found!\n");
                    }
                }
            }
        }
        return null;
    }

    @Override
    public String toString() {
        return "readFile(" + this.expression.toString() + ", " + this.var_name + ");";
    }

    @Override
    public IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        if (!typeEnv.isDefined(var_name)) {
            throw new TypeCheckException("Variable not defined!");
        }

        Type typevar = typeEnv.lookup(var_name);
        Type typexp = expression.typecheck(typeEnv);
        if (! typevar.equals(new IntType())) {
            throw new TypeCheckException("Variables needs to be integer!");
        }
        if (! typexp.equals(new StringType())) {
            throw new TypeCheckException("Expression needs to be string!");
        }
        return typeEnv;
    }
}
