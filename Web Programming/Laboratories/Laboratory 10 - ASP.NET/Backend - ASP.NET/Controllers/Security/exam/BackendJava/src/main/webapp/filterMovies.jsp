<%@ page import="java.util.stream.Collectors"%><%@ page import="com.fasterxml.jackson.databind.ObjectMapper"%>
<%@ page import="java.util.Map"%>
<%@ page import="model.*"%>
<% response.setHeader("Access-Control-Allow-Headers", "Access-Control-Allow-Origin, Content-Type");%>
<% response.setHeader("Access-Control-Allow-Origin", "*");%>
<%@ page contentType="application/json; charset=UTF-8" pageEncoding="UTF-8" %>


<%
    String json = request.getReader().lines().collect(Collectors.joining(System.lineSeparator()));
    ObjectMapper mapper = new ObjectMapper();
    UsernameDTO obj = mapper.readValue(json.toString(), UsernameDTO.class);
    out.print(MovieDAO.getAllFiltered(obj.getUsername()).toString());
%>
