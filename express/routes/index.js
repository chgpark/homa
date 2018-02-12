var express = require('express');
var router = express.Router();
var Mkey = require('../models/MSkey');

var indexArray = ['search', 'upload'];

/* GET home page. */
router.use(function timeLog(req, res, next) {
	console.log('Time: ', Date.now());
	next();
});

router.get('/', (req, res, next) => {
	res.render('index', { title: 'Index Page', data: indexArray });
});

router.get('/search', (req, res, next) => {
	var elem = {};
	if (req.query.id) elem = {'id':req.query.id};
		Mkey.findElement(elem)
			.then((mkeys) => {
				if (!mkeys.length) return res.status(404).send({ err: 'mkey not found' });
				res.render('search', { title: 'Search Page', data: mkeys, condition: true });
			})
			.catch(err => res.status(500).send(err));
});

router.post('/search', (req, res) => {
	Mkey.create(req.body)
		.then(mkey => res.send(mkey))
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

router.get('/test1', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.get('/test2', (req, res, next) => {
	res.render('index', { title: 'Cool', condition: false } );
});

module.exports = router;
