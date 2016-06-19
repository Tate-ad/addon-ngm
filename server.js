var os = require('os');
var fs = require('fs');

var restify = require('restify');

function handle(req, res, next) {
    console.log(req.body);
    console.log("req.files-->", req.files.srcfile);
    res.json(req.files);
    return next();
}

var service = restify.createServer({
    name: "BW ngm service"
});


service.use(restify.bodyParser({
    maxBodySize: 0,
    mapParams: true,
    mapFiles: true,
    overrideParams: false,
    keepExtensions: false,
    multiples: true,
    hash: 'sha1'
}));

service.post('/mesh', handle);


service.listen(3003, function(){
    console.log('%s listen on %s', service.name, service.url);
});
