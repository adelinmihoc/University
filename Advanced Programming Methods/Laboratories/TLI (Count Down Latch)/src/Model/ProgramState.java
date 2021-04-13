package Model;


import Exceptions.*;
import Model.ADTs.*;
import Model.Statements.IStatement;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.io.IOException;


public class ProgramState {
    IStack<IStatement> exeStack;
    IDict<String, Value> symTable;
    IList<Value> out;
    IStatement originalProgram;
    IDict<StringValue, BufferedReader> fileTable;
    IHeap<Integer, Value> heap;
    int id = 1;
    ILatchTable<Integer, Value> latchTable;


    public ProgramState(IStack<IStatement> exeStack, IDict<String, Value> symTable, IList<Value> out,
                        IStatement originalProgram, IDict<StringValue, BufferedReader> fileTable,
                        IHeap<Integer, Value> heap, ILatchTable<Integer, Value> latchTable) {
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.originalProgram = originalProgram;
        this.exeStack.push(originalProgram);
        this.fileTable = fileTable;
        this.heap = heap;
        this.latchTable = latchTable;
    }

    public ProgramState(IStack<IStatement> exeStack, IDict<String, Value> symTable, IList<Value> out,
                        IStatement originalProgram, IDict<StringValue, BufferedReader> fileTable,
                        IHeap<Integer, Value> heap, int id, ILatchTable<Integer, Value> latchTable) {
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.originalProgram = originalProgram;
        this.exeStack.push(originalProgram);
        this.fileTable = fileTable;
        this.heap = heap;
        this.id = id;
        this.latchTable = latchTable;
    }

    public ILatchTable<Integer, Value> getLatchTable() {
        return latchTable;
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
                "\n-----------------------LatchTable-------------------\n" + latchTable.toString() +
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
