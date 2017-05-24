interface Cry
{
	void cry();
}

class Cat implements Cry
{
	public void cry()
	{
		System.out.println("야옹~");
	}
}

class Dog
{
	public void cry()
	{
		System.out.println("멍멍");
	}
}

class  CheackCry
{
	public static void main(String[] args) 
	{
		Cat cat = new Cat();
		Dog dog = new Dog();

		if(cat instanceof Cry)       // instanceof는 cat이 Cry로 부터 상속을 받은것이냐아니냐
		{							 // 라는걸 알려주는 친절한 수식
			cat.cry();
		}
		else if(dog instanceof Cry)  
		{
			dog.cry();
		}
	}
}
