package Controller;

import Exceptions.*;
import Model.ProgramState;
import Model.Values.ReferenceValue;
import Model.Values.Value;
import Repository.IRepository;
import java.io.IOException;
import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;


public class Controller {
    IRepository repository;
    public boolean displayFlag;
    ExecutorService executor;

    public void addProgram(ProgramState programState) throws MyException {
        this.repository.add(programState);
    }

    public Controller(IRepository repository) {
        this.repository = repository;
        this.displayFlag = false;
    }

    public Map<Integer, Value> safeGarbageCollector(java.util.List<Integer> symTableAddresses, Map<Integer, Value> heap) {
        return heap.entrySet().stream()
                .filter(e->symTableAddresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public java.util.List<Integer> getAddrFromSymTable(List<Collection<Value>> symTableValues, Map<Integer, Value> heapDict) {
        Set<Integer> set = new HashSet<>();
        for (Collection<Value> col: symTableValues) {
            set.addAll(col.stream()
                    .filter(v -> v instanceof ReferenceValue)
                    .map(v -> {
                        ReferenceValue v1 = (ReferenceValue) v;
                        return v1.getAddress();
                    }).collect(Collectors.toSet()));
        }

        while (true) {
            java.util.List<Integer> heapReferencedAddresses = heapDict.entrySet().stream()
                    .filter(entry -> entry.getValue() instanceof ReferenceValue)
                    .filter(entry -> set.contains(entry.getKey()))
                    .map(entry -> {
                        ReferenceValue value = (ReferenceValue) entry.getValue();
                        return value.getAddress();
                    })
                    .filter(entry -> !set.contains(entry))
                    .collect(Collectors.toList());
            if (heapReferencedAddresses.isEmpty()) {
                break;
            }
            set.addAll(heapReferencedAddresses);
        }

        return new ArrayList<>(set);
    }

    public List<ProgramState> removeCompletedProgram(List<ProgramState> inProgramList) {
        return inProgramList.stream()
                .filter(ProgramState::isNotCompleted)
                .collect(Collectors.toList());
    }

    public void oneStepForAllPrograms(List<ProgramState> programStatesList) throws Exception {
        programStatesList.forEach(programState -> {
            try {
                this.repository.logProgramStateExec(programState);
            } catch (IOException | MyException e) {
                throw new RuntimeException(e);

            }
        });

        try {
            List<Callable<ProgramState>> callList = programStatesList.stream()
                    .map((ProgramState p) -> (Callable<ProgramState>) (p::oneStep))
                    .collect(Collectors.toList());


            List<ProgramState> newProgramList = executor.invokeAll(callList).stream()
                    .map(future -> {
                        try {
                            return future.get();
                        } catch (InterruptedException | ExecutionException e) {
                            //throw new RuntimeException(e.getMessage());
                            System.out.println(e.getMessage());
                        }
                        return null;
                    })
                    .filter(Objects::nonNull)
                    .collect(Collectors.toList());

            programStatesList.addAll(newProgramList);
        } catch (Exception e) {
            throw new MyException(e.getMessage());
        }

        programStatesList.forEach(programState -> {
            try {
                this.repository.logProgramStateExec(programState);
            } catch (IOException | MyException e) {
                throw new RuntimeException(e);
            }
        });

        this.repository.setProgramsList(programStatesList);
    }

    public void allSteps() throws Exception {
        executor = Executors.newFixedThreadPool(2);
        List<ProgramState> programStatesList = removeCompletedProgram(this.repository.getProgramsList());
        while (programStatesList.size() > 0) {

            List<Collection<Value>> allSymTableValues = new LinkedList<>();
            for (ProgramState programState: programStatesList) {
                allSymTableValues.add(programState.getSymTable().getContent().values());
            }

            programStatesList.get(0).getHeap().setContent(
                    (HashMap<Integer, Value>) safeGarbageCollector(
                            getAddrFromSymTable(
                                    allSymTableValues,
                                    programStatesList.get(0).getHeap().getContent()),
                            programStatesList.get(0).getHeap().getContent())
            );


            oneStepForAllPrograms(programStatesList);
            programStatesList = removeCompletedProgram(this.repository.getProgramsList());
        }
        executor.shutdownNow();

        this.repository.setProgramsList(programStatesList);
    }

    public void oneStepGUI() throws Exception {
        List<ProgramState> programStatesList = removeCompletedProgram(repository.getProgramsList());

        //garbage collector part------------------------------------------------
        List<Collection<Value>> allSymTableValues = new LinkedList<>();
        for (ProgramState programState: programStatesList) {
            allSymTableValues.add(programState.getSymTable().getContent().values());
        }

        programStatesList.get(0).getHeap().setContent(
                (HashMap<Integer, Value>) safeGarbageCollector(
                        getAddrFromSymTable(
                                allSymTableValues,
                                programStatesList.get(0).getHeap().getContent()),
                        programStatesList.get(0).getHeap().getContent())
        );
        //-----------------------------------------------------------------------

        try {
            executor = Executors.newFixedThreadPool(2);
            oneStepForAllPrograms(programStatesList);
            executor.shutdown();
        } catch (Exception e) {
            throw new MyException(e.getMessage());
        }

    }

    public IRepository getRepository() {
        return this.repository;
    }

    @Override
    public String toString() {
        return this.repository.getProgramsList().get(0).getOriginalProgram().toString();
    }
}
