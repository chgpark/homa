const mongoose = require('mongoose');

// Define Schemes
const MkeySchema = new mongoose.Schema({
	id: { type: Number, required: true, unique: true },
	ktype: { type: String, required: true },
	key: { type: String, required: true },
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

MkeySchema.statics.findAll = function () {
	return this.find({});
};

MkeySchema.statics.findOneById = function (id) {
	return this.findOne({ id });
};

MkeySchema.statics.findElement = function (elem) {
	return this.find(elem);
};

MkeySchema.statics.updateById = function (id, payload) {
	return this.findOneAndUpdate({ id }, payload, { buyer_date: Date.now });
};

MkeySchema.statics.deleteById = function (id) {
	return this.remove({ id });
};

module.exports = mongoose.model('MSkey', MkeySchema);
