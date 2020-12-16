

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <title>Login to our website</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">

        <style>
            .wrapper{
                max-width: 50%;
                margin: auto;
                width: 50%; /* move this up*/
            }
            .container{
                padding: 16px;
            }
            form{
                border: 3px solid #f1f1f1;
            }
            input[type=text], input[type=password]{
                width: 100%;
                padding: 12px 10px;
                margin: 8px 0;
                display: inline-block;
                border: 1px solid #ccc;
                box-sizing: border-box;
            }
            button[type=submit]{
                background-color: #4CAF50;
                color: white;
                padding: 14px 20px;
                margin: 8px 0;
                border: none;
                cursor: pointer;
                width: 100%;
            }
            .signup{
                float: right;
                margin: 0;
                padding-top: 5px;
            }
            a{
                text-decoration: none;
            }
            a:link{
            }
            a:visited{
                color: black;
            }
            .dark-mode{
                background-color: black;
                color: white;
            }
            footer{
                position: fixed;
                bottom: 0;
                left: 0;
                width: 100%;
                border: 1px solid black;
                margin: 0;
                padding: 0;
                background-color: #f1f1f1;
            }
            .darkbtn{
                padding: 10px;
                margin: 20px;
                background-color: black;
                border: 1px solid black;
                color: white;
            }
        </style>
    </head>
    <body>
        <div class="wrapper" style="max-width: 600px;">

            <form action="login" method="post">
                <div class="container">
                    <p>
                        <% String message = (String) session.getAttribute("message");
                        log(message);
                            if (message != null && message != "") {
                                out.write(message);
                            }
                        %>
                    </p>
                    <label for="uname"><b>Username</b></label>
                    <input type="text" placeholder="Enter username" name="uname" required>

                    <label for="psw"><b>Password</b></label>
                    <input type="password" placeholder="Enter password" name="psw" required>

                    <button type="submit">Login</button>
                    <label>
                        <input type="checkbox" checked="checked" name="remember">Remember me
                    </label>
                    <p class="signup"><a href="signupPage.html">Sign up instead</a></p>
                </div>
            </form>
        </div>
        <footer>
            <button class="darkbtn" onclick="console.log('pressed');">Change to dark mode</button>
        </footer>
        <script src="https://code.jquery.com/jquery-3.2.1.min.js"></script>
    </body>
</html>
