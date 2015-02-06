case class ListNode[+T](data: T, next: Option[ListNode[T]])

object List {
  def newList[T](data: T) = newListFromNode(new ListNode(data, None))

  def newListFromNode[T](node: ListNode[T]) = new List(node)

  private def travse_iter[A](head:Option[ListNode[A]], fn: (ListNode[A]) => Unit): Unit = {
    head match {
      case Some(node) => {
        fn(node)
        List.travse_iter(node.next, fn)
      }
      case None =>
    }
  }

  def travse[A](l: List[A], fn: (ListNode[A]) => Unit): Unit = {
    travse_iter(Some(l.head), fn)
  }
}

// functional list, immutable list
class List[+T] (node: ListNode[T]) {
  val head = node

  def insert[A >: T](data: A) = List.newListFromNode(new ListNode(data, Some(head)))
}
