<%-- 
    Document   : showcase
    Created on : Jun 26, 2020, 2:36:05 PM
    Author     : rob
--%>

<%@page import="java.sql.ResultSet"%>
<%@page import="java.sql.Statement"%>
<%@page import="java.util.ArrayList"%>
<%@page import="java.sql.DriverManager"%>
<%@page import="it.unitn.studenti.robertomazzalai.Product"%>
<%@page import="java.sql.Connection"%>
<%@page import="java.sql.SQLException"%>
<%!
    String dbURL = "jdbc:derby://localhost:1527/DerbyDB";
    String user = "roberto";
    String password = "roberto";
    Connection conn = null;

    ArrayList<Product> productList = new ArrayList<>();

    public void jspInit() {
        try {
            Class.forName("org.apache.derby.jdbc.ClientDriver");
            conn = DriverManager.getConnection(dbURL, user, password);
            log("init");
        } catch (ClassNotFoundException | SQLException ex) {
            ex.printStackTrace();
        }

        try {
            Statement stmt = conn.createStatement();
            String sql = "SELECT * FROM products ORDER by id FETCH FIRST 15 ROWS ONLY";
            ResultSet rs = stmt.executeQuery(sql);
            while (rs.next()) {
                Product product = new Product(rs.getInt("id"), rs.getString("name"), rs.getString("description"), rs.getString("price"), rs.getString("imgURL"));
                productList.add(product);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void jspDestroy() {
        try {
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Showcase</title>
        <script type="text/javascript" src=""></script>
        <style>
            .top{
                width: 100%;
                height: 30px;
                padding: 20px 0;
                margin-bottom: 20px;
                background-color: blue;
            }
            .logoutbtn{
                padding: 10px 20px 10px 20px;
                margin: 5px;
                margin-top: 0;
                margin-right: 100px;
                background-color: red;
                float: right;
                border: none;
                border-radius: 10px;
            }
            .sidebar{
                float: left;
                display: flex;
                flex-direction: column;
                width: 20vw;
            }
            .card{
                border: 1px solid black;
                width: 100%;
                padding: 10px;
                margin: 0;
                height: 20vh;
                border-radius: 5px;
                max-width: 30vw;
            }
            .main{
                margin-left: 10vw;
                margin-right:  auto;
            }
            .recently-seen{
                display: flex;
                flex-flow: row;
            }
            .container{
                float: left;
                margin-left: 5vw;
            }
        </style>
    </head>
    <body>
        <div class="top">
            <form action="./logout">
                <button type="submit" class="logoutbtn">Logout</button>
            </form>
        </div>


        <!-- sidebar -->
        <div class="sidebar">
            <%log("for");
                for (Product product : productList) {%>
            <div class="card" id="product-preview-<%=product.getId()%>" onclick="displayProduct(<%= product.getId()%>)">
                <span><%= product.getName()%></span>
                <p><i><%= product.getPrice()%></i></p>
                <p><%= product.getDescription()%></p>
            </div>
            <% }%>
        </div>
        <div class="container">
            <div class="main" id="main">

            </div>

            <div class="recently-seen" id="recent">

            </div>
        </div>

        <script>

            function displayRecentlySeen() {
                let productJSON;
                var xhttp = new XMLHttpRequest();
                xhttp.responseType = "json";
                xhttp.open("get", "./recentlySeen", true);
                xhttp.onreadystatechange = function () {
                    if (this.readyState == 4 && this.status == 200) {
                        productJSON = this.response;
                        console.log(productJSON.recentProducts);

                        document.getElementById("recent").innerHTML = "";
                        productJSON.recentProducts.forEach((product) =>
                        {
                            console.log(product);
                            document.getElementById("recent").innerHTML += `
                                <div class="card" id="recentProd-` + product.id + `">
                                    ` + product.name + `
                                </div> `;
                            console.log(document.getElementById("recent").innerHTML);
                        });
                    }
                }
                xhttp.send();
            }

            function displayProduct(id) {
                let productJSON;
                let product;
                var xhttp = new XMLHttpRequest();
                xhttp.responseType = "json";
                xhttp.open("get", "./product?id=" + id, true);
                xhttp.onreadystatechange = function () {
                    if (this.readyState == 4 && this.status == 200) {
                        productJSON = this.response;
                        //product = JSON.parse(this.response);
                        console.log(productJSON);
                        document.getElementById("main").innerHTML = `
                        <div class="card" id="product-` + productJSON.id + `">
                            <span>` + productJSON.name + `</span>
                            <p><i>` + productJSON.price + `</i></p>
                            <p>` + productJSON.description + `</p>
                        </div>`;
                        displayRecentlySeen();
                    }
                }
                xhttp.send();
            }
        </script>
    </body>
</html>
