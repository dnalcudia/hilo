import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Conexion {
    Connection conn = null;
    Statement st = null;
    String url = "jdbc:mysql://sql12.freesqldatabase.com:3306/sql12289990";
    String us = "sql12289990";
    String pass = "qi3g9i7h5N";
    
    public void conecting(){
    try{
        try {
            Class.forName("com.mysql.jdbc.Driver");
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(Conexion.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            conn = (Connection)DriverManager.getConnection(url,us,pass);
        } catch (SQLException ex) {
            Logger.getLogger(Conexion.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            st = conn.createStatement();
        } catch (SQLException ex) {
            Logger.getLogger(Conexion.class.getName()).log(Level.SEVERE, null, ex);
        }
    System.out.println("Conexion en línea");
} catch(Exception e){
    System.out.println("Error de conexión");
}    
}
}
