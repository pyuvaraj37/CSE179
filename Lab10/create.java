
import java.io.*;

public class create {
	
	public static void main(String[] args) {
		
		randomgraph a = new randomgraph(100, 50, -1);
		a.display();

		try {
			FileOutputStream file = new FileOutputStream("graph.txt");

			for(int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {

					file.write(a.edgeLength(i, j));


				}
			}

			file.close();
			
		} catch(IOException e) {
			System.out.println("Error - " + e.toString());
		}

	}

}