var fs = require('fs');
var n = undefined;
function addOne() {
	fs.readFile(process.argv[2], function doneReading(err, buf) {
		if (err)
			return console.log(err);
		str = buf.toString()
		n = str.split('\n').length-1;
		console.log(n);
	});
}

addOne();

