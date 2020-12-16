/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package it.unitn.studenti.robertomazzalai;

import java.io.IOException;
import java.util.Random;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 *
 * @author rob
 */
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
        log("exit");

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
        processRequest(request, response);
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
