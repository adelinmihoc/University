package Repository;


import Exceptions.MyException;

import java.util.LinkedList;
import java.util.List;
import Model.ProgramState;
import Model.Statements.IStatement;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;


public class Repository implements IRepository {
    List<ProgramState> programStates;
    String logFilePath = "";

    public Repository(String logFilePath) {
        this.programStates = new LinkedList<>();
        this.logFilePath = logFilePath;
    }

    @Override
    public void logProgramStateExec(ProgramState programState) throws MyException {
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)));
            logFile.append(programState.toString());
            logFile.close();
        } catch (IOException e) {
            throw new MyException("File not found!\n");
        }
    }

    @Override
    public List<ProgramState> getProgramsList() {
        return this.programStates;
    }

    @Override
    public void setProgramsList(List<ProgramState> newProgramsList) {
        this.programStates = newProgramsList;
    }

    @Override
    public void add(ProgramState newProgramState) throws MyException {
        programStates.add(newProgramState);
    }

}