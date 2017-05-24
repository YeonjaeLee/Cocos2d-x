import java.util.Scanner;

class  DivideByZero
{
	public static void main(String[] args) 
	{
		System.out.println("두 개의 정수 입력: ");
		Scanner keyboard = new Scanner(System.in);  // System.in ←scanf와 같은 것
		int num1 = keyboard.nextInt();
		int num2 = keyboard.nextInt();

		try// 예외가 발생할수 있는 부분을 적어준다
		{
			System.out.println("나눗셈 결과의 몫: " + (num1 / num2));
			System.out.println("나눗셈 결과의 나머지: " + (num1 % num2));
		}
		catch (ArithmeticException e)  // 이곳에서 모든 예외처리를 해준다.
		{
			System.out.println("나눗셈 불가능");
			System.out.println(e.getMessage()); // e.getMessage() 예외가 발생한 원인정보를 문자열의 형태로 반환해줌
		}

		System.out.println("프로그램을 종료합니다.");
	}
}
