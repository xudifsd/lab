package foo.bar

trait Foo {
  def foo() = println("in Foo.foo")
}

object Lib {
  def method() = println("in Lib.method")
}
