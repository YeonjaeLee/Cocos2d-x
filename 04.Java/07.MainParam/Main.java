class Main 
{
	public static void main(String[] args) 
	{
		int i;

		if(args.length == 0)
		{
			System.out.println("커맨드라인 인수가 없습니다.");
		}
		else 
		{	
			for(i = 0; i < args.length; i++)
			{
				System.out.println((i + 1) + ": " + args[i]);
			}
		}
	}

}
