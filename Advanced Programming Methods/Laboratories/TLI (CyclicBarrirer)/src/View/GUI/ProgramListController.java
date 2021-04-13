package View.GUI;

import Controller.Controller;
import Exceptions.MyException;
import Exceptions.TypeCheckException;
import Model.ADTs.*;
import Model.Expressions.*;
import Model.ProgramState;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.ReferenceType;
import Model.Types.StringType;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;
import Repository.IRepository;
import Repository.Repository;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.stage.Stage;
import javafx.util.Callback;
import javafx.util.Pair;

import java.io.BufferedReader;
import java.io.IOException;


public class ProgramListController {
    static IRepository repository1, repository2, repository3, repository4, repository5, repository6, repository7, repository8, repository9, repository10;
    static Controller controller1, controller2, controller3, controller4, controller5, controller6, controller7, controller8, controller9, controller10;
    static IStatement example1, example2, example3, example4, example5, example6, example7, example8, example9, example10;

    @FXML
    public Button startProgramButton;

    @FXML
    private ListView<Controller> programListView;

    @FXML
    private Label label;

    public void setUp() {
        //----------Examples----------//

        //-----------------------------------------//
         example1 = new CompoundStatement(
                new VarDeclStatement("v", new IntType()),
                new CompoundStatement(
                        new AssignStatement("v", new ConstExpression(new IntValue(2))),
                        new PrintStatement(new VarExpression("v"))
                )
        );

        //-----------------------------------------//
         example2 = new CompoundStatement(
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
         example3 = new CompoundStatement(
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
         example4 = new CompoundStatement(
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
         example5 = new CompoundStatement(
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
         example6 = new CompoundStatement(
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
         example7 = new CompoundStatement(
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
         example8 = new CompoundStatement(
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
         example9 = new PrintStatement(new ConstExpression(new IntValue(10)));


        //-----------------------------------------//
         example10 = new PrintStatement(new ConstExpression(new IntValue(10)));




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

        //----------Barrier Tables----------//
        IBarrierTable<Integer, Pair<Integer, java.util.List<Integer>>> barrierTable1 = new BarrierTable<>();
        IBarrierTable<Integer, Pair<Integer, java.util.List<Integer>>> barrierTable2 = new BarrierTable<>();
        IBarrierTable<Integer, Pair<Integer, java.util.List<Integer>>> barrierTable3 = new BarrierTable<>();
        IBarrierTable<Integer, Pair<Integer, java.util.List<Integer>>> barrierTable4 = new BarrierTable<>();
        IBarrierTable<Integer, Pair<Integer, java.util.List<Integer>>> barrierTable5 = new BarrierTable<>();
        IBarrierTable<Integer, Pair<Integer, java.util.List<Integer>>> barrierTable6 = new BarrierTable<>();
        IBarrierTable<Integer, Pair<Integer, java.util.List<Integer>>> barrierTable7 = new BarrierTable<>();
        IBarrierTable<Integer, Pair<Integer, java.util.List<Integer>>> barrierTable8 = new BarrierTable<>();
        IBarrierTable<Integer, Pair<Integer, java.util.List<Integer>>> barrierTable9 = new BarrierTable<>();
        IBarrierTable<Integer, Pair<Integer, java.util.List<Integer>>> barrierTable10 = new BarrierTable<>();


        //----------ProgramStates----------//
        ProgramState programState1 = new ProgramState(stack1, symTable1,out1,example1,fileTable1, heap1, barrierTable1);
        ProgramState programState2 = new ProgramState(stack2, symTable2,out2,example2,fileTable2, heap2, barrierTable2);
        ProgramState programState3 = new ProgramState(stack3, symTable3,out3,example3,fileTable3, heap3, barrierTable3);
        ProgramState programState4 = new ProgramState(stack4, symTable4,out4,example4,fileTable4, heap4, barrierTable4);
        ProgramState programState5 = new ProgramState(stack5, symTable5,out5,example5,fileTable5, heap5, barrierTable5);
        ProgramState programState6 = new ProgramState(stack6, symTable6,out6,example6,fileTable6, heap6, barrierTable6);
        ProgramState programState7 = new ProgramState(stack7, symTable7,out7,example7,fileTable7, heap7, barrierTable7);
        ProgramState programState8 = new ProgramState(stack8, symTable8,out8,example8,fileTable8, heap8, barrierTable8);
        ProgramState programState9 = new ProgramState(stack9, symTable9,out9,example9,fileTable9, heap9, barrierTable9);
        ProgramState programState10 = new ProgramState(stack10, symTable10,out10,example10,fileTable10, heap10, barrierTable10);


        //----------Repositories----------//
         repository1 = new Repository("log1.txt");
         repository2 = new Repository("log2.txt");
         repository3 = new Repository("log3.txt");
         repository4 = new Repository("log4.txt");
         repository5 = new Repository("log5.txt");
         repository6 = new Repository("log6.txt");
         repository7 = new Repository("log7.txt");
         repository8 = new Repository("log8.txt");
         repository9 = new Repository("log9.txt");
         repository10 = new Repository("log10.txt");


        //----------Controllers----------//
         controller1 = new Controller(repository1);
         controller2 = new Controller(repository2);
         controller3 = new Controller(repository3);
         controller4 = new Controller(repository4);
         controller5 = new Controller(repository5);
         controller6 = new Controller(repository6);
         controller7 = new Controller(repository7);
         controller8 = new Controller(repository8);
         controller9 = new Controller(repository9);
         controller10 = new Controller(repository10);



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
    }

    @FXML
    public void initialize() {
        setUp();

        ObservableList<Controller> controllers = FXCollections.observableArrayList();
        controllers.add(controller1);
        controllers.add(controller2);
        controllers.add(controller3);
        controllers.add(controller4);
        controllers.add(controller5);
        controllers.add(controller6);
        controllers.add(controller7);
        controllers.add(controller8);
        controllers.add(controller9);
        controllers.add(controller10);

        programListView.setItems(controllers);
        programListView.getSelectionModel().selectFirst();

    }

    public void runProgram() {
        label.setText("Running program:\n" + programListView.getSelectionModel().getSelectedItem().toString());

        Stage programStage = new Stage();
        Parent programRoot;
        Callback<Class<?>, Object> controllerFactory = type -> {
            if (type == ProgramRunController.class) {
                return new ProgramRunController(programListView.getSelectionModel().getSelectedItem());
            } else {
                try {
                    return type.newInstance() ;
                } catch (Exception exc) {
                    System.err.println("Could not create controller for "+type.getName());
                    throw new RuntimeException(exc);
                }
            }
        };
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("ProgramLayout.fxml"));
            fxmlLoader.setControllerFactory(controllerFactory);
            programRoot = fxmlLoader.load();
            Scene programScene = new Scene(programRoot);
            programStage.setTitle("Toy Language - Program running");
            programStage.setScene(programScene);
            programScene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
            programStage.show();
        } catch (IOException e1) {
            e1.printStackTrace();
        }

    }

}
