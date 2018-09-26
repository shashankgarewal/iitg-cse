import java.util.*;
import java.net.*;
import java.io.*;

public class ClientThread extends Thread{
	Socket socket;
	Client client;
	ObjectInputStream objectin;
	ObjectOutputStream objectout;
	DataOutputStream dataout;
	boolean run = true;

	public ClientThread(Socket socket, Client client){
		super("ClientThread");
		this.socket = socket;
		this.client = client;
	}

	public void sendMenuToServer(ArrayList<Order> orderList){
		try{
			objectout.writeObject(orderList);
			objectout.flush(); 
		}
		catch(IOException e){
			e.printStackTrace();
			close();
		}
	}

	public void run(){
		try{
			dataout = new DataOutputStream(socket.getOutputStream());
			objectout = new ObjectOutputStream(socket.getOutputStream());
			objectin = new ObjectInputStream(socket.getInputStream());

			while(run){
				try{
					System.out.println("here");
					String check = "start";
					dataout.writeUTF(check);
					Object object = objectin.readObject();
					// @SuppressWarnings("unchecked")
            		Client.menu = (ArrayList<Item>) object;

            		check = "stop";
            		dataout.writeUTF(check);

            		sendMenuToServer(Client.orderList);
            		run = false;

            		for(int i =0;i < Client.orderList.size();i++){
						System.out.println(Client.menu.get(i).name + " " +Client.menu.get(i).stock);
					}
				}
				catch(Exception e){
					e.printStackTrace();
					close();
				}
			}
		}
		catch(IOException e){
			e.printStackTrace();
			close();
		}
	}

	public void close(){
		try{
			dataout.close();
			objectout.close();
			objectin.close();
		}
		catch(IOException e){
			e.printStackTrace();
		}
	}
}