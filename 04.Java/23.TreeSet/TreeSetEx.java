import java.util.Iterator;
import java.util.TreeSet;

class TreeSetEx 
{
	public static void main(String[] args) 
	{
		TreeSet<Integer> sTree = new TreeSet<Integer>();
		sTree.add(1);
		sTree.add(2);
		sTree.add(4);
		sTree.add(3);
		sTree.add(2);

		System.out.println("저장된 데이터 수 : " + sTree.size());

		Iterator<Integer> itr = sTree.iterator();
		while(itr.hasNext())
		{
			System.out.println(itr.next());
		}
	}
}


// 중복을 없앤건 set
// 순서를 바로 잡아준건 Tree
// 정렬이 우선이면 TreeSet
// 속도가 우선이면 HashSet