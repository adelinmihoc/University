package controller;

import model.PostDAO;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class VoteController extends HttpServlet {
    public VoteController() {
        super();
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        int post_id = Integer.parseInt(request.getParameter("post_id"));
        int user_id = Integer.parseInt(request.getParameter("user_id"));
        int vote = Integer.parseInt(request.getParameter("vote"));
        boolean status =  PostDAO.addVote(user_id, post_id, vote);
        if (!status) {
            String message = "already liked";
            request.getSession().setAttribute("message", message);
            response.sendRedirect("home.jsp");
        } else {
            String message = "liked!";
            request.getSession().setAttribute("message", message);
            RequestDispatcher dispatcher = request.getRequestDispatcher("home.jsp");
            dispatcher.forward(request, response);
        }
    }
}
