import java.io.*;

public class Item implements Serializable{
	String name;
	double price;
	int cookingTime; // in min
	int stock;

	public Item(String name, double price, int cookingTime, int stock){
		this.name = name;
		this.price = price;
		this.cookingTime = cookingTime;
		this.stock = stock;
	}
}