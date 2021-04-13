package Repository;


import Exceptions.MyException;
import java.util.List;
import Model.ProgramState;

import java.io.IOException;

public interface IRepository {
    void add(ProgramState newProgramState) throws MyException;
    void logProgramStateExec(ProgramState programState) throws IOException, MyException;
    List<ProgramState> getProgramsList();
    void setProgramsList(List<ProgramState> newProgramsList);
}
