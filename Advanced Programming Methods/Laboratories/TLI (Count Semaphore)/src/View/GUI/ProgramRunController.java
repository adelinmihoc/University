package View.GUI;

import java.net.URL;
import java.util.HashMap;
import java.util.List;
import java.util.ResourceBundle;
import Controller.Controller;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Values.StringValue;
import Model.Values.Value;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.stage.Stage;


public class ProgramRunController implements Initializable {
    @FXML
    public ListView<String> fileTable_ListView;
    @FXML
    public ListView<String> out_ListView;
    @FXML
    public TableView<HashMap.Entry<Integer, Value>> heapTable_TableView;
    @FXML
    public TableColumn<HashMap.Entry<Integer, Value>, String> heapTableAddr_TableCol;
    @FXML
    public TableColumn<HashMap.Entry<Integer, Value>, String> heapTableVal_TableCol;
    @FXML
    public ListView<String> prgStatesIden_ListView;
    @FXML
    public TableView<HashMap.Entry<String, Value>> symTable_TableView;
    @FXML
    public TableColumn<HashMap.Entry<String, Value>, String> symTableVarName_TableCol;
    @FXML
    public TableColumn<HashMap.Entry<String, Value>, String> symTableValue_TableCol;
    @FXML
    public ListView<String> exeStack_ListView;
    @FXML
    public Button run_Button;
    @FXML
    public Label nrPrgStates_Label;

    Controller controller;

    public ProgramRunController(Controller controller) {
        this.controller = controller;
    }

    public void initialize(URL location, ResourceBundle resources) {
        initialRun();
        prgStatesIden_ListView.setOnMouseClicked(mouseEvent -> setSymTableAndExeStack());
        run_Button.setOnAction(actionEvent -> {
            try {
                if (controller.getRepository().getProgramsList().size() > 0)
                    controller.oneStepGUI();
            } catch (IndexOutOfBoundsException e1) {
                //System.out.println(e1.getClass());
                Alert alert = new Alert(AlertType.INFORMATION);
                alert.setTitle("Toy Language - Current program finished");
                alert.setHeaderText(null);
                alert.setContentText("Program finished successfully!");
                Button confirm = (Button) alert.getDialogPane().lookupButton( ButtonType.OK );
                confirm.setDefaultButton(false);
                confirm.setStyle("-fx-focus-color: transparent; -fx-faint-focus-color: transparent;");
                alert.showAndWait();
                Stage stage = (Stage) heapTable_TableView.getScene().getWindow();
                stage.close();
            } catch (Exception e1) {
                //System.out.println(e1.getClass());
                Alert alert = new Alert(AlertType.INFORMATION);
                alert.setTitle("Toy Language - Current program finished");
                alert.setHeaderText(null);
                alert.setContentText(e1.getMessage());
                Button confirm = (Button) alert.getDialogPane().lookupButton( ButtonType.OK );
                confirm.setDefaultButton(false);
                confirm.setStyle("-fx-focus-color: transparent; -fx-faint-focus-color: transparent;");
                alert.showAndWait();
                Stage stage = (Stage) heapTable_TableView.getScene().getWindow();
                stage.close();
            }
            updateUIComponents();
        });
    }

    public void initialRun() {
        setNumberLabel();
        setHeapTable();
        setOutList();
        setFileTable();
        setProgramStatesList();
        prgStatesIden_ListView.getSelectionModel().selectFirst();
        setSymTableAndExeStack();
    }

    public void updateUIComponents() {
        setNumberLabel();
        setHeapTable();
        setOutList();
        setFileTable();
        setProgramStatesList();

        if(prgStatesIden_ListView.getSelectionModel().getSelectedItem() == null) {
            prgStatesIden_ListView.getSelectionModel().selectFirst();
        }

        setSymTableAndExeStack();
    }

    public void setNumberLabel() {
        nrPrgStates_Label.setText("Number of Program States: " + controller.getRepository().getProgramsList().size());
    }

    public void setHeapTable() {
        ObservableList<HashMap.Entry<Integer, Value>> heapTableList = FXCollections.observableArrayList();
        heapTableAddr_TableCol.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(Integer.toString(cellData.getValue().getKey())));
        heapTableVal_TableCol.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(Value.toString(cellData.getValue().getValue())));
        heapTableList.addAll(controller.getRepository().getProgramsList().get(0).getHeap().getContent().entrySet());
        heapTable_TableView.setItems(heapTableList);
        heapTable_TableView.refresh();
    }

    public void setOutList() {
        ObservableList<String> outObservableList = FXCollections.observableArrayList();
        for (Value e : controller.getRepository().getProgramsList().get(0).getOut().getList()) {
            outObservableList.add(e.toString());
        }
        out_ListView.setItems(outObservableList);
        out_ListView.refresh();
    }

    public void setFileTable() {
        ObservableList<String> fileTableList = FXCollections.observableArrayList();
        for (StringValue e : controller.getRepository().getProgramsList().get(0).getFileTable().getContent().keySet()) {
            fileTableList.add(e.getValue());
        }
        fileTable_ListView.setItems(fileTableList);
        fileTable_ListView.refresh();
    }

    public void setProgramStatesList() {
        ObservableList<String> prgStateIdList = FXCollections.observableArrayList();
        for (ProgramState e : controller.getRepository().getProgramsList()) {
            prgStateIdList.add(Integer.toString(e.getId()));
        }
        prgStatesIden_ListView.setItems(prgStateIdList);
        prgStatesIden_ListView.refresh();
    }

    public void setSymTableAndExeStack() {
        ObservableList<HashMap.Entry<String, Value>> symTableList = FXCollections.observableArrayList();
        ObservableList<String> exeStackList = FXCollections.observableArrayList();
        symTableVarName_TableCol.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getKey()));
        symTableValue_TableCol.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(Value.toString(cellData.getValue().getValue())));
        List<ProgramState> allPrgs = controller.getRepository().getProgramsList();
        ProgramState prgResult = null;
        for (ProgramState e : allPrgs) {
            if(e.getId() == Integer.parseInt(prgStatesIden_ListView.getSelectionModel().getSelectedItem())) {
                prgResult = e;
                break;
            }
        }
        if (prgResult != null) {
            symTableList.addAll(prgResult.getSymTable().getContent().entrySet());
            for (IStatement e : prgResult.getExeStack().getContent()) {
                exeStackList.add(e.toString());
            }
            symTable_TableView.setItems(symTableList);
            exeStack_ListView.setItems(exeStackList);
            symTable_TableView.refresh();
            exeStack_ListView.refresh();
        }
    }

}

