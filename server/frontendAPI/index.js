var http = require('http');
var fs = require('fs');
var Database = require('./Database.class.js');

var config = JSON.parse(fs.readFileSync('config.json', 'utf8'));

var con = new Database(config.mysql);

http.createServer(function (req, res) {
    res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');
    res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,content-type');

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
        obj = {"type": json.type, "data": null};

        switch(json.type) {
            case 'ListLocations':
                return listLocations(obj, res);

            case 'ListDevices':
                return listDevices(obj, res, json);

            case 'ListOverview':
                return listOverview(obj, res, json);

            case 'ListData':
                return listData(obj, res, json);

            default:
                throw 'Unsupported Type';
        }
        return;
    }

    throw 'No Typ';
}

sqlWrapper = (obj, res, query, func) => {
    console.log(query);
    con.query(query).then(
        result => {
            obj.data = func(result);
            res.writeHead(200, {'Content-Type': 'application/json'});
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
        where.push('start >= ' + con.escape(new Date(json.start)));
    if(json.end)
        where.push('end <= ' + con.escape(new Date(json.end)));
    if(json.location)
        where.push('location = ' + con.escape(json.location) )

    sqlWrapper(
        obj, 
        res, 
        'SELECT device.macaddress, name, location \
            FROM forklift.device LEFT JOIN forklift.log ON device.macaddress = log.macaddress \
            ' + (where.length > 0 ? ' WHERE ' + where.join(' AND ' ) : '') + ' \
            GROUP BY device.macaddress \
            ORDER BY location',
        (result) => {
            return result.map(e => { return {
                "id": e.macaddress,
                "name": e.name,
                "location": e.location
            } } );
        }
    )
}

listOverview = (obj, res, json) => {
    forDevices(
        obj, res, json,
        device => {return {
            "id": device.id,
            "name": device.name,
            "location": device.location,
            "loadedTime": device.loadedTimes.map(e => e[1]-e[0]).reduce( (r,a) => r+a, 0)/1000 | 0,
            "emptyTime":   device.emptyTimes.map(e => e[1]-e[0]).reduce( (r,a) => r+a, 0)/1000 | 0,
        }}
    )
}

listData = (obj, res, json) => {
    forDevices(
        obj, res, json,
        device => device
    )
}

forDevices = (obj, res, json, func) => {
    if(!json.devices || !Array.isArray(json.devices) || json.devices.length == 0 || !json.start || !json.end)
        throw "wrong arguments";

    let where = [
        'start >= ' + con.escape(new Date(json.start)),
        'end <= ' + con.escape(new Date(json.end)),
        '(' + json.devices.map( id => 'device.macaddress = ' + con.escape(id) ).join(' OR ') + ')'
    ];

    sqlWrapper(
        obj, 
        res, 
        'SELECT * FROM forklift.device LEFT JOIN forklift.log ON device.macaddress = log.macaddress \
            WHERE ' + where.join(' AND ') + '\
            ORDER BY location, device.macaddress',
        (result) => {
            devices = []
            tmpDeviceMac = null;
            result.forEach(d => {
                elem = devices.length > 0 ? devices[devices.length-1] : null;
                if(!elem || elem.id != d.macaddress) {
                    devices.push({
                        "id": d.macaddress, 
                        "name": d.name, 
                        "location": d.location, 
                        "loadedTimes": [],
                        "emptyTimes": []
                    });
                }
                if(d.load)
                    devices[devices.length-1].loadedTimes.push([d.start, d.end]);
                else
                    devices[devices.length-1].emptyTimes.push([d.start, d.end]);
            })
            return devices.map(func);
        }
    )
}

