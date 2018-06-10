var express = require('express');
var router = express.Router();
var spawn = require('child_process').spawn;
var cors = require('cors');

router.options('/', cors());
router.post('/', function(req, res, next) {
	res.header('Access-Control-Allow-Origin', "*");
	res.header('Access-Control-Allow-Methods', "GET, POST, PATCH, PUT, DELETE, OPTIONS");
	res.header('Access-Control-Allow-Headers', "Origin, Content-Type, X-Auth-Token");

	const { lowerProofKit, upperProofKit, secretKey, value, lower, upper } = req.body;
	var ls = spawn('../../ProofKits/bin/generateProof', [lowerProofKit, upperProofKit, secretKey, value, lower, upper]);

	ls.stdout.on('data', function (data) {
		res.status(200).send(data.toString());
	});

	ls.stderr.on('data', function (data) {
		console.log(data.toString());
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
			name: "Bank account number",
			description: "Bank account number",
			value: 3235,
			lowerProofKit: "N3NNwTPpX5IlwQlVq3LijJoIa1HuBlQQeWW4/4KLVnE=",
			upperProofKit: "H9IdHXuSgKnk5T1NSDzWaMRZSTd7QQ2wv7gLIZ2+2Ds=",
			secretKey: "b/z78UMcacilf7eYEOKLIsAnj9jTAZDtADkaNJhXmDE=",
			logo: 'abn',
		},
		{
			name: "Mileage",
			description: "Milages with the lease car",
			value: 75723,
			lowerProofKit: "pu39qXpZ2RZvLR8Hh0Y5H0LDzPAaECyxyaCIRsVpiKY=",
			upperProofKit: "NV31BKbETMaGA3CEkTisHp6V3gvejjmdAokri7bgd9Y=",
			secretKey: "b/z78UMcacilf7eYEOKLIsAnj9jTAZDtADkaNJhXmDE=",
			logo: 'deloitte',
		}
	]);
});

module.exports = router;
