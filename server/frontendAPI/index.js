var http = require('http');
var fs = require('fs');
var Database = require('./Database.class.js');

var config = JSON.parse(fs.readFileSync('config.json', 'utf8'));

var con = new Database(config.mysql);

http.createServer(function (req, res) {
    let body = [];
    req.on('data', (chunk) => {
        body.push(chunk);
    }).on('end', () => {
        try {
            handleConnection(body, res);
        } catch (err) {
            res.writeHead(500, {'Content-Type': 'text/html'});
            res.end('<h1>Internal server error</h1> "' + err + '"');
        }
    });
}).listen(config.port);

handleConnection = (body, res) => {
    let data = Buffer.concat(body).toString();
    let json = JSON.parse(data);

    if(json.type) {
        res.writeHead(200, {'Content-Type': 'application/json'});
        obj = {"type": json.type, "data": null};
        switch(json.type) {
            case 'ListLocations':
                listLocations(obj, res);
                break;

            case 'ListDevices':
                listDevices(obj, res, json);
                break;

            default:
                throw 'Unsupported Type';
        }

    } else {
        throw 'No Typ';
    }
}

sqlWrapper = (obj, res, query, func) => {
    con.query(query).then(
        result => {
            obj.data = func(result)
            res.end( JSON.stringify(obj) );
        },
        err => {
            throw err;
        }
    );
}

listLocations = (obj, res) => {
    sqlWrapper(
        obj, 
        res, 
        'SELECT location FROM forklift.device GROUP BY location ORDER BY location',
        (result) => {return result.map(e => e.location)}
    )
}

listDevices = (obj, res, json) => {
    let where = [];
    if(json.start)
        where.push('start > ' + con.escape(new Date(json.start)));
    if(json.end)
        where.push('end < ' + con.escape(new Date(json.end)));
    if(json.location)
        where.push('location = ' + con.escape(json.location) )

    sqlWrapper(
        obj, 
        res, 
        'SELECT device.macaddress, name, location \
            FROM forklift.device LEFT JOIN forklift.log ON device.macaddress \
            ' + (where.length > 0 ? ' WHERE ' + where.join(' AND ' ) : '') + ' \
            GROUP BY device.macaddress \
            ORDER BY location',
        (result) => {
            return result.map(e => {return {"id":e.macaddress,"name":e.name,"location":e.location}} );
        }
    )
}

