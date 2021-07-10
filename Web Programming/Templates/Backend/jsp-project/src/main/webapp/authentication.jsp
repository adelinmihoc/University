<%@ page import="java.util.stream.Collectors"%>
<%@ page import="com.fasterxml.jackson.databind.ObjectMapper"%>
<%@ page import="Model.Entity"%>
<%@ page import="Model.DbUtil"%>
<% response.setHeader("Access-Control-Allow-Headers", "Access-Control-Allow-Origin, Content-Type");%>
<% response.setHeader("Access-Control-Allow-Origin", "*");%>
<%@ page contentType="application/json; charset=UTF-8" pageEncoding="UTF-8" %>


<%
    String json = request.getReader().lines().collect(Collectors.joining(System.lineSeparator()));
    ObjectMapper mapper = new ObjectMapper();
    Entity obj = mapper.readValue(json.toString(), Entity.class);
    Entity entity = DbUtil.authenticate(obj);
    if (entity != null) {
        out.print(entity.toString());
    } else {
        response.sendError(404, "Not Found");
    }
%>