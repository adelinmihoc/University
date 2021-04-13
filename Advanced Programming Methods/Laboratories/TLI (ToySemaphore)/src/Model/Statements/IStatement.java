package Model.Statements;

import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.IDict;
import Model.ProgramState;
import Model.Types.Type;

import java.io.IOException;

public interface IStatement {
    ProgramState execute(ProgramState state) throws MyException, IOException;
    String toString();
    IDict<String, Type> typecheck(IDict<String, Type> typeEnv) throws TypeCheckException;
}
