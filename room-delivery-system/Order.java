import java.io.*;

public class Order implements Serializable{
	String name;
	int quantity;

	public Order(String name, int quantity){
		this.name = name;
		this.quantity = quantity;
	}
}