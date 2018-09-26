// Server thread handle incoming connections from everyconnection else

import java.util.*;
import java.net.*;
import java.io.*;

public class ServerThread extends Thread{
	Socket socket;
	Server server;
	ObjectInputStream objectin;
	ObjectOutputStream objectout;
	DataInputStream datain;
	boolean run = true;

	public ServerThread(Socket socket, Server server){
		super("ServerThread");
		this.socket = socket;
		this.server = server;
	}

	public void sendMenuToClient(ArrayList<Item> menu){
		try{
			objectout.writeObject(menu);
			objectout.flush();
		}
		catch(IOException e){
			e.printStackTrace();
		}
	}

	public void sendMenuToAllClient(ArrayList<Item> menu){
		for(int i = 0; i < Server.threads.size(); i++){
			ServerThread temp = Server.threads.get(i);
			temp.sendMenuToClient(menu);
		}
	}

	public void updateMenu(ArrayList<Order> orderList){
		System.out.println("hello");
		for(int i =0; i < Server.menu.size();i++){
			Server.menu.get(i).stock -= orderList.get(i).quantity;
		}
		System.out.println("");
	}

	public void run(){
		try{
			datain = new DataInputStream(socket.getInputStream());
			objectout = new ObjectOutputStream(socket.getOutputStream());
			objectin = new ObjectInputStream(socket.getInputStream());
			while(run){
				String check = datain.readUTF();
				if(new String("start").equals(check)){
					// send menu to client
					sendMenuToClient(Server.menu);
				}
				else if(new String("stop").equals(check)){
					// recive order list from client
					Object object = objectin.readObject();
					// @SuppressWarnings("unchecked")
            		Server.orderList =  (ArrayList<Order>) object;
            		// send menu to all client as menu been updated
					// sendMenuToAllClient(menu);
					for(int i =0;i < Server.orderList.size();i++){
						System.out.println(Server.orderList.get(i).name + " , " + Server.orderList.get(i).quantity);
					}
						updateMenu(Server.orderList);
						Server.orderList.clear();
					run = false;
				}
			}
			datain.close();
			objectin.close();
			objectout.close();
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
}