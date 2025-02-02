module com.example.interpretergui {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.interpretergui to javafx.fxml;
    exports com.example.interpretergui;
}