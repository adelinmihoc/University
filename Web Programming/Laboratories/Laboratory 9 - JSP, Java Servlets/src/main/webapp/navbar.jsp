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

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>

<ul>
    <li><a href="login.jsp">Login</a></li>
    <li><a href="LogoutController">Logout</a></li>
    <li><a href="home.jsp">Home</a></li>
    <div class="profileWrapper">${user.name} (${user.username})</div>
</ul>

</body>
</html>
