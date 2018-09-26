/*
java Server ServerThread. Item. Order.
*/

// Server to handle accepting connection

import java.util.*;
import java.net.*;
import java.io.*;

public class Server{
	ServerSocket serverSkt;
	Socket clientSkt;
	boolean run = true;
	public static ArrayList<ServerThread> threads = new ArrayList<>();
	public static ArrayList<Order> orderList = new ArrayList<>();
	public static ArrayList<Item> menu = new ArrayList<>();

	public Server(){
		try{
			serverSkt = new ServerSocket(5000);
			while(run){
				clientSkt = serverSkt.accept();
				ServerThread serverThread = new ServerThread(clientSkt, this);
				serverThread.start();	
				threads.add(serverThread);
			}
		}
		catch(IOException e){
			e.printStackTrace();
		}
	}

	public static void main(String[] args) throws IOException{
		menu.add(new Item("coffee",8,1,1000) );
		menu.add(new Item("tea",6,1,1000) );
		menu.add(new Item("snacks",10,0,100) );
		menu.add(new Item("food",20,0,150) );
		menu.add(new Item("paratha",15,0,200) );
		new Server();
	}
}