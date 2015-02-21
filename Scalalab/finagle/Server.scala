//#imports
import com.twitter.finagle.{Http, Service}
import com.twitter.util.{Await, Future}
import java.net.InetSocketAddress
import org.jboss.netty.handler.codec.http._
import org.jboss.netty.buffer.ChannelBuffers
//#imports
import com.twitter.finagle.http.filter.StatsFilter
import com.twitter.finagle.http.{Request, Response, HttpMuxHandler, HttpMuxer}
import com.twitter.finagle.stats.{OstrichStatsReceiver, OstrichExporter}

object Server extends App {
//#service
  val underlayService = new Service[Request, Response] {
    def apply(req: Request): Future[Response] = {
      val response = new DefaultHttpResponse(req.getProtocolVersion, HttpResponseStatus.OK)
      response.setContent(ChannelBuffers.wrappedBuffer("hello world\n".getBytes))

      Future.value(Response(response))
    }
  }

//#service
//#builder
  val receiver = new OstrichStatsReceiver()
  val filter = new StatsFilter[Request](receiver)
  val filtedService = filter andThen underlayService

  val service = new Service[HttpRequest, HttpResponse] {
    def apply(req: HttpRequest): Future[HttpResponse] = {
      println("in service apply")
      filtedService(Request(req))
    }
  }
  val server = Http.serve(":8080", new HttpMuxer().withHandler("/hello", service).withHandler("/stats.json", new OstrichExporter()))
  Await.ready(server)
//#builder
}
