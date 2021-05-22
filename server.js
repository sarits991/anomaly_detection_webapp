const express = require("express")
const app = express();
const userRoutes = require('./routes/route');
const fileUpload = require('express-fileupload')
app.use(express.json());
app.use(express.static('view'))
app.use(fileUpload({}))
app.use('/', userRoutes);

app.listen(8080, () => {
    console.log("Server running on port 8080");
});

