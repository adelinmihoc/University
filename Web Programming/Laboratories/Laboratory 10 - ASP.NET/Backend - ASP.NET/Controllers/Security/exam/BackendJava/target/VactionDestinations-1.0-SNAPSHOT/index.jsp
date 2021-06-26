<%@ page import="model.VacationDestination"%><%@ page import="java.util.List"%><%@ page import="model.VacationDestinationDAO"%>
<%@ page contentType="application/json; charset=UTF-8" pageEncoding="UTF-8" %>
<% response.setHeader("Access-Control-Allow-Headers", "Access-Control-Allow-Origin, Content-Type");%>
<% response.setHeader("Access-Control-Allow-Origin", "*");%>


<%
    List<VacationDestination> destinations = VacationDestinationDAO.getAll();
%>

<%=destinations.toString()%>

