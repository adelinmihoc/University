<%@ page import="model.User" %>
<%@ page import="java.sql.*" %>
<%@ page import="java.io.OutputStream" %>
<%@ page import="model.Post" %>
<%@ page import="java.util.List" %>
<%@ page import="model.PostDAO" %>
<%@ page import="model.UserDAO" %>
<%@ page import="jdk.internal.util.xml.impl.Pair" %>
<%@ page isELIgnored="false" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>


<%--
  Created by IntelliJ IDEA.
  User: adeli
  Date: 5/19/2021
  Time: 10:38 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Home</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <%@ include file="navbar.jsp"%>

    <div style="text-align: center">
        <h1>System for image voting</h1>
        <%
//            session = request.getSession(false);
            if (session != null) {
            User user = (User) session.getAttribute("user");

            if (user != null) {
            } else {
                out.print("Please login first");
                response.sendRedirect("login.jsp");
            }
        } else {
            out.print("Please login first");
            response.sendRedirect("login.jsp");
        } %>
        <br><br>
    </div>

    <h1>System for image voting</h1>


    <div class="fileUploadWrapper">
        <h3>File uploading</h3>
        select file to upload: <br />
        <form action="PostController" method="post" enctype="multipart/form-data" >
            <input type="hidden" name="user_id" value="${user.id}">
            <input type="file" name="photo" size="50"  accept=".jpg"/>
            <br />
            <input type="submit" value="Upload file" />
        </form>
    </div>
    <hr>

    <%
        List<Post> posts = PostDAO.getAllPosts();
        request.setAttribute("posts", posts);
    %>

    <div style="text-align: center" class="mainWrapper">
        <form action="PostController" method="get">
            <label>Top N photos:
                <input type="number" name="numberOfPosts" size="50" id="numberOfPosts" min="0" />
            </label>
        </form>
        <h1>Top ${top} images</h1>
        <c:forEach items="${posts}" var="post">
            <c:if test="${top != null}">
                <c:if test="${posts.indexOf(post) < top}">
                    <div class="postWrapper">
                        <br/>
                        <img src="data:image/jpg;base64,${post.base64Image}" alt="" width="800px"/>
                        <br/>
                        <b>Votes: ${post.votes} | </b>
                        <b>Author name: ${UserDAO.getUserById(post.user_id).name}</b>
                        <br/>
                        <c:if test="${user.id != null}">
                        <c:if test="${user.id != post.user_id and PostDAO.okayToLike(user.id, post.id)}">
                        <form action="VoteController" method="post">
                            <input type="hidden" name="post_id" value="${post.id}">
                            <input type="hidden" name="user_id" value="${user.id}">
                            <label> add vote:
                                <input type="number" name="vote" size="50" min="0" max="10" />
                            </label>
                            <br />
                                <input type="submit" value="submit vote" />
                            <p>${message}</p>
                            <c:remove var="message" scope="session" />
                        </form>
                        </c:if>
                        </c:if>
                    </div>
                    <hr>
                </c:if>
            </c:if>
        </c:forEach>
    </div>
</body>
</html>
