package model;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DocumentDAO {
    public static Connection getConnection() {
        final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        final String DB_URL = "jdbc:mysql://localhost:3306/pw_exam";
        final String dbUsername = "root";
        final String dbPassword = "adelin123";

        Connection connection = null;
        try {
            Class.forName(JDBC_DRIVER);
            connection = DriverManager.getConnection(DB_URL, dbUsername, dbPassword);
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
        return connection;
    }

    public static List<Document> getAllFiltered(String username) {
        List<Document> list = new ArrayList<>();
        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "select d.id, d.name, d.contents from Documents d " +
                            "inner join Authors a " +
                            "on a.documentList like concat('%', d.id, '%') " +
                            "where a.name = ?");
            preparedStatement.setString(1, username);
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Document document = new Document();

                document.setId(resultSet.getInt("id"));
                document.setName(resultSet.getString("name"));
                document.setContents(resultSet.getString("contents"));

                list.add(document);
            }

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        return list;
    }

    public static List<Document> getAll() {
//        List<Document> list = new ArrayList<>();
//        try {
//            Connection connection = getConnection();
//            PreparedStatement preparedStatement = connection.prepareStatement("select * from Documents");
//            ResultSet resultSet = preparedStatement.executeQuery();
//
//            while (resultSet.next()) {
//                VacationDestination vacationDestination = new VacationDestination();
//                vacationDestination.setId(resultSet.getInt("id"));
//                vacationDestination.setDestination(resultSet.getString("destination"));
//                vacationDestination.setCountry(resultSet.getString("country"));
//                vacationDestination.setPrice(resultSet.getInt("price"));
//                list.add(vacationDestination);
//            }
//
//        } catch (SQLException throwables) {
//            throwables.printStackTrace();
//        }
//        return list;
        return null;
    }
}
