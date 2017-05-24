import java.util.Random;  // import ← C언어의 include와 같은 역할

class  SeedRandom
{
	public static void main(String[] args) 
	{
		Random rand = new Random(12);
		rand.setSeed(System.currentTimeMillis());  // 현재시간을 밀리 초단위로 반환

		for(int i = 0; i < 100; i++)
		{
			System.out.println(rand.nextInt(1000));
		}
	}
}
