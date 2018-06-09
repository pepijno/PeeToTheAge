var express = require('express');
var router = express.Router();
var spawn = require('child_process').spawn;

router.get('/', function(req, res, next) {
	var oneof = false;
	if(req.headers.origin) {
		res.header('Access-Control-Allow-Origin', req.headers.origin);
		oneof = true;
	}
	if(req.headers['access-control-request-method']) {
		res.header('Access-Control-Allow-Methods', req.headers['access-control-request-method']);
		oneof = true;
	}
	if(req.headers['access-control-request-headers']) {
		res.header('Access-Control-Allow-Headers', req.headers['access-control-request-headers']);
		oneof = true;
	}
	if(oneof) {
		res.header('Access-Control-Max-Age', 60 * 60 * 24 * 365);
	}

	const { lowerProofKit, upperProofKit, secretKey, value, lower, upper } = req.query;
	var ls = spawn('../../ProofKits/bin/proofKit', [lowerProofKit, upperProofKit, secretKey, value, lower, upper]);

	ls.stdout.on('data', function (data) {
		res.status(200).send(data.toString());
	});

	ls.stderr.on('data', function (data) {
		//console.log(data.toString());
	});

	ls.on('exit', function (code) {
		res.end();
	});
});

router.get('/items', function(req, res, next) {
	var oneof = false;
	if(req.headers.origin) {
		res.header('Access-Control-Allow-Origin', req.headers.origin);
		oneof = true;
	}
	if(req.headers['access-control-request-method']) {
		res.header('Access-Control-Allow-Methods', req.headers['access-control-request-method']);
		oneof = true;
	}
	if(req.headers['access-control-request-headers']) {
		res.header('Access-Control-Allow-Headers', req.headers['access-control-request-headers']);
		oneof = true;
	}
	if(oneof) {
		res.header('Access-Control-Max-Age', 60 * 60 * 24 * 365);
	}
	res.status(200).send([
		{
			name: "Item1",
			description: "Descr",
			value: 100,
			lowerProofKit: "a",
			upperProofKit: "b",
			secretKey: "c",
			logo: 'abn',
		},
		{
			name: "Item2",
			description: "Descr",
			value: 100,
			lowerProofKit: "aaaaa",
			upperProofKit: "bbbb",
			secretKey: "ccccc",
			logo: 'tesla',
		}
	]);
});

module.exports = router;
