const express = require('express');
const app = express();
const bodyParser= require('body-parser');
let port = process.env.PORT || 3000;

let command = -1;

app.use(bodyParser.urlencoded({extended:true}));
app.use(express.static(__dirname ));

app.set('view engine', 'pug');

app.get('/', (req, res) => {
        res.render('index');
        //res.sendStatus(command);
        // res.send(command);
});

app.post('/poweron',(req,res)=>{

command = req.body.powerOn; // here you can get the value of from the textbox
    res.render('index');
});

app.post('/arrowup',(req,res)=>{

    command = req.body.arrowUp; // here you can get the value of from the textbox
    res.render('index');
});

app.post('/arrowdown',(req,res)=>{

    command = req.body.arrowDown; // here you can get the value of from the textbox
    res.render('index');
});

app.post('/fan',(req,res)=>{

    command = req.body.fan; // here you can get the value of from the textbox
    res.render('index');
});

app.post('/nightmode',(req,res)=>{

    command = req.body.nightMode; // here you can get the value of from the textbox
    res.render('index');
});

app.post('/format',(req,res)=>{

    command = req.body.format; // here you can get the value of from the textbox
    res.render('index');
});

app.post('/mode',(req,res)=>{

    command = req.body.mode; // here you can get the value of from the textbox
    res.render('index');
});

app.post('/angle',(req,res)=>{

    command = req.body.angle; // here you can get the value of from the textbox
    res.render('index');
});

app.post('/timer',(req,res)=>{

    command = req.body.timer; // here you can get the value of from the textbox
    res.render('index');
});

app.get('/command',(req,res)=>{
    res.send(command.toString());
});

app.listen(port, () => console.log('Server is running on port ' + port));