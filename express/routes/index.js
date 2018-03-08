var express = require('express');
var upload = require('express-fileupload');
var csv = require('parse-csv');
var router = express.Router();
var Mkey = require('../models/MSkey');
var parsingTool = require('./parmod');

var indexArray = ['search', 'upload'];
var ktypeArray = ['WIOP', 'WIPF', 'WIHO', 'WIHF', 'OFPP', 'OFHS']

var pT = new parsingTool();

/* GET home page. */
router.use(upload());
router.use(function timeLog(req, res, next) {
	console.log('Time: ', Date.now());
	next();
});

router.get('/', (req, res, next) => {
	res.render('index', { title: 'Index Page', data: indexArray });
});

router.get('/search', (req, res, next) => {
	var elem = {};
	var cnum = {
		'WIPO':{'used':0,'unused':0}, 
		'WIPF':{'used':0,'unused':0}, 
		'WIHO':{'used':0,'unused':0}, 
		'WIHF':{'used':0,'unused':0}, 
		'OFPP':{'used':0,'unused':0},
		'OFHS':{'used':0,'unused':0} 
	};
	if (req.query.id) elem['id'] = req.query.id;
	if (req.query.key) elem['key'] = req.query.key;
	if (req.query.name) elem['buyer_name'] = req.query.name;
	if (req.query.email) elem['buyer_email'] = req.query.email;
	if (req.query.type !== 'TOTAL') elem['ktype'] = req.query.type;
	elem['used'] = req.query.used;

	var timeStamp = pT.getTms();

	Mkey.findElement({})
		.then((mkeys) => {
			let	ii = -1;
			while (++ii < mkeys.length){
				if (mkeys[ii].used) cnum[mkeys[ii].ktype].used += 1;
				else cnum[mkeys[ii].ktype].unused += 1;
			}
			console.log(mkeys);
		});
	Mkey.findElement(elem)
		.then((mkeys) => {
			res.render('search', { title: 'Search Page', data: mkeys, cnt: cnum, condition: true, ktypelist: ktypeArray });
		})
		.catch(err => res.status(500).send(err));
});

router.post('/search', (req, res) => {
	Mkey.findElement(req.body)
		.then(mkey => res.send(mkey.length.toString()))
		.catch(err => res.status(500).send(err));
});

router.put('/mkeyid/:id', (req, res) => {
	Mkey.updateById(req.params.id, req.body)
		.then(mkey => res.send(mkey))
		.catch(err => res.status(500).send(err));
});

router.delete('/mkeyid/:id', (req, res) => {
	Mkey.deleteById(req.params.id)
		.then(() => res.sendStatus(200))
		.catch(err => res.status(500).send(err));
});

router.get('/search/submit', (req, res, next) => {
	Mkey.findElement(req.query.id)
		.then((mkeys) => {
			if (!mkeys.length) return res.status(404).send({ err: 'mkey not found' });
			res.render('search', { data: mkeys, condition: true });
		})
		.catch(err => res.status(500).send(err));
});

router.post('/search/submit', (req, res, next) => {
	Mkey.create(req.body)
		.then(mkey => res.send(mkey))
		.catch(err => res.status(500).send(err));
});

router.get('/uploadByKey', function(req, res, next) {
  res.render('uploadByKey', { title: 'UploadByKey' });
});

router.post('/uploadByKey', (req, res, next) => {
	var elem = {};
	var payload = {};

	elem['ktype'] = req.body.type;
	if (req.body.key) elem['key'] = req.body.key;
	else return res.send('Must write key');
	if (req.body.name && req.body.email) {
		payload['buyer_email'] = req.body.email;
		payload['buyer_name'] = req.body.name;
	} else return res.send('Must fullfill');
	Mkey.updateByKey(elem, payload);
});

router.get('/upload', function(req, res, next) {
  res.render('upload', { title: 'Upload' });
});

router.post('/upload', function(req, res, next) {
	if (req.files){
		var file = req.files.filename, filename = file.name;
		if (file.mimetype !== 'text/csv')
			return res.send("Invalid file format");
		//file.mv("./upload/"+filename, (err) => {if (err) res.send("error occured");else res.send("success");});
		pT.parmod(file.data.toString());
		
	}
});

router.get('/test2', (req, res, next) => {
	res.render('index', { title: 'Cool', condition: false } );
});

router.post('/create', (req, res, next) => {
	console.log(req.body);
});

module.exports = router;
