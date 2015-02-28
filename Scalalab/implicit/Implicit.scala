trait Base {
  def base() = println("in base")
}

class A extends Base
class B extends Base
case class C[X](s: String, i: X) extends Base

sealed trait Featured[X] // this is just a marker trait

object Featured {
  implicit def featureC[X]: Featured[C[X]] = new Featured[C[X]] {}
}

object Implicit {
  def test[X <: Base](base: X)(implicit f: Featured[X]) = {
    // implicit here restrict only object that have implicit type view to Featured can be passed as base
    base.base()
  }

  def main(args: Array[String]):Unit = {
    test(new C("a", "b"))
    // test(new B()) this won't compiled
  }
}
