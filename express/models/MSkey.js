const mongoose = require('mongoose');

// Define Schemes
const MkeySchema = new mongoose.Schema({
	id: { type: Number, required: true},
	ktype: { type: String, required: true },
	key: { type: String, required: true, unique: true },
	used: { type: Boolean, required: true, default: false },
	buyer_date: { type: Date, default: "" },
	buyer_name: { type: String, default: "" },
	buyer_email: { type: String, default: "" }
},
{
	timestamps: true
});

MkeySchema.statics.create = function (payload) {
	const Mkey = new this(payload);
	return Mkey.save();
};

MkeySchema.statics.findOneByelem = function (elem) {
	return this.findOne(elem);
};

MkeySchema.statics.findElement = function (elem) {
	return this.find(elem);
};

MkeySchema.statics.updateByKey = function (keynktype, payload) {
	payload['used'] = true;
	payload['buyer_date'] = Date.now();
	return this.findOneAndUpdate(keynktype, payload);
};

MkeySchema.statics.deleteByelem = function (elem) {
	return this.remove(elem).exec();
};

module.exports = mongoose.model('MSkey', MkeySchema);
