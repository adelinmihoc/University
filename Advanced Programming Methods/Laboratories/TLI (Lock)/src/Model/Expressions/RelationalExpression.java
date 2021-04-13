package Model.Expressions;


import Exceptions.*;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.Value;

public class RelationalExpression extends Expression {
    private final Expression expression1;
    private final Expression expression2;
    private final String operand;

    public RelationalExpression(Expression expression1, Expression expression2, String operand) {
        this.expression1 = expression1;
        this.expression2 = expression2;
        this.operand = operand;
    }

    @Override
    public Value evaluate(IDict<String, Value> symTable, IHeap<Integer, Value> heap) throws MyException {
        if (!this.expression1.evaluate(symTable, heap).getType().equals(new IntType()) || !this.expression2.evaluate(symTable, heap).getType().equals(new IntType())) {
            throw new MyException("Expressions type need to be IntType!\n");
        }

        IntValue intValue1 = (IntValue) this.expression1.evaluate(symTable, heap);
        IntValue intValue2 = (IntValue) this.expression2.evaluate(symTable, heap);

        switch (this.operand) {
            case "<":
                if (intValue1.getValue() < intValue2.getValue()) {
                    return new BoolValue(true);
                } else {
                    return new BoolValue(false);
                }
            case "<=":
                if (intValue1.getValue() <= intValue2.getValue()) {
                    return new BoolValue(true);
                } else {
                    return new BoolValue(false);
                }
            case "==":
                if (intValue1.getValue() == intValue2.getValue()) {
                    return new BoolValue(true);
                } else {
                    return new BoolValue(false);
                }
            case "!=":
                if (intValue1.getValue() != intValue2.getValue()) {
                    return new BoolValue(true);
                } else {
                    return new BoolValue(false);
                }
            case ">":
                if (intValue1.getValue() > intValue2.getValue()) {
                    return new BoolValue(true);
                } else {
                    return new BoolValue(false);
                }
            case ">=":
                if (intValue1.getValue() >= intValue2.getValue()) {
                    return new BoolValue(true);
                } else {
                    return new BoolValue(false);
                }
            case "mul":
                return new IntValue((intValue1.getValue() * intValue2.getValue()) - (intValue1.getValue() + intValue2.getValue()));
            default:
                throw new MyException("Operand type not recognized!\n");
        }
    }

    @Override
    public String toString() {
        return expression1.toString() + operand + expression2.toString();
    }

    @Override
    public Type typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        Type typ1, typ2;
        typ1 = expression1.typecheck(typeEnv);
        typ2 = expression2.typecheck(typeEnv);

        if (!typ1.equals(new IntType()) || !typ2.equals(new IntType())) {
            throw new TypeCheckException("Expressions type needs to be IntType!");
        }
        return new BoolType();
    }
}