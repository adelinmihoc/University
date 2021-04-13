package Model.Expressions;


import Exceptions.*;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;

public class ArithmeticExpression extends Expression {
    char operand;
    Expression left;
    Expression right;

    public ArithmeticExpression(char operand, Expression left, Expression right) {
        this.operand = operand;
        this.left = left;
        this.right = right;
    }

    @Override
    public Value evaluate(IDict<String, Value> symTable, IHeap<Integer, Value> heap) throws MyException{
        Value v1,v2;
        v1 = left.evaluate(symTable, heap);
        v2 = right.evaluate(symTable, heap);
        if (v1.getType().equals(new IntType())) {
            if (v2.getType().equals(new IntType())) {
                IntValue i1 = (IntValue)v1;
                IntValue i2 = (IntValue)v2;
                if (operand == '+') {
                    return new IntValue(i1.getValue() + i2.getValue());
                } else if (operand == '-') {
                    return new IntValue(i1.getValue() - i2.getValue());
                } else if (operand == '*') {
                    return new IntValue(i1.getValue() * i2.getValue());
                } else if (operand == '/') {
                    if (i2.getValue() == 0) {
                        throw new MyException("Division by zero!\n");
                    } else {
                        return new IntValue(i1.getValue()/i2.getValue());
                    }
                } else {
                    throw new MyException("Operand type not recognized!\n");
                }
            } else {
                throw new MyException("Right expression type not int!\n");
            }
        } else {
            throw new MyException("Left expression type not int!\n");
        }
    }

    @Override
    public String toString() {
        return left.toString() + operand + right.toString();
    }

    @Override
    public Type typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        Type typ1, typ2;
        typ1 = left.typecheck(typeEnv);
        typ2 = right.typecheck(typeEnv);

        if (typ1.equals(new IntType())) {
            if (typ2.equals(new IntType())) {
                return new IntType();
            } else {
                throw new TypeCheckException("Second operand is not an integer!");
            }
        } else {
            throw new TypeCheckException("First operand is not an integer!");
        }
    }

}
