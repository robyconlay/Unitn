<%-- 
    Document   : game
    Created on : Jun 30, 2020, 8:25:26 PM
    Author     : rob
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Minesweeper</title>

        <style> 
            table{
                height: 500px;
                width: 500px;
                border: 1px solid black;
                border-collapse: collapse;
            }
            td{
                width: 50px;
                height: 50px;
                border: 1px solid black;
                text-align: center;
                background-color: gray;
            }
            #popup{
                display: none;
                position: fixed;
                z-index: 1;
                height: 100%;
                width: 100%;
                top: 0;
                left: 0;
                overflow: auto;
            }
            .content{
                background-color: #fefefe;
                margin: 15% auto;
                padding: 20px;
                border: 1px solid #888;
                width: 40%;
                display: inline-block;
            }
            button{
                width: auto;
                margin: 10px;
                padding: 10px;
                background-color: white;
            }
            select{
                width: 40px;
                height: 40px;
                margin: 10px;
            }
        </style>
    </head>
    <body>
        <div id="popup">   <!-- not working properly -->
            <form method="get" action="start" class="content">
                <span>Hai perso</span>
                <button type="submit" style="float:right; clear: both;">Restart</button>
            </form>
        </div>
        <h1>
            Hi
            <% if (session.getAttribute("username") != null) {
                    out.print(session.getAttribute("username"));
                }
            %>
        </h1>
        <table class="field" id="field">

        </table>

        <button onclick='getValue(document.getElementById("row").value, document.getElementById("col").value)'>Test</button>
        <select id="row"></select>
        <select id="col"></select>
        <form method="get" action="start">
            <button type="submit">Restart</button>
        </form>
        <button onclick="reveal()">Reveal all</button>


        <script>
    
            function init() {       //generation of the field
                var field = '';
                for (var i = 0; i < 9; i++) {
                    field += '<tr>';
                    for (var j = 0; j < 9; j++) {
                        field += '<td id="' + i + "-" + j + '" onclick="getValue(' + i + ',' + j + ')"></td>';
                    }
                    field += "</tr>";
                }

                document.getElementById("field").innerHTML = field;
                var options = "";
                for (var i = 0; i < 9; i++) {
                    options += '<option value="' + i + '">' + (i + 1) + '</option>';
                }
                document.getElementById("row").innerHTML = options;
                document.getElementById("col").innerHTML = options;
            }
            init();


            function getValue(i, j) {   //asynchronous function 
                if (document.getElementById(i + "-" + j).innerHTML == "") {
                    let valueJSON;
                    var xhttp = new XMLHttpRequest();
                    xhttp.responseType = "json";
                    xhttp.open("get", "value?i=" + i + "&j=" + j, true);
                    xhttp.onreadystatechange = function () {
                        if (this.readyState == 4 && this.status == 200) {
                            valueJSON = this.response;
                            document.getElementById(i + "-" + j).innerHTML = valueJSON.id;
                            if (valueJSON.id == -1) {
                                document.getElementById(i + "-" + j).style.background = "red";
                                document.getElementById("popup").style.display = "block";
                            } else {
                                document.getElementById(i + "-" + j).style.background = "lime";
                            }
                        }
                    }
                    xhttp.send();
                }
            }

            function reveal() {     //reveal all cells by calling getValue on each one
                for (var i = 0; i < 9; i++) {
                    for (var j = 0; j < 9; j++) {
                        getValue(i, j);
                    }
                }
            }

        </script>
    </body>
</html>
