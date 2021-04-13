package Model.Expressions;


import Exceptions.*;
import Model.ADTs.IDict;
import Model.ADTs.IHeap;
import Model.Types.BoolType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.Value;

public class LogicExpression extends Expression {
    Expression expression1;
    Expression expression2;
    String operand;

    public LogicExpression(Expression expression1, Expression expression2, String operand) {
        this.expression1 = expression1;
        this.expression2 = expression2;
        this.operand = operand;
    }

    public LogicExpression(Expression expression1, String operand) {
        this.expression1 = expression1;
        this.expression2 = null;
        this.operand = operand;
    }

    @Override
    public Value evaluate(IDict<String, Value> symTable, IHeap<Integer, Value> heap) throws MyException {
        if (expression2 != null) {
            if (!expression1.evaluate(symTable, heap).getType().equals(new BoolType()) ||
                    !expression2.evaluate(symTable, heap).getType().equals(new BoolType())) {
                throw new MyException("Expressions type needs to be bool!\n");
            }
            BoolValue cond1 = (BoolValue) expression1.evaluate(symTable, heap);
            BoolValue cond2 = (BoolValue) expression2.evaluate(symTable, heap);
            switch (operand) {
                case "and":
                    if (cond1.getValue() && cond2.getValue()) {
                        return new BoolValue(true);
                    } else {
                        return new BoolValue(false);
                    }
                case "or":
                    if (cond1.getValue() || cond2.getValue()) {
                        return new BoolValue(true);
                    } else {
                        return new BoolValue(false);
                    }

                default:
                    throw new MyException("Operand type not recognized!\n");
            }
        } else {
            if (operand.equals("!")) {
                if (!expression1.evaluate(symTable, heap).getType().equals(new BoolType())) {
                    throw new MyException("Expressions type needs to be bool!\n");
                }
                BoolValue cond1 = (BoolValue) expression1.evaluate(symTable, heap);

                if (cond1.getValue()) {
                    return new BoolValue(false);
                } else {
                    return new BoolValue(true);
                }
            }
            throw new MyException("Operand type not recognized!\n");
        }
    }

    @Override
    public String toString() {
        if (expression2 != null) {
            return "(" + expression1.toString() + " " + operand + " " + expression2.toString() + ")";
        } else {
            return "(" + operand + expression1.toString() +")";
        }
    }

    @Override
    public Type typecheck(IDict<String, Type> typeEnv) throws TypeCheckException {
        if (expression2 != null) {
            Type typ1, typ2;
            typ1 = expression1.typecheck(typeEnv);
            typ2 = expression2.typecheck(typeEnv);

            if (!typ1.equals(new BoolType()) || !typ2.equals(new BoolType())) {
                throw new TypeCheckException("Expressions type needs to be BoolType!");
            }
        } else {
            Type typ1;
            typ1 = expression1.typecheck(typeEnv);
            if (!typ1.equals(new BoolType())) {
                throw new TypeCheckException("Expression type needs to be bool!");
            }
        }
        return new BoolType();
    }
}
