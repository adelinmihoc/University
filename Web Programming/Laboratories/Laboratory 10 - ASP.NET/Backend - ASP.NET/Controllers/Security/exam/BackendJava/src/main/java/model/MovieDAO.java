package model;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class MovieDAO {
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

    public static List<Movie> getAllFiltered(String username) {
        List<Movie> list = new ArrayList<>();
        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "select d.id, d.title, d.duration from Movies d " +
                            "inner join Authors a " +
                            "on a.movieList like concat('%', d.id, '%') " +
                            "where a.name = ?");
            preparedStatement.setString(1, username);
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Movie movie = new Movie();

                movie.setId(resultSet.getInt("id"));
                movie.setTitle(resultSet.getString("title"));
                movie.setDuration(resultSet.getInt("duration"));

                list.add(movie);
            }

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        return list;
    }
}
