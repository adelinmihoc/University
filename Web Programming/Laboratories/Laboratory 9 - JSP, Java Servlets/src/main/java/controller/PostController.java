package controller;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

@MultipartConfig(maxFileSize = 16177215)
public class PostController extends HttpServlet {
    private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/pw_lab8";
    private static final String dbUsername = "root";
    private static final String dbPassword = "adelin123";

    public PostController() {
        super();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        int numberOfPosts = Integer.parseInt(request.getParameter("numberOfPosts"));
        request.getSession().setAttribute("top", numberOfPosts);
        RequestDispatcher dispatcher = request.getRequestDispatcher("home.jsp");
        dispatcher.forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        int user_id = Integer.parseInt(request.getParameter("user_id"));

        InputStream inputStream = null; // for upload file
        Part filePart = request.getPart("photo");
        if (filePart != null) {
            inputStream = filePart.getInputStream();
        }

        Connection connection = null;
        String message = null;

        try {
            Class.forName(JDBC_DRIVER);
            connection = DriverManager.getConnection(DB_URL, dbUsername, dbPassword);

            String sql = "insert into post(user_id, image, votes) values (?, ?, 0)";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setInt(1, user_id);
            if (inputStream != null) {
                statement.setBlob(2, inputStream);
            }

            int row = statement.executeUpdate();
            if (row > 0) {
                message = "File uploaded and saved into database";
            }

        } catch (SQLException | ClassNotFoundException throwables) {
            throwables.printStackTrace();
        } finally {
            if (connection != null) {
                try {
                    connection.close();
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }
            }
            request.setAttribute("Message", message);
            getServletContext().getRequestDispatcher("/Message.jsp").forward(request, response);
        }
    }
}
