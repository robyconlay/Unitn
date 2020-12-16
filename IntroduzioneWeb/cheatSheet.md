## Pagine utili
 
### w3schools

- How to Bar
- JQuery References
- CSS templates

## JQuery import

<script src="https://code.jquery.com/jquery-3.2.1.min.js"></script>

## signup Page

```css
* {box-sizing: border-box}
.wrapper{margin-left: auto;  margin-right: auto; width: 40%;}
hr{ border: 1px solid #f1f1f1;  margin-bottom: 25px;}
input[type=text], input[type=password]{
    width: 100%; padding: 15px; margin: 5px 0 22px 0; display: inline-block; border: none; background: #f1f1f1; }
button{background-color: #4CAF50; color: white; padding: 14px 20px; margin: 8px 0; border: none; cursor: pointer; width: 100%; opacity: 0.9; }
.cancelbtn {padding: 14px 20px; background-color: #f44336; }
.cancelbtn, .signupbtn{ float: left; width: 50%; }
.container{ padding: 16px; }
.clearfix::after { content: ""; clear: both; display: table; }
@media screen and (max-width: 300px){  .cancelbtn, .signupbtn{ width: 100%; } }
```
```html
<div class="wrapper">
    <div class="mainPage">
        <form action="signup" method="post" style="border: 1px solid #ccc">
            <div class="container">
                <h1>Sign up</h1>
                <p>Please fill in this form to create an account</p>
                <hr>
                <label for="uname"><b>Username</b></label>
                   <input type="text" placeholder="Enter Username" name="uname" required>
                <label for="psw"><b>Password</b></label>
                   <input type="password" placeholder="Enter Password" name="psw" id="psw" required>
                <label for="psw-repeat"><b>Repeat Password</b></label>
                   <input type="password" placeholder="Repeat Password" name="psw-repeat"  id="psw-repeat" required>
                <p id="errorPar" style="color: red; display: none">Passwords do not match</p>
                <label for="email"><b>Email</b></label>
                    <input type="text" placeholder="Enter Email" name="email" required>
                <label>     <input type="checkbox" checked="checked" name="remember" style="margin-bottom: 15px">Remember me</label>
                <p>By creating an account you agree to our <a href="#" style="color:dodgerblue">Terms & Privacy</a>.</p>
                <div class="clearfix">
                    <button type="button" class="cancelbtn">Cancel</button>
                    <button type="submit" class="signupbtn">Sign Up</button>
                </div>
</div>      </form>     </div>      </div>
```
```javascript
<script>
    $(document).ready(function () {
        $("#psw, #psw-repeat").keyup(function () {
            if ($("#psw").val() != $("#psw-repeat").val()) {    //not working lol
                document.getElementById("errorPar").style("display: inline");
                $("#errorPar").css("display: inline");
            }
        })
    });         </script>
```
## loginPage.jsp

```css
    .wrapper{ max-width: 50%;     margin: auto;     width: 50%;     }
    .container{   padding: 16px;    }
    form{    border: 3px solid #f1f1f1;    }
    input[type=text], input[type=password]{
        width: 100%;     padding: 12px 10px; margin: 8px 0; display: inline-block; border: 1px solid #ccc; box-sizing: border-box; }
    button[type=submit]{
        background-color: #4CAF50; color: white; padding: 14px 20px; margin: 8px 0; border: none; cursor: pointer; width: 100%;    }
    .signup{ float: right; margin: 0; padding-top: 5px; }
    a{   text-decoration: none;    }
    a:link, a:visited{  color: black;    }
</style>
```
```html
<div class="wrapper" style="max-width: 600px;">
    <form action="login" method="post">
        <div class="container">
            <p><% String message = (String) session.getAttribute("message");
                 if (message != null && message != "") {out.write(message); } %>
            </p>
            <label for="uname"><b>Username</b></label>
                <input type="text" placeholder="Enter username" name="uname" required>
            <label for="psw"><b>Password</b></label>
                <input type="password" placeholder="Enter password" name="psw" required>
            <button type="submit">Login</button>
            <label>     <input type="checkbox" checked="checked" name="remember">Remember me</label>
            <p class="signup"><a href="signupPage.html">Sign up instead</a></p>
        </div>
    </form>
</div>
```
## Connection to Database (for pretty much every Servlet)

