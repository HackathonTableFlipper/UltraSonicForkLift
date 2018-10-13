var http = require('http');
var mysql = require('mysql');
var fs = require('fs');

var config = JSON.parse(fs.readFileSync('config.json', 'utf8'));

var con = mysql.createConnection({
  host: config.mysql.host,
  user: config.mysql.user,
  password: config.mysql.pass
});

con.connect(function(err) {
    if (err) throw err;
    console.log("Connected!");
});

http.createServer(function (req, res) {
    let chunks = [];

    req.on('data', function(data) {
      chunks.push(data);
    }).on('end', function() {
        let data = Buffer.concat(chunks);
        let json = JSON.parse(data);

        console.log(json.type);

        if(json.type && json.type == 'ListLocations') {
            con.query("SELECT location FROM forklift.device GROUP BY location ORDER BY location", function (err, result, fields) {
                if (err) throw err;
                res.writeHead(200, {'Content-Type': 'text/json'});
                res.end(JSON.stringify({"type":json.type, "data": result.map(e => e.location) }));
            });
        } else {
            res.writeHead(200, {'Content-Type': 'text/json'});
            res.end("{}");
        }

    });

}).listen(config.port);