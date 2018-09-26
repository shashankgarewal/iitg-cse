/*
java Client ClientThread. Item. Order.
*/

import java.util.*;
import java.net.*;
import java.io.*;

public class Client{
	Socket clientSkt;
	ClientThread clientThread;
	public static ArrayList<Order> orderList = new ArrayList<>();
	public static ArrayList<Item> menu = new ArrayList<>();

	public static void main(String[] args) {

		orderList.add(new Order("coffee", 2) );
		orderList.add(new Order("tea", 0) );
		orderList.add(new Order("snacks", 1) );
		orderList.add(new Order("food", 3) );
		orderList.add(new Order("paratha", 0) );

		new Client();
		ListenForInput();
	}

	public Client(){
		try{
			clientSkt = new Socket("127.0.0.1", 5000);
			ClientThread clientThread = new ClientThread(clientSkt, this);
			clientThread.start();
		}
		catch(IOException e){
			e.printStackTrace();
		}
	}

	public static void ListenForInput(){
		Scanner console = new Scanner(System.in);

		while(true){
			while(!console.hasNextLine()){
				try{
					Thread.sleep(1);
				}
				catch(InterruptedException e){
					e.printStackTrace();
				}
			}

			String input = console.nextLine();

			if(input.toLowerCase().equals("quit"))
				break;
		}
	}
}