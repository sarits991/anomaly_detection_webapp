const express = require('express');
const control = require("../controller/control");
const router = express.Router();

router.post("/api/model", control.learn);
router.get("/api/model", control.getModel);
router.get("/api/models", control.getAllModels);
router.delete("/api/model", control.deleteModel);


module.exports = router;