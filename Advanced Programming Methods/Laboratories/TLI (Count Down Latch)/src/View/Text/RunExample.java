package View.Text;

import Controller.Controller;
import Exceptions.*;

import java.io.IOException;

public class RunExample extends Command {
    private final Controller controller;

    public RunExample(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try{
            controller.allSteps();
        } catch (IOException | MyException | InterruptedException | RuntimeException | java.util.concurrent.ExecutionException e) {
            System.out.println(e.getMessage());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
