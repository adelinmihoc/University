<%@ page import="Model.DbUtil"%>
<% response.setHeader("Access-Control-Allow-Headers", "Access-Control-Allow-Origin, Content-Type");%>
<% response.setHeader("Access-Control-Allow-Origin", "*");%>
<%@ page contentType="application/json; charset=UTF-8" pageEncoding="UTF-8" %>


<%
    out.print(DbUtil.getAll().toString());
%>
