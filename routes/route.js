const express = require('express');
const control = require("../controller/control");
const router = express.Router();

router.post("/api/model/detect", control.findAnomalies);

module.exports = router;