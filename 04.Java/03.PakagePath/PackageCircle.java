class PackageCircle
{
	public static void main(String[] args)
	{
		orange.area.Circle c1 = new orange.area.Circle(1.5);
		System.out.println("반지름이 1.5인 원의 넓이: " +c1.getArea());

		orange.perimeter.Circle c2 = new orange.perimeter.Circle(2.5);
		System.out.println("반지름이 2.5인 원의 둘레: " +c2.getPerimeter());
	}
}