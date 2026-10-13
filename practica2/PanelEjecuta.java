import java.awt.*;
import java.awt.event.*;
import javax.swing.event.*;
import javax.swing.*;
import java.util.StringTokenizer;

public class PanelEjecuta extends JPanel {
   private Maquina maq;
   private Parser par;
   private boolean newline;
   private String etiqs[]={"Ejecuta", "Limpia"};
   private Paleta paleta;
   static JTextArea cmd;
   public PanelEjecuta(Maquina maq, Parser par){
      this.maq=maq; this.par=par;
      setLayout(new GridLayout(2,1));
      cmd = new JTextArea(3, 40);   
      JScrollPane qScroller = new JScrollPane(cmd);
      add(qScroller);
      paleta=new Paleta(etiqs,new GridLayout(etiqs.length, 1), new ManejaAccionInt()); 
      add(paleta);
   }
   public void ejecutaTexto(String texto){
      cmd.setText(texto);
      lanzar();
   }
   void lanzar(){
      String limpio = sinComentarios(cmd.getText());
      par.setTokenizer(new StringTokenizer(limpio));
      par.setNewline(false);
      for(maq.initcode(); par.yyparse ()!=0; maq.initcode())
         maq.execute(maq.progbase);
      if (Parser.lienzo != null) Parser.lienzo.repaint();
   }
   static String sinComentarios(String texto){
      StringBuilder sb = new StringBuilder();
      for (String linea : texto.split("\n", -1)) {
         int i = linea.indexOf("//");
         if (i >= 0) linea = linea.substring(0, i);
         sb.append(linea).append('\n');
      }
      return sb.toString();
   }
   class ManejaAccionInt implements AccionInt {
      public void accion(int n, ActionEvent e){ 
         //System.out.println("accion");
	 if(n==0){ 
            if (Parser.lienzo != null) Parser.lienzo.limpia();
            lanzar();
         }
         if(n==1){
            cmd.setText("");
            if (Parser.lienzo != null) Parser.lienzo.limpia();
        }
     }
   }
}
