object Main {
  def main(args: Array[String]):Unit = {
    var list:List[Any] = List.newList("aaa")
    val fn = (node: ListNode[Any]) =>
      println(node.data)
    list = list.insert("ccc")
    list = list.insert(123)
    List.travse(list, fn)
  }
}
