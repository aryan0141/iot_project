const express = require("express");
require("dotenv").config();
const router = express.Router();
const Sensor = require("../models/Sensors");

router.post("/liveSensorData", async (req, res) => {
    const main = [];
    let content;
    if (process.env.USE_PYTHON_SCRIPT == "true") {
        content = JSON.parse(`${JSON.stringify(req.body.data)}`); // For testing through python script.
    } else {
        content = JSON.parse(`${JSON.stringify(req.body)}`.slice(1, -4)); // For actual purposes.
    }
    const arr = content.split("|");
    arr.forEach((elm) => {
        let obj = JSON.parse(elm.replace(/'/gi, `"`));
        obj["time"] = new Date().toISOString();
        main.push(obj);
    });
    console.log("Received Value: ", main[0]);
    res.json({ msg: "Data received succesfully!" });

    // Adding the current data in the database
    const newSensor = new Sensor({
        time: main[0].time,
        data: main[0].data,
    });
    await newSensor.save();
});


// @ Get all the data of the sensors
router.get("/getAllData", async (req, res) => {
    try {
        const data = await Sensor.find();
        return res.status(200).json(data);
    } catch (err) {
        console.log(err);
        return res.status(500).json({ msg: "Internal Server Error" });
    }
});

module.exports = router;