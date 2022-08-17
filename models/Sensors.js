const mongoose = require("mongoose");

const SensorsSchema = new mongoose.Schema({
  name: {
    type: String,
    required: false,
    default: "Ultrasonic-1"
  },
  time: {
    type: String,
    required: true,
  },
  data: {
    type: String,
    required: true,
  },
});

module.exports = mongoose.model("Sensors", SensorsSchema);