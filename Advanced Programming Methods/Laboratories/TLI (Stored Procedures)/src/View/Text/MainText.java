package View.Text;


import Controller.Controller;
import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.*;
import Model.Expressions.*;
import Model.ProgramState;
import Model.Statements.*;
import Model.Types.*;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;
import Repository.IRepository;
import Repository.Repository;
import javafx.util.Pair;

import java.io.BufferedReader;
import java.util.ArrayList;


public class MainText {
    public static void main(String[] args) {

        //----------Examples----------//

        //-----------------------------------------//
        IStatement example1 = new CompoundStatement(
                new VarDeclStatement("v", new IntType()),
                new CompoundStatement(
                        new AssignStatement("v", new ConstExpression(new IntValue(2))),
                        new PrintStatement(new VarExpression("v"))
                )
        );

        //-----------------------------------------//
        IStatement example2 = new CompoundStatement(
                new CompoundStatement(
                        new CompoundStatement(
                                new CompoundStatement(
                                        new VarDeclStatement("a",new IntType()),
                                        new VarDeclStatement("b", new IntType())
                                ),
                                new AssignStatement("a", new ArithmeticExpression('+', new ConstExpression(new IntValue(2)), new ArithmeticExpression('*',new ConstExpression(new IntValue(3)), new ConstExpression(new IntValue(5))))
                                )
                        ),
                        new AssignStatement("b", new ArithmeticExpression('+', new VarExpression("a"), new ConstExpression(new IntValue(1))))
                ) ,
                new PrintStatement(new VarExpression("b"))
        );

        //-----------------------------------------//
        IStatement example3 = new CompoundStatement(
                new CompoundStatement(
                        new CompoundStatement(
                                new CompoundStatement(
                                        new VarDeclStatement("a", new BoolType()),
                                        new VarDeclStatement("v", new IntType())),
                                new AssignStatement("a", new ConstExpression(new BoolValue(true)))
                        ),
                        new IfStatement(new VarExpression("a"), new AssignStatement("v", new ConstExpression(new IntValue(2))), new AssignStatement("v", new ConstExpression(new IntValue(3))))
                ), new PrintStatement(new VarExpression("v"))
        );


        //-----------------------------------------//
        IStatement example4 = new CompoundStatement(
                new CompoundStatement(
                        new CompoundStatement(
                                new CompoundStatement(
                                        new CompoundStatement(
                                                new CompoundStatement(
                                                        new CompoundStatement(
                                                                new CompoundStatement(
                                                                        new VarDeclStatement("varf", new StringType()),
                                                                        new AssignStatement("varf", new ConstExpression(new StringValue("C:\\Users\\adeli\\OneDrive\\Documents\\adelin backup\\IdeaProjects\\ToyLanguageInterpreter\\src\\Tests\\test.in")))
                                                                ),
                                                                new OpenRFile(new VarExpression("varf"))
                                                        ),
                                                        new VarDeclStatement("varc", new IntType())
                                                ),
                                                new ReadFile(new VarExpression("varf"), "varc")
                                        ), new PrintStatement(new VarExpression("varc"))
                                ),
                                new ReadFile(new VarExpression("varf"), "varc")
                        ), new PrintStatement(new VarExpression("varc"))
                ),
                new CloseRFile(new VarExpression("varf"))
        );

        //-----------------------------------------//
        IStatement example5 = new CompoundStatement(
                new VarDeclStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(
                        new HeapAllocationStatement("v", new ConstExpression(new IntValue(20))),
                        new CompoundStatement(
                                new VarDeclStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(
                                        new HeapAllocationStatement("a", new VarExpression("v")),
                                        new CompoundStatement(
                                                new PrintStatement(new ReadHeapExpression(new VarExpression("v"))),
                                                new PrintStatement(new ReadHeapExpression(new ReadHeapExpression(new VarExpression("a"))))
                                        )
                                )
                        )
                )
        );

        //-----------------------------------------//
        IStatement example6 = new CompoundStatement(
                new CompoundStatement(
                        new CompoundStatement(
                                new CompoundStatement(
                                        new CompoundStatement(
                                                new VarDeclStatement("v", new ReferenceType(new IntType()))
                                                ,new HeapAllocationStatement("v", new ConstExpression(new IntValue(20)))
                                        )
                                        , new VarDeclStatement("a", new ReferenceType(new ReferenceType(new IntType())))
                                )
                                , new HeapAllocationStatement("a", new VarExpression("v"))
                        )
                        , new HeapAllocationStatement("v", new ConstExpression(new IntValue(30)))
                )
                , new PrintStatement(new ReadHeapExpression(new ReadHeapExpression(new VarExpression("a"))))
        );

        //-----------------------------------------//
        IStatement example7 = new CompoundStatement(
                new CompoundStatement(
                        new CompoundStatement(
                                new VarDeclStatement("v", new IntType())
                                , new AssignStatement("v", new ConstExpression(new IntValue(4)))
                        )
                        ,new WhileStatement(new RelationalExpression(new VarExpression("v"), new ConstExpression(new IntValue(0)), ">"), new CompoundStatement(new PrintStatement(new VarExpression("v")) , new AssignStatement("v", new ArithmeticExpression('-',new VarExpression("v"), new ConstExpression(new IntValue(1))))))
                )
                , new PrintStatement(new VarExpression("v"))
        ) ;

        //-----------------------------------------//
        IStatement example8 = new CompoundStatement(
                new VarDeclStatement("v", new IntType()),
                new CompoundStatement(
                        new VarDeclStatement("a", new ReferenceType(new IntType())),
                        new CompoundStatement(
                                new AssignStatement("v", new ConstExpression(new IntValue(10))),
                                new CompoundStatement(
                                        new HeapAllocationStatement("a", new ConstExpression(new IntValue(22))),
                                        new CompoundStatement(
                                                new ForkStatement(
                                                        new CompoundStatement(
                                                                new HeapWriteStatement("a", new ConstExpression(new IntValue(30))),
                                                                new CompoundStatement(
                                                                        new AssignStatement("v", new ConstExpression(new IntValue(32))),
                                                                        new CompoundStatement(
                                                                                new PrintStatement(new VarExpression("v")),
                                                                                new PrintStatement(new ReadHeapExpression(new VarExpression("a")))
                                                                        )
                                                                )
                                                        )
                                                ),
                                                new CompoundStatement(
                                                        new PrintStatement(new VarExpression("v")),
                                                        new PrintStatement(new ReadHeapExpression(new VarExpression("a")))
                                                )
                                        )
                                )
                        )
                )
        );

        //-----------------------------------------//
        ArrayList<Expression> list1 = new ArrayList<>();
        list1.add(new ArithmeticExpression('*', new VarExpression("v"), new ConstExpression(new IntValue(10))));
        list1.add(new VarExpression("w"));

        ArrayList<Expression> list2 = new ArrayList<>();
        list2.add(new VarExpression("v"));
        list2.add(new VarExpression("w"));

        ArrayList<Expression> list3 = new ArrayList<>();
        list3.add(new VarExpression("v"));
        list3.add(new VarExpression("w"));

        IStatement example9 = new CompoundStatement(
                new VarDeclStatement("v", new IntType()),
                new CompoundStatement(
                        new VarDeclStatement("w", new IntType()),
                        new CompoundStatement(
                                new AssignStatement("v", new ConstExpression(new IntValue(2))),
                                new CompoundStatement(
                                        new AssignStatement("w", new ConstExpression(new IntValue(5))),
                                        new CompoundStatement(
                                                new CallStatement("sum", list1),
                                                new CompoundStatement(
                                                        new PrintStatement(new VarExpression("v")),
                                                        new ForkStatement(
                                                                new CompoundStatement(
                                                                        new CallStatement("product", list2),
                                                                        new ForkStatement(new CallStatement("sum", list3))
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );


        //-----------------------------------------//
        IStatement example10 = new PrintStatement(new ConstExpression(new IntValue(10)));




        //----------Type Checking----------//
        try {
            example1.typecheck(new Dict<>());
            example2.typecheck(new Dict<>());
            example3.typecheck(new Dict<>());
            example4.typecheck(new Dict<>());
            example5.typecheck(new Dict<>());
            example6.typecheck(new Dict<>());
            example7.typecheck(new Dict<>());
            example8.typecheck(new Dict<>());
            example9.typecheck(new Dict<>());
            example10.typecheck(new Dict<>());
        } catch (TypeCheckException e) {
            System.out.println(e.toString());
        }


        //----------Stacks----------//
        IStack<IStatement> stack1 = new Stack<>();
        IStack<IStatement> stack2 = new Stack<>();
        IStack<IStatement> stack3 = new Stack<>();
        IStack<IStatement> stack4 = new Stack<>();
        IStack<IStatement> stack5 = new Stack<>();
        IStack<IStatement> stack6 = new Stack<>();
        IStack<IStatement> stack7 = new Stack<>();
        IStack<IStatement> stack8 = new Stack<>();
        IStack<IStatement> stack9 = new Stack<>();
        IStack<IStatement> stack10 = new Stack<>();


        //----------SymTables----------//
        IDict<String, Value> symTable1 = new Dict<>();
        IDict<String, Value> symTable2 = new Dict<>();
        IDict<String, Value> symTable3 = new Dict<>();
        IDict<String, Value> symTable4 = new Dict<>();
        IDict<String, Value> symTable5 = new Dict<>();
        IDict<String, Value> symTable6 = new Dict<>();
        IDict<String, Value> symTable7 = new Dict<>();
        IDict<String, Value> symTable8 = new Dict<>();
        IDict<String, Value> symTable9 = new Dict<>();
        IDict<String, Value> symTable10 = new Dict<>();


        //----------Outs----------//
        IList<Value> out1 = new List<>();
        IList<Value> out2 = new List<>();
        IList<Value> out3 = new List<>();
        IList<Value> out4 = new List<>();
        IList<Value> out5 = new List<>();
        IList<Value> out6 = new List<>();
        IList<Value> out7 = new List<>();
        IList<Value> out8 = new List<>();
        IList<Value> out9 = new List<>();
        IList<Value> out10 = new List<>();


        //----------FileTables----------//
        IDict<StringValue, BufferedReader> fileTable1 = new Dict<>();
        IDict<StringValue, BufferedReader> fileTable2 = new Dict<>();
        IDict<StringValue, BufferedReader> fileTable3 = new Dict<>();
        IDict<StringValue, BufferedReader> fileTable4 = new Dict<>();
        IDict<StringValue, BufferedReader> fileTable5 = new Dict<>();
        IDict<StringValue, BufferedReader> fileTable6 = new Dict<>();
        IDict<StringValue, BufferedReader> fileTable7 = new Dict<>();
        IDict<StringValue, BufferedReader> fileTable8 = new Dict<>();
        IDict<StringValue, BufferedReader> fileTable9 = new Dict<>();
        IDict<StringValue, BufferedReader> fileTable10 = new Dict<>();


        //----------Heaps----------//
        IHeap<Integer, Value> heap1 = new Heap<>();
        IHeap<Integer, Value> heap2 = new Heap<>();
        IHeap<Integer, Value> heap3 = new Heap<>();
        IHeap<Integer, Value> heap4 = new Heap<>();
        IHeap<Integer, Value> heap5 = new Heap<>();
        IHeap<Integer, Value> heap6 = new Heap<>();
        IHeap<Integer, Value> heap7 = new Heap<>();
        IHeap<Integer, Value> heap8 = new Heap<>();
        IHeap<Integer, Value> heap9 = new Heap<>();
        IHeap<Integer, Value> heap10 = new Heap<>();

        //----------Proc Tables----------//
        IProcTable<String, Pair<java.util.List<String>, IStatement>> procTable1 = new ProcTable<>();
        IProcTable<String, Pair<java.util.List<String>, IStatement>> procTable2 = new ProcTable<>();
        IProcTable<String, Pair<java.util.List<String>, IStatement>> procTable3 = new ProcTable<>();
        IProcTable<String, Pair<java.util.List<String>, IStatement>> procTable4 = new ProcTable<>();
        IProcTable<String, Pair<java.util.List<String>, IStatement>> procTable5 = new ProcTable<>();
        IProcTable<String, Pair<java.util.List<String>, IStatement>> procTable6 = new ProcTable<>();
        IProcTable<String, Pair<java.util.List<String>, IStatement>> procTable7 = new ProcTable<>();
        IProcTable<String, Pair<java.util.List<String>, IStatement>> procTable8 = new ProcTable<>();
        IProcTable<String, Pair<java.util.List<String>, IStatement>> procTable9 = new ProcTable<>();
        IProcTable<String, Pair<java.util.List<String>, IStatement>> procTable10 = new ProcTable<>();

        //----------Initializing Proc Tables----------//
                //-----Arrays-----//
        ArrayList<String> str1List9 = new ArrayList<>();
        str1List9.add("a");
        str1List9.add("b");

        ArrayList<String> str2List9 = new ArrayList<>();
        str2List9.add("a");
        str2List9.add("b");
                //-----Statements-----//

        IStatement proc1Stm9 = new CompoundStatement(
                new AssignStatement("v", new ArithmeticExpression('+', new VarExpression("a"), new VarExpression("b"))),
                new PrintStatement(new VarExpression("v"))
        );

        IStatement proc2Stm9 = new CompoundStatement(
                new AssignStatement("v", new ArithmeticExpression('*', new VarExpression("a"), new VarExpression("b"))),
                new PrintStatement(new VarExpression("v"))
        );
                //-----Pairs-----//
        Pair<java.util.List<String>, IStatement> pair9_1 = new Pair<>(str1List9, proc1Stm9);
        Pair<java.util.List<String>, IStatement> pair9_2 = new Pair<>(str2List9, proc2Stm9);

        procTable9.add("sum", pair9_1);
        procTable9.add("product", pair9_2);

        //////////////////////////////////////////////////////////////////////////////////////

        //----------ProgramStates----------//
        ProgramState programState1 = new ProgramState(stack1, symTable1,out1,example1,fileTable1, heap1, procTable1);
        ProgramState programState2 = new ProgramState(stack2, symTable2,out2,example2,fileTable2, heap2, procTable2);
        ProgramState programState3 = new ProgramState(stack3, symTable3,out3,example3,fileTable3, heap3, procTable3);
        ProgramState programState4 = new ProgramState(stack4, symTable4,out4,example4,fileTable4, heap4, procTable4);
        ProgramState programState5 = new ProgramState(stack5, symTable5,out5,example5,fileTable5, heap5, procTable5);
        ProgramState programState6 = new ProgramState(stack6, symTable6,out6,example6,fileTable6, heap6, procTable6);
        ProgramState programState7 = new ProgramState(stack7, symTable7,out7,example7,fileTable7, heap7, procTable7);
        ProgramState programState8 = new ProgramState(stack8, symTable8,out8,example8,fileTable8, heap8, procTable8);
        ProgramState programState9 = new ProgramState(stack9, symTable9,out9,example9,fileTable9, heap9, procTable9);
        ProgramState programState10 = new ProgramState(stack10, symTable10,out10,example10,fileTable10, heap10, procTable10);


        //----------Repositories----------//
        IRepository repository1 = new Repository("log1.txt");
        IRepository repository2 = new Repository("log2.txt");
        IRepository repository3 = new Repository("log3.txt");
        IRepository repository4 = new Repository("log4.txt");
        IRepository repository5 = new Repository("log5.txt");
        IRepository repository6 = new Repository("log6.txt");
        IRepository repository7 = new Repository("log7.txt");
        IRepository repository8 = new Repository("log8.txt");
        IRepository repository9 = new Repository("log9.txt");
        IRepository repository10 = new Repository("log10.txt");


        //----------Controllers----------//
        Controller controller1 = new Controller(repository1);
        Controller controller2 = new Controller(repository2);
        Controller controller3 = new Controller(repository3);
        Controller controller4 = new Controller(repository4);
        Controller controller5 = new Controller(repository5);
        Controller controller6 = new Controller(repository6);
        Controller controller7 = new Controller(repository7);
        Controller controller8 = new Controller(repository8);
        Controller controller9 = new Controller(repository9);
        Controller controller10 = new Controller(repository10);



        //----------Add programs----------//
        try {
            controller1.addProgram(programState1);
            controller2.addProgram(programState2);
            controller3.addProgram(programState3);
            controller4.addProgram(programState4);
            controller5.addProgram(programState5);
            controller6.addProgram(programState6);
            controller7.addProgram(programState7);
            controller8.addProgram(programState8);
            controller9.addProgram(programState9);
            controller10.addProgram(programState10);
        } catch (MyException e) {
            System.out.println(e.toString());
        }



        //----------Text Menu----------//
        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExample("1", example1.toString(), controller1));
        menu.addCommand(new RunExample("2", example2.toString(), controller2));
        menu.addCommand(new RunExample("3", example3.toString(), controller3));
        menu.addCommand(new RunExample("4", example4.toString(), controller4));
        menu.addCommand(new RunExample("5", example5.toString(), controller5));
        menu.addCommand(new RunExample("6", example6.toString(), controller6));
        menu.addCommand(new RunExample("7", example7.toString(), controller7));
        menu.addCommand(new RunExample("8", example8.toString(), controller8));
        menu.addCommand(new RunExample("9", example9.toString(), controller9));
        menu.addCommand(new RunExample("10", example10.toString(), controller10));
        menu.show();

    }
}
