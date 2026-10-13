import java.awt.*;
import java.awt.image.BufferedImage;
import javax.swing.*;

class Lienzo extends JPanel {
	BufferedImage img;
	Graphics2D g2;

	Lienzo(int w, int h) {
		img = new BufferedImage(w, h, BufferedImage.TYPE_INT_RGB);
		g2 = img.createGraphics();
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g2.setStroke(new BasicStroke(2f));
		setPreferredSize(new Dimension(w, h));
		setBackground(Color.white);
		limpia();
	}

	Graphics grafico() {
		return g2;
	}

	void limpia() {
		g2.setColor(Color.white);
		g2.fillRect(0, 0, img.getWidth(), img.getHeight());
		g2.setColor(Color.black);
		repaint();
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawImage(img, 0, 0, this);
	}
}
