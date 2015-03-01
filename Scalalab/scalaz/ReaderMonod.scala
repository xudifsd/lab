import scalaz.Reader

case class A(i: Int, s: String)

case class B(a: A, s: String, b: Boolean)

object ReaderMonod {
  def constructA(s: String) = Reader((i: Int) => new A(i, s))

  def constructB(b: Boolean) = Reader((i: Int) => new B(new A(i, "bb"), "cc", b))

  def main(args: Array[String]):Unit = {
    println(constructA("s")(1))
    println(constructB(true)(1))
  }
}
