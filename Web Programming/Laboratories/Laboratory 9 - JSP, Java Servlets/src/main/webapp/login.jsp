<%--
  Created by IntelliJ IDEA.
  User: adeli
  Date: 5/19/2021
  Time: 10:30 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Login</title>
    <script
            src="https://code.jquery.com/jquery-3.4.1.min.js"
            integrity="sha256-CSXorXvZcTkaix6Yvo6HppcZGetbYMGWSFlBw8HfCJo="
            crossorigin="anonymous"></script>
    <script type="text/javascript"
            src="https://cdn.jsdelivr.net/npm/jquery-validation@1.19.0/dist/jquery.validate.min.js"></script>
</head>
<body>
<div style="text-align: center">
    <h1>Admin Login</h1>
    <form id="loginForm" action="LoginController" method="post">
        <label>Username:
            <input name="username" size="30" />
        </label>
        <br><br>
        <label>Password
            <input type="password" name="password" size="30" />
        </label>
        <br>${message}
        <br><br>
        <button type="submit">Login</button>
    </form>
</div>

</body>
<script type="text/javascript">

    $('document').ready(function() {
        $("#loginForm").validate({
            rules: {
                username: {
                    required: true,
                },
                password: "required",
            },

            messages: {
                username: {
                    required: "Please enter username",
                },
                password: "Please enter password"
            }
        });
    });
</script>
</html>
