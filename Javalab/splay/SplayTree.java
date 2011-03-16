class Node{	//Node is used by SplayTree class
	public String word;
	public int count;
	public Node left_node;
	public Node right_node;

    public Node(String word){
        this.word=word;
        this.count=1;
        this.left_node=null;
        this.right_node=null;
	}
}

class Container{	//Container class is used by top10
	public String word;
	public int count;

	public Container(){
		this.word="";
		this.count=0;
	}

	public Container(String word,int count){
		this.word= new String(word);
		this.count=count;
	}

	public String toString(){
		return this.count+"\t"+this.word;
	}
}

public class SplayTree{
	public Node root;
	private int sum;
	private Container[] top10 = new Container[10];

	public SplayTree(){
        this.root=null;
        this.sum=0;      //sum is the sum of all words.
	}

    public void insert(String word){
        if ( this.root==null ){	//if tree is empty.
            this.root=new Node(word);
            this.sum+=1;
            return;
		}
        else{
			Node p;
            p=this.root; //p is a pointer.
            while ( true ){
                if ( p.word.compareTo(word) == 0 ){
                    p.count+=1;
                    this.sum+=1;
                    return;
				}
				else if ( p.word.compareTo(word) > 0 ){
                    if ( p.left_node == null ){
                        p.left_node=new Node(word);
                        this.sum+=1;
                        return;
					}
                    else{
                        p=p.left_node;
                        continue;
					}
				}
				else if ( p.word.compareTo(word) < 0 ){
                    if ( p.right_node == null ){
                        p.right_node=new Node(word);
                        this.sum+=1;
                        return;
					}
                    else{
                        p=p.right_node;
                        continue;
					}
				}
			}
		}
	}

    public void printall(Node address){
		Node p=address;
        if ( p.left_node != null)
            printall(p.left_node);
        System.out.print(p.word+'\t');
        if ( p.right_node != null )
            printall(p.right_node);
	}

    public Container[] getTop10(Node address){
		Node p=address;
		int i;
        if ( p.left_node != null )
            getTop10(p.left_node);

		Container temp=new Container(p.word,p.count);

		//below is used to fill the top10
		for ( i=0;i<10;i++ ){	//test whether top10[] was filled
			if ( top10[i] == null ){
				break;
			}
		}


		if ( i<10 )	//fill the top10
			top10[i]=new Container (temp.word,temp.count);
		//up is used to fill the top10

		else{	//top10 was already filled
            Container min=top10[0];
            for ( i=1;i<10;i++){    //find the mixest in top10.
                if ( top10[i].count < min.count )
                    min=top10[i];
			}
            if ( temp.count > min.count ){
                min.word=temp.word;
                min.count=temp.count;
			}
		}

        if ( p.right_node != null )
            getTop10(p.right_node);
		if ( p==this.root )	//sort top10 array
			sort();
		return top10;
	}

	private void sort(){
		Container p1,p2;
		for ( int times=0;times<10;times++ ){
			for ( int i=0;i<9;i++ ){
				p1=top10[i];
				p2=top10[i+1];
				if ( p1.count<p2.count )
					swap(p1,p2);
			}
		}
	}
	private void swap(Container p1,Container p2){
		Container temp=new Container(p1.word,p1.count);

		p1.word=p2.word;
		p1.count=p2.count;

		p2.word=temp.word;
		p2.count=temp.count;
	}
}
