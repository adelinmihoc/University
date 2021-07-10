package Model;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DbUtil {
    public static Connection getConnection() {
        final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        final String DB_URL = "jdbc:mysql://localhost:3306/exam";
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

    public static List<Entity> getAll() {
        List<Entity> list = new ArrayList<>();
        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "select * from movies;");
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Entity entity = new Entity();
                entity.id = resultSet.getInt("id");
                entity.title = resultSet.getString("title");
                entity.genre = resultSet.getString("genre");

                list.add(entity);
            }

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        return list;
    }

    public static List<Entity> getAllFiltered(Entity body) {
        List<Entity> list = new ArrayList<>();
        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "select * from files f where f.userid = (select id from users where username= ?);");
            preparedStatement.setString(1, body.username);
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Entity entity = new Entity();
                entity.id = resultSet.getInt("id");
//                entity.userid = resultSet.getInt("userid");
//                entity.filename = resultSet.getString("filename");
//                entity.filepath = resultSet.getString("filepath");
//                entity.size = resultSet.getInt("size");

                list.add(entity);
            }

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        return list;
    }

    public static Entity authenticate(Entity body) {
        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "select * from users where username = ? and password = ?;");
            preparedStatement.setString(1, body.username);
            preparedStatement.setString(2, body.password);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                Entity entity = new Entity();
                entity.username = resultSet.getString("username");
                entity.password = resultSet.getString("password");
                return entity;
            }

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        return null;
    }

    public static void registration(Entity body) {
        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "insert ignore into users(username, password) values (?, ?);");
            preparedStatement.setString(1, body.username);
            preparedStatement.setString(2, body.password);
            preparedStatement.executeUpdate();

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
    }

    public static void add(Entity body) {
        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "insert into movies(title, genre) values (?, ?);");
            preparedStatement.setString(1, body.title);
            preparedStatement.setString(2, body.genre);

            preparedStatement.executeUpdate();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
    }

    public static void delete(Entity body) {
        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "delete from movies where id = ?;");
            preparedStatement.setInt(1, body.id);
            preparedStatement.executeUpdate();

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
    }

    public static void update(Entity body) {
        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "update movies set title = ?, genre = ? where id = ?;");
            preparedStatement.setString(1, body.title);
            preparedStatement.setString(2, body.genre);
            preparedStatement.setInt(3, body.id);
            preparedStatement.executeUpdate();

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
    }

}
