var fs = require('fs');

buf = fs.readFileSync(process.argv[2]);
str = buf.toString().split('\n');
console.log(str.length-1);
