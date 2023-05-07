// nodejs backend to get data recieve data from a link and diusplay on console

var http = require("http");
var url = require("url");
var fs = require("fs");


var server = http.createServer(function (request, response) {
  var path = url.parse(request.url).pathname;

  switch (path) {
    case "/":
      response.writeHead(200, {
        "Content-Type": "text/plain",
      });
      response.write("This is Test Message.");
      response.end();
      break;
    // if the path is /data and a variable is passed print the variable
    case "/data":
      var data = url.parse(request.url, true).query;
      console.log(data);
      response.writeHead(200, {
        "Content-Type": "text/plain",
      });
      response.write("This is Test Message.");
      response.end();
    //   to test this go to http://localhost:8001/data?name=hello

      break;

    default:
      response.writeHead(404);
      response.write("opps this doesn't exist - 404");
      response.end();
      break;
  }
});

server.listen(8001);
console.log("Server is listening");
