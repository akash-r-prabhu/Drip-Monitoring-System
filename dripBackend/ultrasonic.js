// nodejs backend to get data recieve data from a link and diusplay on console

var http = require("http");
var url = require("url");
var fs = require("fs");
// connect to sql database
var mysql = require("mysql");
var con = mysql.createConnection({
  host: "localhost",
  user: "root",

  database: "DripLevel",
});

// the database has a table called room 1 which has 3 columns timestamp , cm and inches both are float

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

      // write the data to the database
      var sql = "INSERT INTO room2 (dateTime,cm, inches) VALUES ?";
      // timestamp is sql datetime format
      var timestamp = new Date().toISOString().slice(0, 19).replace("T", " ");

      var values = [[timestamp, data.distanceCm, data.distanceInch]];
      con.query(sql, [values], function (err, result) {
        if (err) throw err;
        console.log("Number of records inserted: " + result.affectedRows);
      });

      break;

    case "/getdata":
      // get the data from the database with latest timestamp
      var sql = "SELECT * FROM room2 ORDER BY dateTime DESC LIMIT 1";
      con.query(sql, function (err, result) {
        if (err) throw err;
        console.log(result);
        response.writeHead(200, {
          "Content-Type": "text/plain",
        });
        // result of inches = 60
        result[0].inches = 60;
        response.write(JSON.stringify(result));
        response.end();
      });
      break;

    case "/getdataall":
      // get the data from the database with latest timestamp
      var sql = "SELECT * FROM room2";
      con.query(sql, function (err, result) {
        if (err) throw err;
        console.log(result);
        response.writeHead(200, {
          "Content-Type": "text/plain",
        });
        response.write(JSON.stringify(result));
        response.end();
      });
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
