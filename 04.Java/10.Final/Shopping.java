class Purse
{
	static int money = 0;

	void printMoney(int in, int out)
	{
		money = money + in - out;

		if(money < 0)
		{
			System.out.println((-1 * money) + "원 부족합니다.");
		}
		else
		{
			System.out.println("잔금은 " + money + "원입니다.");
		}
	}
}

class  Shopping
{
	public static void main(String[] args) 
	{
		Purse store1 = new Purse();
		Purse store2 = new Purse();
		store1.printMoney(1000, 100);
		store2.printMoney(0, 250);
		store1.printMoney(0, 800);
	}
}
