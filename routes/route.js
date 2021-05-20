const express = require('express');
const control = require("../controller/control");
const router = express.Router();

router.post("/detect", control.findAnomalies);
router.get("/", control.getHtml);

module.exports = router;