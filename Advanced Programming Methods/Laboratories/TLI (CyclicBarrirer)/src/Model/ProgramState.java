package Model;


import Exceptions.*;
import Model.ADTs.*;
import Model.Statements.IStatement;
import Model.Values.StringValue;
import Model.Values.Value;
import javafx.util.Pair;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.List;


public class ProgramState {
    IStack<IStatement> exeStack;
    IDict<String, Value> symTable;
    IList<Value> out;
    IStatement originalProgram;
    IDict<StringValue, BufferedReader> fileTable;
    IHeap<Integer, Value> heap;
    int id = 1;
    IBarrierTable<Integer, Pair<Integer, List<Integer>>> barrierTable;


    public ProgramState(IStack<IStatement> exeStack, IDict<String, Value> symTable, IList<Value> out,
                        IStatement originalProgram, IDict<StringValue, BufferedReader> fileTable,
                        IHeap<Integer, Value> heap,IBarrierTable<Integer, Pair<Integer, List<Integer>>> barrierTable) {
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.originalProgram = originalProgram;
        this.exeStack.push(originalProgram);
        this.fileTable = fileTable;
        this.heap = heap;
        this.barrierTable = barrierTable;
    }

    public ProgramState(IStack<IStatement> exeStack, IDict<String, Value> symTable, IList<Value> out,
                        IStatement originalProgram, IDict<StringValue, BufferedReader> fileTable,
                        IHeap<Integer, Value> heap, int id,IBarrierTable<Integer, Pair<Integer, List<Integer>>> barrierTable) {
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.originalProgram = originalProgram;
        this.exeStack.push(originalProgram);
        this.fileTable = fileTable;
        this.heap = heap;
        this.id = id;
        this.barrierTable = barrierTable;
    }

    public IBarrierTable<Integer, Pair<Integer, List<Integer>>> getBarrierTable() {
        return barrierTable;
    }

    public int getId() {
        return id;
    }

    @Override
    public String toString() {
        return "\n\n======================ProgramState==================\n" +
                "---------------------------id-----------------------\n" + id +
                "\n------------------------exeStack--------------------\n" + exeStack.toString() +
                "------------------------symTable--------------------\n" + symTable.toString() +
                "\n--------------------------out-----------------------\n" + out.toString() +
                "\n-------------------------heap-----------------------\n" + heap.toString() +
                "\n-----------------------Barrier----------------------\n" + barrierTable.toString() +
                "\n--------------------originalProgram-----------------\n" + originalProgram.toString() +
                "\n====================================================\n\n\n";
    }

    public IHeap<Integer, Value> getHeap() {
        return heap;
    }

    public IDict<StringValue, BufferedReader> getFileTable() {
        return fileTable;
    }

    public IStack<IStatement> getExeStack() {
        return exeStack;
    }

    public void setExeStack(IStack<IStatement> exeStack) {
        this.exeStack = exeStack;
    }

    public IDict<String, Value> getSymTable() {
        return symTable;
    }

    public void setSymTable(IDict<String, Value> symTable) {
        this.symTable = symTable;
    }

    public IList<Value> getOut() {
        return out;
    }

    public void setOut(IList<Value> out) {
        this.out = out;
    }

    public IStatement getOriginalProgram() {
        return originalProgram;
    }

    public void setOriginalProgram(IStatement originalProgram) {
        this.originalProgram = originalProgram;
    }

    public Boolean isNotCompleted() {
        return !this.exeStack.isEmpty();
    }

    public ProgramState oneStep() throws MyException, IOException {
        if (!this.exeStack.isEmpty()) {
            IStatement currentStatement = this.exeStack.pop();
            return currentStatement.execute(this);
        } else {
            throw new MyException("Empty Execution Stack!\n");
        }
    }
}
