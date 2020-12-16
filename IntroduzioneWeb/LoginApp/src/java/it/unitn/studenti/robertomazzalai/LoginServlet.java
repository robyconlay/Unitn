/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package it.unitn.studenti.robertomazzalai;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 *
 * @author rob
 */
@WebServlet(name = "LoginServlet", urlPatterns = {"/login"})
public class LoginServlet extends HttpServlet {

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
        }
    }

    @Override
    public void destroy() {
        try {
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

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
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.sendRedirect(request.getContextPath() + "/");
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
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
            request.getSession(false).setAttribute("message", errorMessage);
            e.printStackTrace();
        }

        String destPage;
        if (status) {
            destPage = "/showcase.jsp";
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            session.removeAttribute("message");
            
            //add Cookie if remember checkbox was checked
            String remember = request.getParameter("remember");
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
            destPage = "/loginPage.jsp";
            request.getSession(false).setAttribute("message", errorMessage);
        }
        response.sendRedirect(request.getContextPath() + destPage);

    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
