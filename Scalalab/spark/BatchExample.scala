import org.apache.spark.SparkContext
import org.apache.spark.SparkContext._
import org.apache.spark.SparkConf

object BatchExample {
  def main(args: Array[String]) {
    val logFile = "BatchExample.scala"
    val conf = new SparkConf().setMaster("local[2]").setAppName("Batch Example in spark")
    val sc = new SparkContext(conf)
    val logData = sc.textFile(logFile, 2).cache()
    val numAs = logData.filter(line => line.contains("a")).count()
    val numBs = logData.filter(line => line.contains("b")).count()

    println("Lines with a: %s, Lines with b: %s".format(numAs, numBs))
    sc.stop()
  }
}
