package main

import foo.bar.Foo
import foo.bar.Lib

object fooo extends Foo {
  override def foo() = println("in main.foo")
}

object Main {
  def main(args: Array[String]):Unit = {
    fooo.foo()
    Lib.method()
  }
}
