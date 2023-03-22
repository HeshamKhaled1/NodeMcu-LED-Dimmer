const { response } = require('express')
const express = require('express')
const app = express()
const port = 3000
app.get('/',function(req,res){

    res.sendFile(__dirname+"/index.html");
});


const server = app.listen(port,function(){
    console.log("server is run at port "+port);
});

const SocketServer = require('ws').Server;
const wss = new SocketServer({ server });

let value = 0;

wss.on('connection',function (ws) {
    console.log('client connected');
    ws.send(value);
    ws.on('message',function(msg){
        value= msg+"";
        console.log(value);
        broadcast(value);
    });
    ws.on('close',function(){
     console.log('client disconnected');
    });
});
function broadcast(msg){
wss.clients.forEach(function (client) {
 if (client.readyState === client.OPEN){
    client.send(msg);
 }

});

}