package model;

import java.sql.*;

public class UserDAO {
    private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/pw_lab8";
    private static final String dbUsername = "root";
    private static final String dbPassword = "adelin123";

    public static User getUserById(Integer id) throws ClassNotFoundException, SQLException {
        Class.forName(JDBC_DRIVER);
        Connection connection = DriverManager.getConnection(DB_URL, dbUsername, dbPassword);
        String sql = "select * from user where id = ?";
        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setInt(1, id);

        ResultSet resultSet = statement.executeQuery();

        User user = null;

        if (resultSet.next()) {
            user = new User();
            user.setId(resultSet.getInt("id"));
            user.setUsername(resultSet.getString("username"));
            user.setName(resultSet.getString("name"));
        }

        connection.close();

        return user;
    }

    public static User checkLogin(String username, String password) throws ClassNotFoundException, SQLException {
        Class.forName(JDBC_DRIVER);
        Connection connection = DriverManager.getConnection(DB_URL, dbUsername, dbPassword);
        String sql = "select * from user where username = ? and password = ?";
        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setString(1, username);
        statement.setString(2, password);

        ResultSet resultSet = statement.executeQuery();

        User user = null;

        if (resultSet.next()) {
            user = new User();
            user.setId(resultSet.getInt("id"));
            user.setUsername(resultSet.getString("username"));
            user.setName(resultSet.getString("name"));
        }

        connection.close();

        return user;
    }

}
