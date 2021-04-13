package View.GUI;

import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.layout.StackPane;
import javafx.fxml.FXMLLoader;


public class MainGUI extends Application {

    @Override
    public void start(Stage primaryStage) {
        try {

            StackPane root = FXMLLoader.load(getClass().getResource("ProgramList.fxml"));
            Scene scene = new Scene(root,800,500);
            scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
            primaryStage.setScene(scene);
            primaryStage.setTitle("Toy Language Interpreter - program chooser");
            primaryStage.show();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }


    public static void main(String[] args) {
        launch(args);
    }
}