```java
String dbURL = "jdbc:derby://localhost:1527/DerbyDB";
String user = "roberto";
String password = "roberto";
Connection conn = null;
String errorMessage = "";
   
@Override
public void init() throws ServletException {
    try {
        Class.forName("org.apache.derby.jdbc.ClientDriver");
        conn = DriverManager.getConnection(dbURL, user, password);
    } catch (ClassNotFoundException | SQLException ex) {
        ex.printStackTrace();
    }}
@Override
public void destroy() {
    try {
        conn.close();
    } catch (SQLException e) {
        e.printStackTrace();
    }}
```
## LoginServlet.java
```java
@Override
protected void doPost(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
    processRequest(request, response);
    String username = request.getParameter("uname");
    String password = request.getParameter("psw");
    boolean status = false;
        
    try {
        PreparedStatement preparedStatement = conn.prepareStatement("select * from CREDENTIAL where username = ? and password = ? ");
        preparedStatement.setString(1, username);
        preparedStatement.setString(2, password);
        ResultSet rs = preparedStatement.executeQuery();
        status = rs.next();
    } catch (Exception e) {
        errorMessage = "Database Errore, please retry later";
        request.setAttribute("message", errorMessage);
        e.printStackTrace();
    }

    HttpSession session = request.getSession();
    String destPage;
    if (status) {
        destPage = "/showcase.jsp";
        session.setAttribute("username", username);
        session.removeAttribute("message");
            
        String remember = request.getParameter("remember");     //add Cookie if remember checkbox was checked
        if(remember != null && remember == "on"){
            Cookie nameCookie = new Cookie("username", username);
            Cookie passCookie = new Cookie("password", password);
            nameCookie.setMaxAge(60 * 60 * 24 * 365);
            passCookie.setMaxAge(60 * 60 * 24 * 365);
            response.addCookie(nameCookie);
            response.addCookie(passCookie);
        }
    } else {
        errorMessage = "Invalid email/password!";
        destPage = "/loginPage.jsp";    //.html!!
        request.setAttribute("message", errorMessage);
    }
    response.sendRedirect(request.getContextPath() + destPage);
}
```
## SignupServlet.java
```java
@Override
protected void doPost(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
    processRequest(request, response);
    String username = request.getParameter("uname");
    String password = request.getParameter("psw");
    String email = request.getParameter("email");

    System.out.println(username);
    System.out.println(password);
    System.out.println(email);

    HttpSession session = request.getSession();
    session.setAttribute("username", username);
    String destPage = "/showcase.html";
    try {
        PreparedStatement preparedStatement = conn.prepareStatement("INSERT INTO CREDENTIAL VAlUES (?, ?, ?)");
        preparedStatement.setString(1, username);
        preparedStatement.setString(2, password);
        preparedStatement.setString(3, email);
        System.out.println(preparedStatement);
        preparedStatement.execute();
    } catch (SQLIntegrityConstraintViolationException ex) { //for when the account already exists 
        String errorMessage = "There already exists an account with this username or password!";
        request.setAttribute("message", errorMessage);
        destPage = "/signupPage.html";
        session.removeAttribute("username");
    } catch (SQLException e) {
        e.printStackTrace();
    }
    response.sendRedirect(request.getContextPath() + destPage);
}
```
## LogoutServlet.java
```java
protected void processRequest(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
    HttpSession session = request.getSession(false);
    if (session != null) {
        session.removeAttribute("username");
        session.invalidate();
    }
    Cookie cookies[] = request.getCookies(); //if cookies are set
    for (Cookie c : cookies) {
        c.setMaxAge(0);
        response.addCookie(c);
    }
    response.sendRedirect(request.getContextPath() + "/");
}
```
## AuthFilter.java
```java
public void doFilter(ServletRequest request, ServletResponse response,
        FilterChain chain)
        throws IOException, ServletException {
    HttpServletRequest httpRequest = (HttpServletRequest) request;
    HttpSession session = httpRequest.getSession(false);
    
    boolean isLoggedIn = (session != null && session.getAttribute("username") != null);
    String loginURI = httpRequest.getContextPath() + "/login";
    boolean isLoginRequest = httpRequest.getRequestURI().equals(loginURI);
    boolean isLoginPage = httpRequest.getRequestURI().endsWith("/loginPage.jsp"); //.html!!

    String username = null;
    String password = null;

    Cookie cookies[] = httpRequest.getCookies();
    for (Cookie cookie : cookies) {
        if (cookie.getName() == "username") {
            username = cookie.getValue();
        } else if (cookie.getName() == "password") {
            password = cookie.getValue();
        }
    }

    System.out.println("Login Request: " + isLoginRequest);
    System.out.println("Is logged in: " + isLoggedIn);

    if (isLoggedIn && (isLoginRequest || isLoginPage)) {    // the user is already logged in and he's trying to login again     
        httpRequest.getRequestDispatcher("/").forward(request, response); //then forward to the homepage
    } else if (username != null && password != null) {   //use cookies to automatically login
        httpRequest.getRequestDispatcher("/").forward(request, response);
    } else if (!isLoggedIn) {       // the user is not logged in, and the requested page requires       
        String loginPage = "/loginPage.jsp"; // authentication, then forward to the login page
        RequestDispatcher dispatcher = httpRequest.getRequestDispatcher(loginPage); //.html!! line up
        dispatcher.forward(request, response);
    } else {    // for other requested pages that do not require authentication     
        chain.doFilter(request, response); // or the user is already logged in, continue to the destination
    }}
```
## Product.toJSON()
```java
public String toJSON() {
    String template = "{";
    template += " \"id\": " + this.Id;
    template += ", \"name\": \"" + this.name;
    template += "\", \"description\": \"" + this.description;
    template += "\", \"price\": \"" + this.price;
    template += "\", \"imgUrl\": \"" + this.imgUrl;
    template += "\" }";
    System.out.println(template);  
    return template;        
}
```
## prodListToJSON
```java
 public String prodListToJSON(ArrayList<Product> recentProducts) {
        String template = "{";      //array of products
        template += "\"recentProducts\": [";
        for (Product product : recentProducts) {
            template += product.toJSON() + ", ";
        }
        template += "]}";
        System.out.println(template);
        return template;
    }
```
## RecentlySeen
```java
@Override
protected void doGet(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
   HttpSession session = request.getSession(false);
     
   ArrayList<Product> recentProductList = (ArrayList<Product>) session.getAttribute("recentProducts");
   System.out.println(recentProductList);
       
   String productJSON = prodListToJSON(recentProductList);
   response.setContentType("application/json");
   response.setCharacterEncoding("utf-8");
       
   PrintWriter out = response.getWriter();
   out.write(productJSON); //returns the JSON to the ajax function
}
```
## Ajax
```javascript
function loadDoc() {
  var xhttp = new XMLHttpRequest();
  xhttp.responseType = "json";
  xhttp.open("get", "demo_post.asp", true);
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("demo").innerHTML = this.responseText;
      //modify this 
    }
  };
  xhttp.send();
} 
```
## JSP init
```java
<%!
    String dbURL = "jdbc:derby://localhost:1527/DerbyDB";
    String user = "roberto";
    String password = "roberto";
    Connection conn = null;

    ArrayList<Product> productList = new ArrayList<>(); //list for the products shown

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
    }%>
```
