## index.html
```html
<html>
    <head>
        <title>Welcome to Minesweeper</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
    </head>
    <body>
        <form action="start" method="get">
            <label for="username">Hi, what's your name?</label>
            <input type="text" name="username">
            <button type="submit">Start new game</button>
        </form>
    </body>
</html>
```
## startServlet.java
```java
@WebServlet(name = "StartServlet", urlPatterns = {"/start"})
public class StartServlet extends HttpServlet {

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession();

        String username = request.getParameter("username");
        if (username == null || username == "") {
            username = (String) session.getAttribute("username");
            if (username == null || username == "") {
                response.sendRedirect(request.getContextPath() + "/index.html");
            }
        }

        session.setAttribute("username", username);

        //matrix init
        int field[][] = new int[9][9];
        int bombs = 10;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                field[i][j] = 0;
            }
        }

        while (bombs > 0) {
            int x = new Random().nextInt(9);
            int y = new Random().nextInt(9);
            if (field[x][y] != -1) {
                field[x][y] = -1;
                bombs--;
            }
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (field[i][j] != -1) {
                    field[i][j] = countNear(field, i, j);
                }
            }
        }
        session.removeAttribute("field");
        session.setAttribute("field", field);

        response.sendRedirect(request.getContextPath() + "/game.jsp");
    }

    public int countNear(int[][] field, int x, int y) {
        int counter = 0;
        for (int i = -1; i <= 1; i++) {
            if (x + i >= 0 && x + i < 9) {
                for (int j = -1; j <= 1; j++) {
                    log((x + i) + " " + (y + j));
                    if ((!(x == 0 && j == 0)) && y + j >= 0 && y + j < 9 && field[x + i][y + j] == -1) {

                        counter++;
                    }
                }
            }
        }
        return counter;
    }
```
## game.jsp
```html
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
        <div id="popup">
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
            function init() {
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
            function getValue(i, j) {
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
            function reveal() {
                for (var i = 0; i < 9; i++) {
                    for (var j = 0; j < 9; j++) {
                        getValue(i, j);
                    }
                }
            }
        </script>
    </body>
</html>
```
## valueServlet.java
```java
 protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        int i = Integer.parseInt(request.getParameter("i"));
        int j = Integer.parseInt(request.getParameter("j"));
        HttpSession session = request.getSession(false);
        int[][] field = (int[][]) session.getAttribute("field");
        
        PrintWriter out = response.getWriter();
        out.write("{\"id\" : " + field[i][j] + " }");
        log("" + field[i][j]);
    }
```