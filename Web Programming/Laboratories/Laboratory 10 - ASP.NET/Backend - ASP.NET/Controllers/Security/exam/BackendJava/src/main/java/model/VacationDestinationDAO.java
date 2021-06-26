package model;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class VacationDestinationDAO {
    public static Connection getConnection() {
        final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        final String DB_URL = "jdbc:mysql://localhost:3306/pw_exam_2021";
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

    public static List<VacationDestination> getAllFiltered(String username, String destination) {
        List<VacationDestination> list = new ArrayList<>();
        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "select v.id, v.destination, v.country, v.price " +
                            "from VacationDestinations v where v.id not in " +
                            "(select b.destinationID from BannedList b where b.user = ?)" +
                            " and v.destination like ?");
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, "%" + destination + "%");
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                VacationDestination vacationDestination = new VacationDestination();
                vacationDestination.setId(resultSet.getInt("id"));
                vacationDestination.setDestination(resultSet.getString("destination"));
                vacationDestination.setCountry(resultSet.getString("country"));
                vacationDestination.setPrice(resultSet.getInt("price"));
                list.add(vacationDestination);
            }

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        return list;
    }

    public static List<VacationDestination> getAll() {
        List<VacationDestination> list = new ArrayList<>();
        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement = connection.prepareStatement("select * from VacationDestinations");
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                VacationDestination vacationDestination = new VacationDestination();
                vacationDestination.setId(resultSet.getInt("id"));
                vacationDestination.setDestination(resultSet.getString("destination"));
                vacationDestination.setCountry(resultSet.getString("country"));
                vacationDestination.setPrice(resultSet.getInt("price"));
                list.add(vacationDestination);
            }

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        return list;
    }

}
