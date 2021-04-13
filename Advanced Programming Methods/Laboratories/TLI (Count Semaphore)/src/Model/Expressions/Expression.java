package Model.Expressions;

import Exceptions.*;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.Types.Type;
import Model.Values.Value;

public abstract class Expression {
    public abstract Value evaluate(IDict<String, Value> symTable, IHeap<Integer, Value> heap) throws MyException;
    public abstract String toString();
    public abstract Type typecheck(IDict<String, Type> typeEnv) throws TypeCheckException;
}
