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
            handleConnection(res, body);
        } catch (err) {
            replyWithError(res, err);
        }
    });
}).listen(config.port);

handleConnection = (res, body) => {
    let data = Buffer.concat(body).toString();
    let json = JSON.parse(data);

    if(json.type) {
        switch(json.type) {
            case 'init':
                return requestInit(res, json);

            case 'log':
                return requestLog(res, json);

            default:
                throw 'Unsupported Type';
        }
        return;
    }

    throw 'No Typ';
}

sqlWrapper = (res, query) => {
    console.log(query)
    con.query(query).then(
        result => {
            return replyWithOK(res);
        },
        err => {
            return replyWithError(res, err);
        }
    );
}

requestInit = (res, {type, mac, name, location}) => {
    if(!name || !location || !mac)
        throw "wrong arguments";

    checkMac(mac);

    if(name.length > 32 || location.length > 32)
        throw "string to long";

    con.query(`SELECT * FROM forklift.device \
            WHERE (location = ${ce(location)} \
            AND name = ${con.escape(name)}) \
            OR macaddress = ${ce(mac)};` )
        .then(result => {
            if(result.length > 0)
                return replyWithError(res,"already initialized");

            sqlWrapper(res, `INSERT INTO \`forklift\`.\`device\` \
                (\`macaddress\`, \`name\`, \`location\`) VALUES \
                (${ce(mac)}, ${ce(name)}, ${ce(location)});`);
        });
}

requestLog = (res, {type, mac, data} ) => {
    if(!mac || !data || !Array.isArray(data))
        throw "wrong arguments";

    checkMac(mac);

    if(data.length == 0)
        return replyWithOK(res);

    sqlWrapper(res, `INSERT INTO \`forklift\`.\`log\` \
        (\`macaddress\`, \`load\`, \`start\`, \`end\`) VALUES \
        ` + data.map( ({load, start, end}) => {
            return `(${ce(mac)},${ce(load)},${ce(new Date(start))},${ce(new Date(end))})`
        }).join(',')
        + `;`);
}

replyWithError = (res, err) => {
    res.writeHead(500, {'Content-Type': 'text/html'});
    res.end('<h1>Internal server error</h1> "' + err + '"');
}

replyWithOK = (res) => {
    res.writeHead(200, {'Content-Type': 'application/json'});
    res.end( );
}

checkMac = (mac) => {
    if(mac.length != 12)
        throw "mac has wrong format <string>(12)";
}

let ce = obj => con.escape(obj);