public class Test{
	public static void main(String[] args){
		SplayTree a=new SplayTree();
		Container[] result;
		a.insert("this");
		a.insert("this");
		a.insert("this");
		a.insert("this");
		a.insert("is");
		a.insert("is");
		a.insert("is");
		a.insert("it");
		a.insert("it");
		a.insert("it");
		a.insert("it");
		a.insert("it");
		a.insert("you");
		a.insert("you");
		a.insert("you");
		a.insert("are");
		a.insert("are");
		a.insert("are");
		a.insert("are");
		a.insert("not");
		a.insert("not");
		a.insert("not");
		a.insert("not");
		a.insert("alone");
		a.insert("alone");
		a.insert("alone");
		a.insert("alone");
		a.insert("we");
		a.insert("we");
		a.insert("we");
		a.insert("we");
		a.insert("are");
		a.insert("the");
		a.insert("world");
		a.insert("world");
		a.insert("world");
		a.insert("world");
		a.insert("world");
		a.insert("hello");
		a.insert("hello");
		a.insert("hello");
		a.insert("hello");
		a.insert("hello");
		a.insert("world");
		a.insert("my");
		a.insert("heart");
		a.insert("will");
		a.insert("go");
		result=a.getTop10(a.root);
		for (int i=0;i<10;i++)
			System.out.println(result[i]);
	}
}
