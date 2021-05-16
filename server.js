var express = require("express"), bodyParser = require('body-parser');;
var app = express();
var userRoutes = require('./routes/route');
app.use(bodyParser.json());
app.use(express.json());

app.use('/', userRoutes);
app.listen(8080, () => {
    console.log("Server running on port 9876");
});

