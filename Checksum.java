import java.util.Scanner;
import java.util.LinkedList;
import java.util.Iterator;

public class Checksum{
	public static void main (String[] args){

		Scanner scan= new Scanner(System.in);
		String s=scan.next();
		Scanner scanner = new Scanner(s);

		LinkedList<String> lineList = new LinkedList<String>();

		while (scanner.hasNext()){
			lineList.add(scanner.nextLine());
		}

		Iterator<String> iterator = lineList.iterator();

		while (iterator.hasNext()) {
			short checksum = fletcher16_opt(iterator.next().getBytes());
			// Bitmask short to int
			System.out.println(Integer.toHexString(checksum & 0xffff));
	}
	}
	private static short fletcher16(byte[] data){
		short sum1 = 0;
		short sum2 = 0;
		short modulus = 255;

		for (int i = 0; i < data.length; i++){
			sum1 = (short) ((sum1 + data[i]) % modulus);
			sum2 = (short) ((sum2 + sum1) % modulus);
		}
		return (short) ((sum2 << 8) | sum1);
	}
	private static short fletcher16_opt(byte[] data)
	{
		int length = data.length;
		short sum1 = 0xff;
		short sum2 = 0xff;
		int i = 0;

		while (length > 0) {
			int tlen = (length > 20) ? 20 : length;
			length -= tlen;
			do {
				sum2 += sum1 += data[i];
				i++;
			} while ((--tlen) > 0);
			sum1 = (short) ((sum1 & 0xff) + (sum1 >> 8));
			sum2 = (short) ((sum2 & 0xff) + (sum2 >> 8));
		}
		sum1 = (short) ((sum1 & 0xff) + (sum1 >> 8));
		sum2 = (short) ((sum2 & 0xff) + (sum2 >> 8));
		return (short) (sum2 << 8 | sum1);
	}
}
