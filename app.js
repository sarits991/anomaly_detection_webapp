const express = require("express")
const app = express();
const userRoutes = require('./routes/route');
const fileUpload = require('express-fileupload')
app.use(express.json());
app.use(express.static('view'))
app.use(fileUpload({}))
app.use('/', userRoutes);

let fs = require('fs');
let dir = "csv_files"
if (!fs.existsSync(dir)){
    fs.mkdirSync(dir);
}

app.listen(8080, () => {
    console.log("Server running on port 8080");
});

