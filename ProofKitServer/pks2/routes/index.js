var express = require('express');
var router = express.Router();
var spawn = require('child_process').spawn;
var cors = require('cors');

router.options('/', cors());
router.post('/', function(req, res, next) {
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

	const { lowerProofKit, upperProofKit, lowerProof, upperProof, lowerCheck, upperCheck } = req.body;
	var ls = spawn('../../ProofKits/bin/checkProof', [lowerProofKit, upperProofKit, lowerProof, upperProof, lowerCheck, upperCheck]);

	ls.stdout.on('data', function (data) {
		console.log(data.toString());
	});

	ls.stderr.on('data', function (data) {
		console.log(data.toString());
	});

	ls.on('exit', function (code) {
		res.end();
	});
});

module.exports = router;
