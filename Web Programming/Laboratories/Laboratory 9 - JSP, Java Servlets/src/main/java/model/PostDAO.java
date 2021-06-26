package model;

import java.sql.*;
import java.util.ArrayList;
import java.util.Base64;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class PostDAO {

    public static Connection getConnection() {
        final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        final String DB_URL = "jdbc:mysql://localhost:3306/pw_lab8";
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

    public static boolean okayToLike(Integer user_id, Integer post_id) {
        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement;

            preparedStatement = connection
                    .prepareStatement("select * from user_post where user_id = ? and post_id = ?");
            preparedStatement.setInt(1, user_id);
            preparedStatement.setInt(2, post_id);
            ResultSet resultSet = preparedStatement.executeQuery();
            return !resultSet.next();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
            return false;
        }
    }

    public static boolean addVote(Integer user_id, Integer post_id, Integer vote) {
        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement;

            preparedStatement = connection
                    .prepareStatement("select * from user_post where user_id = ? and post_id = ?");
            preparedStatement.setInt(1, user_id);
            preparedStatement.setInt(2, post_id);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return false;
            }
            preparedStatement = connection
                    .prepareStatement("update post set votes = post.votes + ? where id= ?");
            preparedStatement.setInt(1, vote);
            preparedStatement.setInt(2, post_id);
            preparedStatement.executeUpdate();

            preparedStatement = connection
                    .prepareStatement("insert into user_post values (?, ?)");
            preparedStatement.setInt(1, user_id);
            preparedStatement.setInt(2, post_id);
            preparedStatement.executeUpdate();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        return true;
    }

    public static List<Post> getAllPosts() {
        List<Post> list = new ArrayList<>();

        try {
            Connection connection = getConnection();
            PreparedStatement preparedStatement = connection.prepareStatement("select * from post");
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Post post = new Post();
                post.setId(resultSet.getInt("id"));
                post.setUser_id(resultSet.getInt("user_id"));
                Blob image = resultSet.getBlob("image");
                post.setImage(image.getBytes(1, (int)image.length()));
                post.setVotes(resultSet.getInt("votes"));

                String base64Image = Base64.getEncoder().encodeToString(image.getBytes(1, (int)image.length()));

                post.setBase64Image(base64Image);

                list.add(post);
            }

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }


        return list.stream()
                .sorted(Comparator.comparingInt(Post::getVotes).reversed())
                .collect(Collectors.toList());
    }

}
